#include"Jump.h"

//�X�s�[�h
static float Speed = 0.f;

void StartJump()
{
	Speed = 13.0f;
}

void UpdateJump(float& y,Vec2 movevector)
{
	y = movevector.Y - Speed;
	Speed -= Gravity;
}