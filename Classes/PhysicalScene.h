#ifndef __PHYSICAL_SCENE_H__
#define __PHYSICAL_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyContactListener.h"
#include "PhysicalSprite.h"

USING_NS_CC;

class PhysicalScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PhysicalScene);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	void update(float dt);
	void initPhysical();
	void addNewSpriteAtPosition(Point position);

private:
	b2World* world;
};

#endif // __PHYSICAL_SCENE_H__
