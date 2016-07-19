#include "PhysicalSprite.h"

bool PhysicalSprite::init()
{
	m_body = NULL;
	int idx = (rand_0_1() > 0.5 ? 0 : 1);
	int idy = (rand_0_1() > 0.5 ? 0 : 1);
	this->initWithFile("medal_bronze@2x.png");
	this->setAnchorPoint(Vec2(0.5, 1));
	hp = 5;

	return true;
}

PhysicalSprite::PhysicalSprite()
{
	
}

void PhysicalSprite::setPhysicalBody(b2Body* body)
{
	m_body = body;
}