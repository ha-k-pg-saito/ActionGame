#include"enum.h"
#include"Update.h"

SceneKind g_SceneKind = SceneKind::TitleScene;
SceneStep g_SceneStep = SceneStep::Init;
ButtonStatus g_ButtonStatus = Normal;

void UpdateScene()
{
	switch (g_SceneKind)
	{
	case SceneKind::TitleScene:  UpdateTitleScene();   break;
	case SceneKind::GameScene:	 UpdateGameScene();    break;
	case SceneKind::ResultScene: UpdateResultScene();  break;
	}
}