#include"Result.h"
#include"enum.h"
#include"Src/Engine/Engine.h"

void UpdateResultScene()
{
	switch (g_SceneStep)
	{
	case SceneStep::Init:   InitResultScene();   break;
	case SceneStep::Run:    RunResultScene();    break;
	case SceneStep::Finish: FinishResultScene(); break;
	}
}

void InitResultScene()
{
	Engine::Update();
	
	g_SceneStep = SceneStep::Run;
}

void RunResultScene()
{
	Engine::Update();
	Engine::DrawTexture(0,0,"Result",255);
	
	if (Engine::IsKeyboardKeyPushed(DIK_RETURN))
	{
		g_SceneStep = SceneStep::Finish;
	}

}

void FinishResultScene()
{
	Engine::Update();
	
	/*g_SceneKind = SceneKind::TitleScene;
	g_SceneStep = SceneStep::Run;*/

	//if (Engine::IsKeyboardKeyHeld(DIK_A))
	{
		// ステップをInitに変更(次のシーンのための初期化)
		g_SceneStep = SceneStep::Init;

		// SceneKindを変更したい種類に変更する
		g_SceneKind = SceneKind::TitleScene;
	}
}

