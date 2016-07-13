#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameLayer);

public:
	Sprite* bg1;
	Sprite* bg2;
	Sprite* bird;
	Sprite* pipe_bottom;
	Sprite* pipe_top;
	int index;
	int upIndex;
	int score;
	Label* scoreLabel;
	bool gotScore;
	Animate* animate;
	Vector<Sprite*> grounds;

public:
	void addBg();
	void moveBg(float dt);
	void update(float dt);
	bool collision();
	void showScore();
	void start();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // __GAME_LAYER_H__
