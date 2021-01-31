#ifndef Mapchip_h_
#define Mapchip_h_

#include"Src/Engine/Engine.h"
#include"Rect.h"

//constは初期化後値変更不可能になる
const int STAGE_HEIGHT = 8;
const int STAGE_WIDTH = 20;
const int Chip_Size = 64;

enum EdgeType
{
	EdgeTypeNon = -1,		//無し
	EdgeTypeLeft,			//左
	EdgeTypeRight,			//右
	EdgeTypeTop,			//上
	EdgeTypeBottom,			//下
	EdgeTypeMax				//最大
};

extern int Map[STAGE_HEIGHT][STAGE_WIDTH];

bool CheckGoal(Vec2 obj_pos, Vec2 obj_size);

//プロトタイプ宣言
bool CollisionRectAndMapChipEdge(RectF &rect,Vec2 vector,EdgeType &contact_edge,float &contact_edge_position);

#endif
