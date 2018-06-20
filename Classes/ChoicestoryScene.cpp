#include "ChoicestoryScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "FightScene.h"

USING_NS_CC;

Scene* ChoicestoryScene::createScene()
{
	return ChoicestoryScene::create();
}

bool ChoicestoryScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	voidNode = Layer::create();
	this->addChild(voidNode);

	// 스토리 선택 레이어
	cground = Sprite::create("Images/choicestory.png");
	cground->setAnchorPoint(Vec2::ZERO);
	cground->setPosition(Vec2(0, 0));
	voidNode->addChild(cground);

	auto BACKItem = MenuItemImage::create(
		"Images/backbutton.png",
		"Images/backbutton.png",
		CC_CALLBACK_1(ChoicestoryScene::clickback, this));

	auto chap1Item = MenuItemImage::create(
		"Images/chap1.png",
		"Images/chap1-2.png",
		CC_CALLBACK_1(ChoicestoryScene::clickchap1, this));

	auto chap2Item = MenuItemImage::create(
		"Images/chap2.png",
		"Images/chap2-2.png",
		CC_CALLBACK_1(ChoicestoryScene::clickchap2, this));

	auto chap3Item = MenuItemImage::create(
		"Images/chap3.png",
		"Images/chap3-2.png",
		CC_CALLBACK_1(ChoicestoryScene::clickchap3, this));

	auto pMenu = Menu::create(chap1Item, chap2Item, chap3Item, nullptr);

	chap1Item->setScale(0.2f);
	chap2Item->setScale(0.2f);
	chap3Item->setScale(0.2f);

	pMenu->alignItemsVertically();
	pMenu->setPosition(Vec2(240,150));
	cground->addChild(pMenu);
	
	auto pback = Menu::create(BACKItem, nullptr);
	pback->alignItemsHorizontally();
	pback->setPosition(Vec2(450, 300));
	cground->addChild(pback);

	return true;
}

void ChoicestoryScene::clickback(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::create());
}

void ChoicestoryScene::clickchap1(Ref * pSender)
{
	Director::getInstance()->replaceScene(FightScene::create());
}

void ChoicestoryScene::clickchap2(Ref * pSender)
{
	Director::getInstance()->replaceScene(FightScene::create());
}

void ChoicestoryScene::clickchap3(Ref * pSender)
{
	Director::getInstance()->replaceScene(FightScene::create());
}
