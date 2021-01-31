#ifndef Enum_H_
#define Enum_H_

extern enum SceneKind
{
	TitleScene,
	GameScene,
	ResultScene,
};

extern enum SceneStep
{
	Init,
	Run,
	Finish,
};

extern enum ButtonStatus
{
	Normal,
	Inactive,
	OnCursor,
	Clicked,
};

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;
extern ButtonStatus g_ButtonStatus;

#endif
