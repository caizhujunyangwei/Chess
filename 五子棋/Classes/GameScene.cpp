#include "Head.h"



Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto WinSize = Director::getInstance()->getWinSize();

	m_col = CHESS_COL;
	m_row = CHESS_ROW;
	m_guide = 1;

	//*��ʼ��һ������
	m_chessBox.resize(m_col);
	for (auto &vec : m_chessBox)
	{
		vec.resize(m_row);
	}

	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			m_chessBox[x][y] = nullptr;
		}
	}

	//���ر���
	auto background = Sprite::create("ChessPan.jpg");
	background->setPosition(Vec2(WinSize.width / 2, WinSize.height / 2));
	addChild(background, -1);

	//�¼�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::createChess(int x, int y)
{
	Chess* pRet = nullptr;
	switch (m_guide)
	{
	case 1:
		pRet = Chess::createAChess(1, x, y);
		break;
	case 0:
		pRet = Chess::createAChess(0, x, y);
		break;
	default:
		return;
	}
	m_guide = abs(m_guide - 1);

	pRet->setPosition(Vec2(x*CHESS_WIDTH + 26, y*CHESS_WIDTH + 26));
	m_chessBox[x][y] = pRet;

	addChild(pRet);


	auto result = canWin(pRet, x, y);   //�������Ƿ��ʤ
	WinGame(result);
}

bool GameScene::onTouchBegan(Touch * t, Event * e)
{
	auto pos = convertToNodeSpace(t->getLocation());
	int x = (pos.x - 6) / CHESS_WIDTH;
	int y = (pos.y - 6) / CHESS_WIDTH;

	if (m_chessBox[x][y] != nullptr)
	{
		return false;
	}
	return true;
}

void GameScene::onTouchEnded(Touch * t, Event * e)
{
	auto pos = convertToNodeSpace(t->getLocation());
	int x = (pos.x - 6) / CHESS_WIDTH;
	int y = (pos.y - 6) / CHESS_WIDTH;

	createChess(x, y);
}


int GameScene::canWin(Chess* chess,int x,int y)
{
	int n = 0;   // 1���� ��ͬ��
	int i = 0;    //2���� ��ͬ��

	Chess* NextChess = nullptr;

	//�� ���
	if (y >0)  //����
	{
		n = 1;
		NextChess = m_chessBox[x][y-1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				n++;
				int index = y - n;
				if (index < 0)
				{
					break;
				}
				NextChess = m_chessBox[x][index];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (y < m_row - 1)//����
	{
		i = 1;
		NextChess = m_chessBox[x][y + 1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				i++;
				int index = y + i;
				if (index > m_row-1)
				{
					break;
				}
				NextChess = m_chessBox[x][index];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (i + n > 5)
	{
		return (chess->getType());
	}
	//



	//�� ���
	n = i = 0;
	if (x > 0)//�� ��
	{
		n = 1;
		NextChess = m_chessBox[x - 1][y];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				n++;
				int index = x - n;
				if (index < 0)
				{
					break;
				}
				NextChess = m_chessBox[index][y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (x < m_col - 1)//�� ��
	{
		i = 1;
		NextChess = m_chessBox[x + 1][y];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				i++;
				int index = x + i;
				if (index > m_col - 1)
				{
					break;
				}
				NextChess = m_chessBox[index][y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (i + n > 5)
	{
		return (chess->getType());
	}
	//

	// ��б���
	n = i = 0;
	if (x > 0 && y < m_row - 1)   //б��
	{
		n = 1;
		NextChess = m_chessBox[x - 1][y + 1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				n++;
				int index_x = x - n;
				int index_y = y + n;
				if (index_x<0 || index_y>m_row - 1)
				{
					break;
				}
				NextChess = m_chessBox[index_x][index_y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (x < m_col - 1 && y>0) // б��
	{
		i = 1;
		NextChess = m_chessBox[x + 1][y - 1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				i++;
				int index_x = x + i;
				int index_y = y - i;
				if (index_x > m_col - 1 || index_y < 0)
				{
					break;
				}
				NextChess = m_chessBox[index_x][index_y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (i + n > 5)
	{
		return (chess->getType());
	}
	//

	//��б
	i = n = 0;
	if (x < m_col - 1 && y < m_row - 1)//б ��
	{
		n = 1;
		NextChess = m_chessBox[x + 1][y + 1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				n++;
				int index_x = x + n;
				int index_y = y + n;
				if (index_x > m_col - 1 || index_y>m_row - 1)
				{
					break;
				}
				NextChess = m_chessBox[index_x][index_y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (x > 0 && y > 0) //б��
	{
		i = 1;
		NextChess = m_chessBox[x - 1][y - 1];
		if (NextChess)
		{
			while (chess->getType() == NextChess->getType())
			{
				i++;
				int index_x = x - i;
				int index_y = y - i;
				if (index_x < 0 || index_y < 0)
				{
					break;
				}
				NextChess = m_chessBox[index_x][index_y];
				if (!NextChess)
				{
					break;
				}
			}
		}
	}

	if (i + n > 5)
	{
		return (chess->getType());
	}
	//


	return -1;
}



void GameScene::WinGame(int result)
{
	if (result == -1)
	{
		return;
	}

	_eventDispatcher->pauseEventListenersForTarget(this);

	char text[20] = { 0 };
	if (result == 1)
	{
		sprintf(text, "Black Win!");
	}
	else if (result == 0)
	{
		sprintf(text, "White Win!");
	}

	log("%s", text);


	auto delay = DelayTime::create(2);
	auto call = CallFunc::create([]() {
		Director::getInstance()->replaceScene(
			TransitionFade::create(1.0f, GameScene::createScene()));
	});
	runAction(Sequence::create(delay, call, nullptr));
}
