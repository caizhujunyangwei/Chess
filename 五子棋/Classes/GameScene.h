

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

	int canWin(Chess* chess,int x,int y); //1黑   0白

	void WinGame(int result);   //胜利结果

private:
	virtual bool onTouchBegan(Touch* t, Event* e);
	virtual void onTouchEnded(Touch* t, Event* e);

private:
	int m_col;   //列
	int m_row;   //行
	int m_guide;  //1 黑子 0白子

	vector<vector<Chess*>> m_chessBox;
};
#endif // !__GAMESCENE__H__