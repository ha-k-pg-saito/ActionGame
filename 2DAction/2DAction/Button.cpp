#include"Button.h"
#include"Src/Common/Vec.h"
#include"Src/Engine/Engine.h"
#include"Src/Common/Size.h"

static Button g_Button;

bool Cursor()
{
	Vec2 mouse_pos = Engine::GetMousePos();
	Size button_size = Size(256.0f, 128.0f);

	if (/*g_Button.Position.X*/200 <= mouse_pos.X &&
		/*g_Button.Position.X*/200 + button_size.Width >= mouse_pos.X &&
		/*g_Button.Position.Y*/300 <= mouse_pos.Y &&
		/*g_Button.Position.Y*/300 + button_size.Height >= mouse_pos.Y)
	{
		return true;
	}
		
	return false;
}