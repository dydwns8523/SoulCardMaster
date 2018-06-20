#include "titleScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* titleScene::createScene()
{
	return titleScene::create();
}

bool titleScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	voidNode = Layer::create();
	this->addChild(voidNode);

	// 스토리 선택 레이어
	cground = Sprite::create("Images/title2.png");
	cground->setAnchorPoint(Vec2::ZERO);
	cground->setPosition(Vec2(0, 0));
	voidNode->addChild(cground);

	auto startItem = MenuItemImage::create(
		"Images/gamestart.png",
		"Images/gamestart2.png",
		CC_CALLBACK_1(titleScene::clickstart, this));
	startItem->setScale(0.17f);
	

	auto pstart = Menu::create(startItem, nullptr);
	pstart->alignItemsHorizontally();
	pstart->setPosition(Vec2(230, 60));
	cground->addChild(pstart);

	return true;
}

void titleScene::clickstart(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::create());
}

