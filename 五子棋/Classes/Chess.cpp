#include "Head.h"



Chess * Chess::createAChess(int type, int x, int y)
{
	auto chess = new Chess();
	if (chess && chess->init(type, x, y))
	{
		chess->autorelease();
		return chess;
	}
	else
	{
		CC_SAFE_DELETE(chess);
		return nullptr;
	}
}

bool Chess::init(int type, int x, int y)
{
	if (!Sprite::init())
	{
		return false;
	}

	m_type = type;
	m_x = x;
	m_y = y;

	Sprite* pRet = nullptr;

	switch (m_type)
	{
	case 1://ºÚ×Ó
		pRet = Sprite::create("Black.png");
		break;
	case 0://°××Ó
		pRet = Sprite::create("White.png");
		break;
	default:
		break;
	}
	addChild(pRet);

	return true;
}
