#include "resultScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "PlayerData.h"
#include "GameManager.h"


USING_NS_CC;


Scene* resultScene::createScene()
{
	return resultScene::create();
}

bool resultScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	voidNode = Layer::create();
	this->addChild(voidNode);

	// 상태 결과창 레이어
	cground = Sprite::create("Images/resultScene.png");
	cground->setAnchorPoint(Vec2::ZERO);
	cground->setPosition(Vec2(0, 0));
	voidNode->addChild(cground);

	auto BACKItem = MenuItemImage::create(
		"Images/check.png",
		"Images/check2.png",
		CC_CALLBACK_1(resultScene::clickcheck, this));


	auto pback = Menu::create(BACKItem, nullptr);
	pback->alignItemsHorizontally();
	pback->setAnchorPoint(Vec2::ZERO);
	pback->setPosition(Vec2(245, 100));
	pback->setScale(0.15f);
	cground->addChild(pback);

	makebase();
	makeparticle();

	return true;
}

void resultScene::clickcheck(Ref * pSender)
{
	PlayerDeck* testDeck = GameManager::getInstance()->gettestDeck();
	testDeck[0].atk = 1;
	Director::getInstance()->replaceScene(HelloWorld::create());
}

void resultScene::makebase()
{
	srand((unsigned)time(NULL));
	getgold = 1500;
	sgold = "습득골드 : " + to_string(getgold);
	label = Label::create(sgold, "", 18);
	label->setColor(Color3B::YELLOW);
	label->setPosition(Vec2(270, 142));
	voidNode->addChild(label, 2);
	goldbar = Sprite::create("Images/goldbar.png");
	goldbar->setAnchorPoint(Vec2::ZERO);
	goldbar->setPosition(Vec2(150, 120));
	voidNode->addChild(goldbar, 1);
}

void resultScene::makeparticle()
{
	ParticleSystem * particle;
	particle = ParticleExplosion::create();
	particle->setScale(0.55f);
	particle->setDuration(0.5f);
	particle->setPosition(Vec2(130, 40));
	voidNode->addChild(particle);
	ParticleSystem * particle2;
	particle2 = ParticleExplosion::create();
	particle2->setScale(0.67f);
	particle2->setDuration(0.5f);
	particle2->setPosition(Vec2(420, 170));
	voidNode->addChild(particle2);
	ParticleSystem * particle3;
	particle3 = ParticleExplosion::create();
	particle3->setScale(0.23f);
	particle3->setDuration(0.5f);
	particle3->setPosition(Vec2(10, 150));
	voidNode->addChild(particle3);
	ParticleSystem * particle4;
	particle4 = ParticleExplosion::create();
	particle4->setScale(0.49f);
	particle4->setDuration(0.5f);
	particle4->setPosition(Vec2(300, 47));
	voidNode->addChild(particle4);
}
