#ifndef __PHYSICALSPRITE_H__
#define __PHYSICALSPRITE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class PhysicalSprite : public Sprite
{
public:
    PhysicalSprite();

	void setPhysicalBody(b2Body* body);
	int hp;

	CREATE_FUNC(PhysicalSprite);

private:
	b2Body* m_body;

    virtual bool init();
       
    // implement the "static create()" method manually
    

};

#endif // __PHYSICALSPRITE_H__
