#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Chess :public Sprite
{
public:
	static Chess* createAChess(int type, int x, int y);
	bool init(int type, int x, int y);


	int getType() { return m_type; }
	int getX() { return m_x; }
	int getY() { return m_y; }
private:
	int m_type;
	int m_x;
	int m_y;
};