#include"Mapchip.h"

int Map[STAGE_HEIGHT][STAGE_WIDTH] =
{
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1},
	{1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,2,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void Clamp(int* value, int min, int max)
{
	if (*value<min)
	{
		*value = min;
	}
	else if (*value >max)
	{
		*value = max;
	}
}

//(�ړ��O�̋�`���,�ړ��x�N�g��,���������ӂ�Ԃ�����(in out),�����������W)
//�ړ��O�̋�`���
bool CollisionRectAndMapChipEdge(RectF& src_rect, Vec2 vector, EdgeType& contact_edge, float& contact_edge_position)
{
	RectF rect = src_rect;
	rect.Bottom += vector.Y;
	rect.Top    += vector.Y;
	rect.Right  += vector.X;
	rect.Left   += vector.X;

	//�T�C�Y����
	rect.Right  -= 1;		
	rect.Bottom -= 1;

	//��`��X���͈̔�
	int width_range_ids[]
	{
		 (int)(rect.Left / Chip_Size),
		 (int)(rect.Right / Chip_Size),
	};

	//��`��Y���͈̔�
	int height_range_ids[]
	{
		 (int)(rect.Top    / Chip_Size),
		 (int)(rect.Bottom / Chip_Size),
	};

	for (int i=0;i<2;i++)
	{
		//�X�e�[�W�Ɏ��߂�
		Clamp(&width_range_ids[i], 0, STAGE_WIDTH - 1);
		Clamp(&height_range_ids[i], 0, STAGE_HEIGHT - 1);
	}

	const int start = 0;
	const int end   = 1;

	Vec2I edge_list[EdgeType::EdgeTypeMax][2]
	{
		//����
		{			
			Vec2I(width_range_ids[start],height_range_ids[start]),
			Vec2I(width_range_ids[start],height_range_ids[end]),
		},
		//�E��
		{
			Vec2I(width_range_ids[end],height_range_ids[start]),
			Vec2I(width_range_ids[end],height_range_ids[end]),
		},
		//��
		{
			Vec2I(width_range_ids[start],height_range_ids[start]),
			Vec2I(width_range_ids[end],height_range_ids[start]),
		},
		//��
		{
			Vec2I(width_range_ids[start],height_range_ids[end]),
			Vec2I(width_range_ids[end],height_range_ids[end]),
		},
	};

	bool is_use_edge_list[EdgeType::EdgeTypeMax]
	{
		//�O�����Z�q
		vector.X < 0.0f ? true : false,
		vector.X > 0.0f ? true : false,
		vector.Y < 0.0f ? true : false,
		vector.Y > 0.0f ? true : false
	};

	for (int i = 0; i < EdgeType::EdgeTypeMax; i++)
	{
		if (is_use_edge_list[i]==false)
		{
			continue;
		}

		for (int y = edge_list[i][start].Y; y <= edge_list[i][end].Y; y++)
		{
			for (int x = edge_list[i][start].X; x <= edge_list[i][end].X; x++)
			{
				if (Map[y][x] != 0)
				{
					Vec2 chip_pos = Vec2((float)x * Chip_Size,(float)y * Chip_Size);
					switch((EdgeType)i)
					{
						//�i�s�����̋t�Ɉ�ԋ߂��Ƃ���̂����蔻��
					case EdgeType::EdgeTypeLeft: 
						contact_edge = EdgeType::EdgeTypeRight;
						contact_edge_position = chip_pos.X + Chip_Size;
						break;
					case EdgeType::EdgeTypeRight:
						contact_edge = EdgeType::EdgeTypeLeft;
						contact_edge_position = chip_pos.X;
						break;
					case EdgeType::EdgeTypeTop:
						contact_edge = EdgeType::EdgeTypeBottom;
						contact_edge_position = chip_pos.Y + Chip_Size;
						break;
					case EdgeType::EdgeTypeBottom:
						contact_edge = EdgeType::EdgeTypeTop;
						contact_edge_position = chip_pos.Y;
						break;
					}
					return true;
				}
			}
		}

	}

	return false;
}

bool CheckGoal(Vec2 obj_pos, Vec2 obj_size)
{
	Vec2 vertices[] =
	{
		obj_pos,													//����
		Vec2(obj_pos.X + obj_size.X,obj_pos.Y),						//�E��
		Vec2(obj_pos.X + obj_size.X,obj_pos.Y + obj_size.Y),		//�E��
		Vec2(obj_pos.X ,obj_pos.Y + obj_size.Y),					//����
	};

	int vertex_mapchip_ids_w[4];
	int vertex_mapchip_ids_h[4];

	for (int i = 0; i < 4; i++)
	{
		vertex_mapchip_ids_w[i] = vertices[i].X / Chip_Size;
		vertex_mapchip_ids_h[i] = vertices[i].Y / Chip_Size;
	}

	for (int i = 0; i < 4; i++)
	{
		int w = vertex_mapchip_ids_w[i];
		int h = vertex_mapchip_ids_h[i];
		if (Map[h][w] == 2)
		{
			return true;
		}
	}
	return false;
}