

#ifndef __GAMESCENE__H__
#define __GAMESCENE__H__

#include "Chess.h"
#include <vector>
using namespace std;


class GameScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameScene);

private:
	void createChess(int x, int y);

	int canWin(Chess* chess,int x,int y); //1��   0��

	void WinGame(int result);   //ʤ�����

private:
	virtual bool onTouchBegan(Touch* t, Event* e);
	virtual void onTouchEnded(Touch* t, Event* e);

private:
	int m_col;   //��
	int m_row;   //��
	int m_guide;  //1 ���� 0����

	vector<vector<Chess*>> m_chessBox;
};
#endif // !__GAMESCENE__H__