#include "GameLayer.h"
#include <stdlib.h>
#include <ctime>

USING_NS_CC;

bool GameLayer::init()
{
	index = 0;
	upIndex = 0;
	gotScore = true;
	score = 0;

	auto animation = Animation::create();
	for(int i = 1; i <= 3; i++) {
		char str[50];
		sprintf(str, "bird_%d@2x.png", i);
		animation->addSpriteFrameWithFileName(str); //添加动画帧
	}

	//设置属性
	animation->setRestoreOriginalFrame(true); //还原第一帧
	animation->setDelayPerUnit(1.0 / 3.0);     //单位帧间隔
	animation->setLoops(-1);                  //-1无限循环
	animate = Animate::create(animation);
	animate->retain();

	addBg();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	return true;
}

void GameLayer::addBg()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->bg1 = Sprite::create("back@2x.png");
	this->bg1->setAnchorPoint(Vec2(0, 0));
	this->bg1->setPosition(0, 0);
	this->addChild(this->bg1);

	this->bg2 = Sprite::create("back@2x.png");
	this->bg2->setAnchorPoint(Vec2(0, 0));
	this->bg2->setPosition(visibleSize.width, 0);
	this->addChild(this->bg2);

	bird = Sprite::create("bird_1@2x.png");
	
	this->addChild(bird);
	bird->setLocalZOrder(20);

	std::srand(std::time(0));
	float bottomHeight = rand_0_1() * 600 + 200;
	float inter = rand_0_1() * (visibleSize.height - bottomHeight - 100) + bottomHeight;

	pipe_bottom = Sprite::create("pipe_bottom@2x.png");
	pipe_bottom->setAnchorPoint(Vec2(0, 1));
	pipe_bottom->setLocalZOrder(15);
	this->addChild(pipe_bottom);
	
	pipe_top = Sprite::create("pipe_top@2x.png");
	pipe_top->setAnchorPoint(Vec2(0, 0));
	pipe_top->setLocalZOrder(15);
	this->addChild(pipe_top);

	scoreLabel = Label::createWithTTF("score : 0", "fonts/Marker Felt.ttf", 40);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2.0f, 900));
	this->addChild(scoreLabel, 100);

	for(int i = 0; i < 3; i++)
	{
		auto ground = Sprite::create("floor@2x.png");
		ground->setAnchorPoint(Vec2(0, 0));
		ground->setPosition(i * ground->getBoundingBox().size.width, 0);
		ground->setLocalZOrder(10);
		this->addChild(ground);
		grounds.pushBack(ground);
	}
 	start();
}

void GameLayer::start()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float bottomHeight = rand_0_1() * 600 + 200;
	float topHeight = bottomHeight + 180 + rand_0_1() * (visibleSize.height - bottomHeight - 200);
	pipe_bottom->setPositionX(visibleSize.width);
	pipe_bottom->setPositionY(bottomHeight);
	pipe_top->setPositionX(visibleSize.width);
	pipe_top->setPositionY(topHeight);
	scoreLabel->setString("score : 0");
	bird->setPosition(visibleSize / 2.0f);
	upIndex = 0;
	bird->runAction(animate);
	scheduleUpdate();

	auto menu = this->getChildByName("menu");
	if(menu)
		menu->removeFromParent();
}

void GameLayer::moveBg(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int delta = 5;
	bg1->setPositionX(bg1->getPositionX() - delta);
	bg2->setPositionX(bg2->getPositionX() - delta);
	if (bg1->getPositionX() <= (-1) * visibleSize.width)
		bg1->setPositionX(visibleSize.width);
	if (bg2->getPositionX() <= (-1) * visibleSize.width)
		bg2->setPositionX(visibleSize.width);
}

void GameLayer::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int delta = 4;
	bg1->setPositionX(bg1->getPositionX() - delta);
	bg2->setPositionX(bg2->getPositionX() - delta);
	if (bg1->getPositionX() <= (-1) * visibleSize.width)
		bg1->setPositionX(visibleSize.width);
	if (bg2->getPositionX() <= (-1) * visibleSize.width)
		bg2->setPositionX(visibleSize.width);
	for (auto ground : grounds)
	{
		ground->setPositionX(ground->getPositionX() - delta);
		if (ground->getPositionX() <= (-1) * (616*3 - visibleSize.width))
			ground->setPositionX(visibleSize.width); 
	}
	if (upIndex > 0)
	{
		bird->setPositionY(bird->getPositionY() + 15);
		--upIndex;
	}
	else
		bird->setPositionY(bird->getPositionY() - 4);
	float pos = pipe_bottom->getPositionX() - delta;
	 
	if(bird->getPositionX() > pos && gotScore)
	{
		score++;
		CCLOG("score = %d", score);
		auto ss = __String::createWithFormat("score : %d", score);
		scoreLabel->setString(ss->getCString());
		gotScore = false;
	}

	pipe_bottom->setPositionX(pos);
	pipe_top->setPositionX(pos);
	if (pos <= (-1) * pipe_bottom->getBoundingBox().size.width)
	{
		pipe_bottom->setPositionX(visibleSize.width);
		pipe_top->setPositionX(visibleSize.width);
		float bottomHeight = rand_0_1() * 600 + 200;
		float topHeight = bottomHeight + 180 + rand_0_1() * (visibleSize.height - bottomHeight - 200);
		pipe_bottom->setPositionY(bottomHeight);
		pipe_top->setPositionY(topHeight);
		gotScore = true;
	}
	if (collision())
	{
		CCLOG("ouch get hurt!!!!!!!!!!");
		unscheduleUpdate();
		bird->stopAllActions();
		bird->runAction(MoveBy::create(0.5f, Vec2(0, bird->getPositionY() * -1 + 10)));

		auto closeItem = MenuItemImage::create(
			"restart.png",
			"restart.png",
			CC_CALLBACK_0(GameLayer::start, this));
		closeItem->setPosition(Vec2(visibleSize.width / 2.0f , 200));
		closeItem->setScale(0.6);
		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 200, "menu");
	}

	
}

bool GameLayer::collision()
{
	auto bir = bird->getBoundingBox();
	auto r1 = pipe_bottom->getBoundingBox();
	auto r2 = pipe_top->getBoundingBox();
	return bir.intersectsRect(r1) || bir.intersectsRect(r2) || bir.getMinY() < 0 || bir.getMaxY() > 1136;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	upIndex = 10;
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event) {}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event) {}