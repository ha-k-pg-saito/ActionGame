#ifndef Jump_h_
#define Jump_h_

#include"Src/Engine/Engine.h"

//�d��
static float Gravity = 1.0f;

void StartJump();
void UpdateJump(float& y,Vec2 movevector);


#endif