#include"enum.h"
#include"Game.h"
#include"Button.h"
#include"Mapchip.h"
#include"Jump.h"

static int FadeIn = 255;
Vec2  g_Objpos(100.0f, 280.0f);
Vec2  g_OldObjPos(100.0f, 280.0f);
const int Player_Size = 50;
float slide;
static const float min = 0.0f;
static const float max = 1800.0f;
float current = 0;
float g_CameraX = 0.0f;
bool g_IsGround = true;

void UpdateCamara()
{

	static const float Offset = 200;

	g_CameraX = g_Objpos.X - Offset;

	if (g_CameraX <= 0)
	{
		g_CameraX = 0;
	}
//背景が1280でWindowサイズが640なので移動制限が640まで
	else if (g_CameraX >= 640)
	{
		g_CameraX = 640;
	}

}

void UpdateGameScene()
{
// g_SceneStepの値から各ステップ関数を実行する
	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitGameScene();   break;
	case SceneStep::Run:    RunGameScene();    break;
	case SceneStep::Finish: FinishGameScene(); break;
	}
}

Vec2 World_Pos(Vec2 w_Pos)
{
	//ワールド座標
	Vec2 origin_Pos = Vec2(g_Objpos.X - (640/2),g_Objpos.Y- (480/2));
	//スクリーン座標
	Vec2 screen_Pos = Vec2(w_Pos.X-origin_Pos.X,w_Pos.Y-origin_Pos.Y);
	return screen_Pos;
}

//ゲームシーン初期化
void InitGameScene()
{
	Engine::Update();

	//printf("ゲームシーンの初期化\n");
	Engine::DrawFont(0, 0, "ゲームシーンの初期化\n", FontSize::Large, FontColor::White);

	// ステップをRunに遷移
	g_SceneStep = SceneStep::Run;
}

void DrawBg()
{
	Vec2 w_Pos = Vec2(0.0f, 0.0f);
	Vec2 screen_Pos = World_Pos(w_Pos);
	Engine::DrawTexture(-g_CameraX, w_Pos.Y, "BackGround", 255, 0.0f, 1.0f, 1.0f);
}

//ゲームシーン開始
void RunGameScene()
{
	Engine::Update();

	Vec2 tex_pos;
	Vec2 pos;
	Vec2 chip_size(64.0f, 64.0f);
	Vec2 vector = Vec2(0.0f, 0.0f);		//移動量
	float speed = 4.f;
	bool IsDraw = true;

	//Vec2 w_Pos = Vec2(-200.0f, -100.0f);
	//Engine::DrawFont(0, 0, "ゲームシーン\n", FontSize::Large, FontColor::White);
	//Engine::DrawTexture(0, 0, "Inori",255, 0, 0.8f, 0.8f);
	//Engine::DrawRect(0, 0, 1000, 1000, 0x000000, FadeIn);
	//ボタンの状態変化
	//Engine::DrawTextureUV(100.0f, 400.0f, "StartButton", 0.0f, 128.0f, 256.0f, 128.0f);

	Engine::LoadTexture("Map", "Res/MapChip.png");

	UpdateCamara();

	DrawBg();
	
	int start_mapchip_pos = g_CameraX / 64;
	int end_mapchip_pos = start_mapchip_pos + STAGE_WIDTH /2;

	for (int i = start_mapchip_pos; i <= end_mapchip_pos; i++)
	{
		for (int j = 0; j < STAGE_HEIGHT; j++)
		{
			if (Map[j][i] == 0)
			{
				continue;
			}

			tex_pos.X = Map[j][i] % 4 * chip_size.X;
			tex_pos.Y = Map[j][i] / 4 * chip_size.Y;

			pos = Vec2(i * chip_size.X - g_CameraX, j * chip_size.Y);
			
			Engine::DrawTextureUV(pos.X, pos.Y, "Map", tex_pos.X, tex_pos.Y, chip_size.X, chip_size.Y, 255);
		}
	}

//移動処理
	if (Engine::IsKeyboardKeyHeld(DIK_RIGHTARROW))
	{
		vector.X = speed;
	}
	if (Engine::IsKeyboardKeyHeld(DIK_LEFTARROW))
	{	
		vector.X = -speed;
	}
	if (Engine::IsKeyboardKeyPushed(DIK_A)&&g_IsGround)
	{
			StartJump();
			g_IsGround = false;
	}
	if (g_IsGround==false)
	{
		UpdateJump(vector.Y,Vec2(g_Objpos.X-g_OldObjPos.X, g_Objpos.Y - g_OldObjPos.Y));
	}

	vector.Y += Gravity;

	slide = (current - min) / (max - min);

	current++;
	if (current >= max)
	{
		IsDraw = false;
		Engine::DrawTexture(0, 0, "GameOver");
		if (Engine::IsKeyboardKeyPushed(DIK_RETURN))
		{
			
			//Engine::DrawFont(300, 200, "PushEnter", FontSize::Large, FontColor::White);
			g_SceneKind = SceneKind::TitleScene;
			current = 0;
		}
	}

	Texture* tex = Engine::GetTexture("Enemy");
	Vec2 size = Vec2(tex->Width, tex->Height);

	
	if (CheckGoal(Vec2(g_Objpos.X+vector.X, g_Objpos.Y + vector.Y), Vec2(Player_Size, Player_Size)) == true)
	{
		Engine::DrawTexture(0, 0, "GameOver");
		g_SceneStep = SceneStep::Finish;
	}

	RectF rect{
	g_Objpos.Y,
	g_Objpos.Y + Player_Size,
	g_Objpos.X,
	g_Objpos.X + Player_Size,
	};

	EdgeType contact_edge = EdgeType::EdgeTypeNon;
	float contact_pos = 0.f;
	//PlayerとMapchipが当たっていなければ
	if(CollisionRectAndMapChipEdge(rect,Vec2(vector.X,0.f), contact_edge, contact_pos) ==false)
	{
		g_Objpos.X += vector.X;
	}
	else
	{
		switch (contact_edge)
		{
		case EdgeType::EdgeTypeLeft: 
			g_Objpos.X = contact_pos - Player_Size;
			break;
		case EdgeType::EdgeTypeRight:
			g_Objpos.X = contact_pos;
			break;
		}
	}

	if (CollisionRectAndMapChipEdge(rect, Vec2(0.f,vector.Y), contact_edge, contact_pos) == false)
	{
		g_Objpos.Y += vector.Y;
		g_IsGround = false;
	}
	else
	{
		switch (contact_edge)
		{
		case EdgeType::EdgeTypeTop:
			g_Objpos.Y = contact_pos - Player_Size;
			g_IsGround = true;
			break;
		case EdgeType::EdgeTypeBottom:
			g_Objpos.Y = contact_pos;
			break;
		}
	}
	

	g_OldObjPos = g_Objpos;

	FadeIn -= 1;

	if (FadeIn <= 0)
	{
		FadeIn = 0;
	}

	/*if (Engine::IsKeyboardKeyPushed(DIK_Z))
	{
		if (FadeIn <= 0)
		{
			FadeIn = 255;

			g_SceneKind = SceneKind::TitleScene;
			g_SceneStep = SceneStep::Init;
		}	
	}*/

	if (Engine::IsKeyboardKeyHeld(DIK_W))
	{
		g_SceneStep = SceneStep::Finish;

		FadeIn = 255;
	}

	if (IsDraw)
	{
		Engine::DrawTexture(g_Objpos.X - g_CameraX, g_Objpos.Y, "Enemy", 255);
		//制限時間用スライダー
		Engine::DrawRect(0, 0, 640 * slide, 50, 0x0000ff, 128);
		//制限時間（入れ物）
		Engine::DrawRect(0, 0, 640, 50, 0xffffff, 64);
		Engine::DrawFont(225, 0, "制限時間30秒", FontSize::Large, FontColor::Black);
	}
}

//ゲームシーン終了
void FinishGameScene()
{
	Engine::Update();

	slide = 0;	
	current = 0;
	

		// ステップをInitに変更(次のシーンのための初期化)
		g_SceneStep = SceneStep::Init;

		// SceneKindを変更したい種類に変更する
		g_SceneKind = SceneKind::ResultScene;
	
}