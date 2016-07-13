#include "GameScene.h"

USING_NS_CC;

bool GameScene::init()
{
	auto layer = GameLayer::create();
	this->addChild(layer);
	return true;
}