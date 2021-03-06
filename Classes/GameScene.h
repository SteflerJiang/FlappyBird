#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

public:
	void setPhyWorld(PhysicsWorld* world) {m_world = world;}
	PhysicsWorld* m_world;
};

#endif // __GAME_SCENE_H__
