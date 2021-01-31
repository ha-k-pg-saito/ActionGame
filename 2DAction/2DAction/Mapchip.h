#ifndef Mapchip_h_
#define Mapchip_h_

#include"Src/Engine/Engine.h"
#include"Rect.h"

//const�͏�������l�ύX�s�\�ɂȂ�
const int STAGE_HEIGHT = 8;
const int STAGE_WIDTH = 20;
const int Chip_Size = 64;

enum EdgeType
{
	EdgeTypeNon = -1,		//����
	EdgeTypeLeft,			//��
	EdgeTypeRight,			//�E
	EdgeTypeTop,			//��
	EdgeTypeBottom,			//��
	EdgeTypeMax				//�ő�
};

extern int Map[STAGE_HEIGHT][STAGE_WIDTH];

bool CheckGoal(Vec2 obj_pos, Vec2 obj_size);

//�v���g�^�C�v�錾
bool CollisionRectAndMapChipEdge(RectF &rect,Vec2 vector,EdgeType &contact_edge,float &contact_edge_position);

#endif
