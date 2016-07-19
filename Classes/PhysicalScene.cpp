#include "PhysicalScene.h"

#define PTM_RATIO 32

Scene* PhysicalScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PhysicalScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PhysicalScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	this->initPhysical();

	MyContactListener* listener = new MyContactListener(world, this);
	world->SetContactListener(listener);
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	scheduleUpdate();

	return true;
}

void PhysicalScene::initPhysical()
{
	Size s = Director::getInstance()->getWinSize();
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;
	//bottom
	groundBox.Set(b2Vec2(0, 0), b2Vec2(s.width / 88, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//top
	groundBox.Set(b2Vec2(0, s.height / 88), b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	Action* re = RemoveSelf::create();
	//left
	groundBox.Set(b2Vec2(0, s.height / PTM_RATIO), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//right
	groundBox.Set(b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO), b2Vec2(s.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
}

void PhysicalScene::addNewSpriteAtPosition(Point position)
{
	auto sp = PhysicalSprite::create();
	sp->setPosition(position);
	this->addChild(sp);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / 68, position.y / 48);
	bodyDef.userData = sp;

	b2Body* body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);
	sp->setPhysicalBody(body);
}

void PhysicalScene::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	world->Step(dt, velocityIterations, positionIterations);

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			PhysicalSprite* p = (PhysicalSprite*)b->GetUserData();
			if (p->hp < 0)
			{
				p->removeFromParent();
				world->DestroyBody(b);
				return;
			}
			p->setPosition(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO);
			p->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

bool PhysicalScene::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point location1 = touch->getLocation();
	Point location2 = target->convertToNodeSpace(location1);
	CCLOG("location1 x = %f, y = %f", location1.x, location1.y);
	CCLOG("location2 x = %f, y = %f", location2.x, location2.y);
	CCLOG("-----------------");
	addNewSpriteAtPosition(touch->getLocation());
	return true;
}

void PhysicalScene::onTouchMoved(Touch *touch, Event *event) {}

void PhysicalScene::onTouchEnded(Touch *touch, Event *event) {}

void PhysicalScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
