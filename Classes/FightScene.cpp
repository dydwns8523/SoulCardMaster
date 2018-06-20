#include "FightScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "Constans.h"
#include "resultScene.h"

USING_NS_CC;
using namespace std;

int turn;

Scene* FightScene::createScene()
{
	return FightScene::create();
}

bool FightScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	isDelay = false;
	isDelay2 = false;
	isDelay3 = false;
	isDelay4 = false;
	isDelay5 = false;
	isDelay6 = false;
	isDelay8 = false;

	voidNode = Layer::create();
	this->addChild(voidNode);
	voidNode2 = Layer::create();
	this->addChild(voidNode2);
	voidNode3 = Layer::create();
	this->addChild(voidNode3);
	voidNode4 = Layer::create();
	this->addChild(voidNode4);
	
	fground = Sprite::create("Images/chap1L.png");
	fground->setAnchorPoint(Vec2::ZERO);
	fground->setPosition(Vec2(0, 0));
	voidNode->addChild(fground);

	auto BItem2 = MenuItemImage::create(
		"Images/100backbutton.png",
		"Images/100backbutton.png",
		CC_CALLBACK_1(FightScene::clickB, this));

	// 전투 씬의 백버튼
	auto pSMenu5 = Menu::create(BItem2, nullptr);
	pSMenu5->alignItemsHorizontally();
	pSMenu5->setPosition(Vec2(20, 300));
	voidNode->addChild(pSMenu5);

	auto turnItem = MenuItemImage::create(
		"Images/turnover.png",
		"Images/turnover.png",
		CC_CALLBACK_1(FightScene::clickturn, this));

	auto pMenu = Menu::create(turnItem, nullptr);
	pMenu->alignItemsHorizontally();
	pMenu->setPosition(Vec2(430, 160));
	voidNode->addChild(pMenu);

	setFightDeck();

	playercost = 0;
	bosscost = 0;
	playerhp = 10;
	bosshp = 10;

	makebase();
	makeupdate();
	playerturn();
	
	this->schedule(schedule_selector(FightScene::callEveryFrame));

	return true;
}

void FightScene::makebase()
{

	auto pface = Sprite::create("Images/player.png");
	pface->setAnchorPoint(Vec2::ZERO);
	pface->setPosition(Vec2(420, 30));
	voidNode->addChild(pface);

	auto bface = Sprite::create("Images/chap1-b.png");
	bface->setAnchorPoint(Vec2::ZERO);
	bface->setPosition(Vec2(420, 270));
	voidNode->addChild(bface);

	pcost = Sprite::create("Images/cost.png");
	pcost->setAnchorPoint(Vec2::ZERO);
	pcost->setPosition(Vec2(420, 5));
	pcost->setScale(0.1f);
	voidNode->addChild(pcost);

	bcost = Sprite::create("Images/cost.png");
	bcost->setAnchorPoint(Vec2::ZERO);
	bcost->setPosition(Vec2(420, 245));
	bcost->setScale(0.1f);
	voidNode->addChild(bcost);

	php = Sprite::create("Images/heart.png");
	php->setAnchorPoint(Vec2::ZERO);
	php->setPosition(Vec2(365, 35));
	php->setScale(0.7f);
	voidNode->addChild(php);

	bhp = Sprite::create("Images/heart.png");
	bhp->setAnchorPoint(Vec2::ZERO);
	bhp->setPosition(Vec2(365, 245));
	bhp->setScale(0.7f);
	voidNode->addChild(bhp);

	auto sprite1 = Sprite::create("Images/basecard.png");
	sprite1->setAnchorPoint(Vec2::ZERO);
	sprite1->setPosition(Vec2(80, 280));
	voidNode->addChild(sprite1);

	auto sprite2 = Sprite::create("Images/basecard.png");
	sprite2->setAnchorPoint(Vec2::ZERO);
	sprite2->setPosition(Vec2(140, 280));
	voidNode->addChild(sprite2);

	auto sprite3 = Sprite::create("Images/basecard.png");
	sprite3->setAnchorPoint(Vec2::ZERO);
	sprite3->setPosition(Vec2(200, 280));
	voidNode->addChild(sprite3);

	auto sprite4 = Sprite::create("Images/basecard.png");
	sprite4->setAnchorPoint(Vec2::ZERO);
	sprite4->setPosition(Vec2(260, 280));
	voidNode->addChild(sprite4);

	auto sprite5 = Sprite::create("Images/basecard.png");
	sprite5->setAnchorPoint(Vec2::ZERO);
	sprite5->setPosition(Vec2(320, 280));
	voidNode->addChild(sprite5);
}

void FightScene::makeupdate()
{
	voidNode->removeChild(pLabel1, 1);
	voidNode->removeChild(pLabel2, 1);
	voidNode->removeChild(bLabel1, 1);
	voidNode->removeChild(bLabel2, 1);

	// 플레이어 코스트 라벨 생성
	p_cost = to_string(playercost);
	pLabel1 = Label::create(p_cost, "", 20);
	pLabel1->setColor(Color3B::BLUE);
	pLabel1->setPosition(Vec2(450, 17));
	voidNode->addChild(pLabel1);

	// 적군 코스트 라벨 생성
	b_cost = to_string(bosscost);
	bLabel1 = Label::create(b_cost, "", 20);
	bLabel1->setColor(Color3B::BLUE);
	bLabel1->setPosition(Vec2(450, 258));
	voidNode->addChild(bLabel1);

	// 플레이어 체력 라벨 생성
	p_hp = to_string(playerhp);
	pLabel2 = Label::create(p_hp, "", 20);
	pLabel2->setColor(Color3B::RED);
	pLabel2->setPosition(Vec2(405, 47));
	voidNode->addChild(pLabel2);

	// 적군 체력 라벨 생성
	b_hp = to_string(bosshp);
	bLabel2 = Label::create(b_hp, "", 20);
	bLabel2->setColor(Color3B::RED);
	bLabel2->setPosition(Vec2(405, 258));
	voidNode->addChild(bLabel2);
	
}

void FightScene::clickB(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::create());
}

void FightScene::clickturn(Ref * pSender)
{
	nNum = 0;
	nNum2 = 0;
	nNum3 = 0;
	nNum4 = 0;
	nNum5 = 0;
	nNum6 = 0;
	nNum8 = 0;
	pre++;
	for (int i = 0; i < 5; i++)
	{
	voidNode2->removeChild(HandMenu[i], 1);
	}
	bossturn();
	
}

void FightScene::playerturn()
{
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	PlayerDeck * FightDeck = GameManager::getInstance()->getFightDeck();

	// pre 는 cost 당 마나 증가 수
	playercost = pre + 11;
			
	for (int i = 0; i < 6; i++)
	{
		e_sprite[i] = Sprite::create("Images/basecard.png");
		e_sprite[i]->setAnchorPoint(Vec2::ZERO);
		e_sprite[i]->setPosition(Vec2(10 + PLUS3 * i, 80));
		voidNode3->addChild(e_sprite[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		m_sprite[i] = Sprite::create("Images/basecard.png");
		m_sprite[i]->setAnchorPoint(Vec2::ZERO);
		m_sprite[i]->setPosition(Vec2(10 + PLUS3 * i, 182));

		voidNode3->addChild(m_sprite[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		if (FightDeck[i].cname.c_str() != "")
		{
			HandDeck[i] = MenuItemImage::create(
				FightDeck[i].cname.c_str(),
				FightDeck[i].cname.c_str(),
				CC_CALLBACK_1(FightScene::clickHand, this, i, FightDeck[i].cost));
			HandMenu[i] = Menu::create(HandDeck[i], nullptr);
			HandDeck[i]->setAnchorPoint(Vec2::ZERO);
			HandDeck[i]->setPosition(Vec2(PLUS4 * i - 250, -200));
			voidNode4->addChild(HandMenu[i]);
		}
	}
		
	makeupdate();
}
void FightScene::bossturn()
{
	
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	PlayerDeck * FightDeck = GameManager::getInstance()->getFightDeck();
	voidNode3->removeChild(m_sprite[5], 1);
	m_sprite[0] = Sprite::create("Images/storefire/09.png");
	m_sprite[0]->setScale(0.8f);
	m_sprite[0]->setAnchorPoint(Vec2::ZERO);
	m_sprite[0]->setPosition(Vec2(400, 174));
	voidNode4->addChild(m_sprite[0]);

	fightturn();
}
void FightScene::fightturn()
{
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	PlayerDeck * FightDeck = GameManager::getInstance()->getFightDeck();

	char * str = "Images/basecard.png";

	// 플레이어 카드의 전투 대기 장소 이동
	patk1 = MoveTo::create(0.5f, Vec2(160, 124));

	// 보스 카드의 전투 대기 장소 이동
	patk2 = MoveTo::create(0.5f, Vec2(270, 124));

	// 플레이어 카드의 예비 전투 장소 이동
	patk3 = MoveTo::create(0.5f, Vec2(20, 124));
	patk4 = MoveTo::create(0.5f, Vec2(20, 104));
	patk5 = MoveTo::create(0.5f, Vec2(20, 84));
	patk6 = MoveTo::create(0.5f, Vec2(20, 64));

	// 전투후 아웃
	out = MoveTo::create(0.01f, Vec2(1000, 1000));

	// 보스 카드와 플레이어 카드의 전투 움직임
	fight = MoveTo::create(0.3f, Vec2(220, 124));

	batk = MoveTo::create(0.5f, Vec2(400, 200));

	delay = DelayTime::create(1.5f);
	pseq1 = Sequence::create(patk1, delay, fight, delay, out, NULL);
	pseq2 = Sequence::create(patk2, delay, fight, delay, out, NULL);
	pseq3 = Sequence::create(delay, delay, delay, batk, delay, out, NULL);
	pseq4 = Sequence::create(delay, delay, delay, delay, delay, batk, delay, out, NULL);
	pseq5 = Sequence::create(delay, delay, delay, delay, delay, delay, delay, batk, delay, out, NULL);
	pseq6 = Sequence::create(delay, delay, delay, delay, delay, delay, delay, delay, delay, batk, delay, out, NULL);

	int turn = 0;

	set = MoveTo::create(0.5f, Vec2(140, 124));
	atk = MoveTo::create(0.5f, Vec2(230, 124));

	voidNode3->removeAllChildren();

	int alive = 1;

	while (alive)
	{
		switch (turn)
		{
		case 0:
		{
			if (m_sprite[0]->getResourceName() != str)
			{
				e_sprite[0]->runAction(pseq1->clone());
				m_sprite[0]->runAction(pseq2->clone());
				isDelay8 = true;
				if (e_sprite[1]->getTextureAtlas() == NULL)
				{
					e_sprite[1]->runAction(patk3);
					isDelay2 = true;
				}
				if (e_sprite[2]->getTextureAtlas() == NULL)
				{
					e_sprite[2]->runAction(patk4);
					isDelay3 = true;
				}
				if (e_sprite[3]->getTextureAtlas() == NULL)
				{
					e_sprite[3]->runAction(patk5);
					isDelay4 = true;
				}
				if (e_sprite[4]->getTextureAtlas() == NULL)
				{
					e_sprite[4]->runAction(patk6);
					isDelay5 = true;
				}


			}
			turn++;
			break;
		}
		case 1:
		{

			if (e_sprite[1]->getTextureAtlas() == NULL)
			{
				e_sprite[1]->runAction(pseq3->clone());
			}
			if (e_sprite[2]->getTextureAtlas() == NULL)
			{
				e_sprite[2]->runAction(pseq4->clone());
			}
			if (e_sprite[3]->getTextureAtlas() == NULL)
			{
				e_sprite[3]->runAction(pseq5->clone());
			}
			if (e_sprite[4]->getTextureAtlas() == NULL)
			{
				e_sprite[4]->runAction(pseq6->clone());
			}
		}

		alive = 0;
		break;
		}
	}
	isDelay = true;
	
	for (int k = 0; k < PRE_DECK_MAX - 4 ; k++)
	{
		if (FightDeck[k].cname == "" && FightDeck[k + 1].cname != "")
		{
			FightDeck[k].numofcard = FightDeck[k + 1].numofcard;
			FightDeck[k].type = FightDeck[k + 1].type;
			FightDeck[k].cname = FightDeck[k + 1].cname;
			FightDeck[k].attribute = FightDeck[k + 1].attribute;
			FightDeck[k].grade = FightDeck[k + 1].grade;
			FightDeck[k].cost = FightDeck[k + 1].cost;
			FightDeck[k].atk = FightDeck[k + 1].atk;
			FightDeck[k].hp = FightDeck[k + 1].hp;
			FightDeck[k].sk1 = FightDeck[k + 1].sk1;
			FightDeck[k].sk2 = FightDeck[k + 1].sk2;
			FightDeck[k].sk3 = FightDeck[k + 1].sk3;
			FightDeck[k + 1].numofcard = 0;
			FightDeck[k + 1].type = 10;
			FightDeck[k + 1].cname = "";
			FightDeck[k + 1].attribute = 0;
			FightDeck[k + 1].grade = 0;
			FightDeck[k + 1].cost = 0;
			FightDeck[k + 1].atk = 0;
			FightDeck[k + 1].hp = 0;
			FightDeck[k + 1].sk1 = 0;
			FightDeck[k + 1].sk2 = 0;
			FightDeck[k + 1].sk3 = 0;
		}
		else if (FightDeck[k + 1].cname == "" && FightDeck[k + 2].cname != "")
		{
			FightDeck[k + 1].numofcard = FightDeck[k + 1 + 1].numofcard;
			FightDeck[k + 1].type = FightDeck[k + 1 + 1].type;
			FightDeck[k + 1].cname = FightDeck[k + 1 + 1].cname;
			FightDeck[k + 1].attribute = FightDeck[k + 1 + 1].attribute;
			FightDeck[k + 1].grade = FightDeck[k + 1 + 1].grade;
			FightDeck[k + 1].cost = FightDeck[k + 1 + 1].cost;
			FightDeck[k + 1].atk = FightDeck[k + 1 + 1].atk;
			FightDeck[k + 1].hp = FightDeck[k + 1 + 1].hp;
			FightDeck[k + 1].sk1 = FightDeck[k + 1 + 1].sk1;
			FightDeck[k + 1].sk2 = FightDeck[k + 1 + 1].sk2;
			FightDeck[k + 1].sk3 = FightDeck[k + 1 + 1].sk3;
			FightDeck[k + 1 + 1].numofcard = 0;
			FightDeck[k + 1 + 1].type = 10;
			FightDeck[k + 1 + 1].cname = "";
			FightDeck[k + 1 + 1].attribute = 0;
			FightDeck[k + 1 + 1].grade = 0;
			FightDeck[k + 1 + 1].cost = 0;
			FightDeck[k + 1 + 1].atk = 0;
			FightDeck[k + 1 + 1].hp = 0;
			FightDeck[k + 1 + 1].sk1 = 0;
			FightDeck[k + 1 + 1].sk2 = 0;
			FightDeck[k + 1 + 1].sk3 = 0;
			FightDeck[k].numofcard = FightDeck[k + 1].numofcard;
			FightDeck[k].type = FightDeck[k + 1].type;
			FightDeck[k].cname = FightDeck[k + 1].cname;
			FightDeck[k].attribute = FightDeck[k + 1].attribute;
			FightDeck[k].grade = FightDeck[k + 1].grade;
			FightDeck[k].cost = FightDeck[k + 1].cost;
			FightDeck[k].atk = FightDeck[k + 1].atk;
			FightDeck[k].hp = FightDeck[k + 1].hp;
			FightDeck[k].sk1 = FightDeck[k + 1].sk1;
			FightDeck[k].sk2 = FightDeck[k + 1].sk2;
			FightDeck[k].sk3 = FightDeck[k + 1].sk3;
			FightDeck[k + 1].numofcard = 0;
			FightDeck[k + 1].type = 10;
			FightDeck[k + 1].cname = "";
			FightDeck[k + 1].attribute = 0;
			FightDeck[k + 1].grade = 0;
			FightDeck[k + 1].cost = 0;
			FightDeck[k + 1].atk = 0;
			FightDeck[k + 1].hp = 0;
			FightDeck[k + 1].sk1 = 0;
			FightDeck[k + 1].sk2 = 0;
			FightDeck[k + 1].sk3 = 0;
		}
		else if (FightDeck[k + 2].cname == "" && FightDeck[k + 3].cname != "")
		{
			FightDeck[k + 1 + 1].numofcard = FightDeck[k + 1 + 1 + 1].numofcard;
			FightDeck[k + 1 + 1].type = FightDeck[k + 1 + 1 + 1].type;
			FightDeck[k + 1 + 1].cname = FightDeck[k + 1 + 1 + 1].cname;
			FightDeck[k + 1 + 1].attribute = FightDeck[k + 1 + 1 + 1].attribute;
			FightDeck[k + 1 + 1].grade = FightDeck[k + 1 + 1 + 1].grade;
			FightDeck[k + 1 + 1].cost = FightDeck[k + 1 + 1 + 1].cost;
			FightDeck[k + 1 + 1].atk = FightDeck[k + 1 + 1 + 1].atk;
			FightDeck[k + 1 + 1].hp = FightDeck[k + 1 + 1 + 1].hp;
			FightDeck[k + 1 + 1].sk1 = FightDeck[k + 1 + 1 + 1].sk1;
			FightDeck[k + 1 + 1].sk2 = FightDeck[k + 1 + 1 + 1].sk2;
			FightDeck[k + 1 + 1].sk3 = FightDeck[k + 1 + 1 + 1].sk3;
			FightDeck[k + 1 + 1 + 1].numofcard = 0;
			FightDeck[k + 1 + 1 + 1].type = 10;
			FightDeck[k + 1 + 1 + 1].cname = "";
			FightDeck[k + 1 + 1 + 1].attribute = 0;
			FightDeck[k + 1 + 1 + 1].grade = 0;
			FightDeck[k + 1 + 1 + 1].cost = 0;
			FightDeck[k + 1 + 1 + 1].atk = 0;
			FightDeck[k + 1 + 1 + 1].hp = 0;
			FightDeck[k + 1 + 1 + 1].sk1 = 0;
			FightDeck[k + 1 + 1 + 1].sk2 = 0;
			FightDeck[k + 1 + 1 + 1].sk3 = 0;
			FightDeck[k + 1].numofcard = FightDeck[k + 1 + 1].numofcard;
			FightDeck[k + 1].type = FightDeck[k + 1 + 1].type;
			FightDeck[k + 1].cname = FightDeck[k + 1 + 1].cname;
			FightDeck[k + 1].attribute = FightDeck[k + 1 + 1].attribute;
			FightDeck[k + 1].grade = FightDeck[k + 1 + 1].grade;
			FightDeck[k + 1].cost = FightDeck[k + 1 + 1].cost;
			FightDeck[k + 1].atk = FightDeck[k + 1 + 1].atk;
			FightDeck[k + 1].hp = FightDeck[k + 1 + 1].hp;
			FightDeck[k + 1].sk1 = FightDeck[k + 1 + 1].sk1;
			FightDeck[k + 1].sk2 = FightDeck[k + 1 + 1].sk2;
			FightDeck[k + 1].sk3 = FightDeck[k + 1 + 1].sk3;
			FightDeck[k + 1 + 1].numofcard = 0;
			FightDeck[k + 1 + 1].type = 10;
			FightDeck[k + 1 + 1].cname = "";
			FightDeck[k + 1 + 1].attribute = 0;
			FightDeck[k + 1 + 1].grade = 0;
			FightDeck[k + 1 + 1].cost = 0;
			FightDeck[k + 1 + 1].atk = 0;
			FightDeck[k + 1 + 1].hp = 0;
			FightDeck[k + 1 + 1].sk1 = 0;
			FightDeck[k + 1 + 1].sk2 = 0;
			FightDeck[k + 1 + 1].sk3 = 0;
			FightDeck[k].numofcard = FightDeck[k + 1].numofcard;
			FightDeck[k].type = FightDeck[k + 1].type;
			FightDeck[k].cname = FightDeck[k + 1].cname;
			FightDeck[k].attribute = FightDeck[k + 1].attribute;
			FightDeck[k].grade = FightDeck[k + 1].grade;
			FightDeck[k].cost = FightDeck[k + 1].cost;
			FightDeck[k].atk = FightDeck[k + 1].atk;
			FightDeck[k].hp = FightDeck[k + 1].hp;
			FightDeck[k].sk1 = FightDeck[k + 1].sk1;
			FightDeck[k].sk2 = FightDeck[k + 1].sk2;
			FightDeck[k].sk3 = FightDeck[k + 1].sk3;
			FightDeck[k + 1].numofcard = 0;
			FightDeck[k + 1].type = 10;
			FightDeck[k + 1].cname = "";
			FightDeck[k + 1].attribute = 0;
			FightDeck[k + 1].grade = 0;
			FightDeck[k + 1].cost = 0;
			FightDeck[k + 1].atk = 0;
			FightDeck[k + 1].hp = 0;
			FightDeck[k + 1].sk1 = 0;
			FightDeck[k + 1].sk2 = 0;
			FightDeck[k + 1].sk3 = 0;
		}
	}

	// TODO : 플레이어와 보스의 체력을 체크하여 둘중 하나라도 0이하가 되면 게임 종료후 씬전환
	isDelay = true;
}


void FightScene::gameclear()
{
	Director::getInstance()->replaceScene(resultScene::create());
}

void FightScene::setFightDeck()
{
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	PlayerDeck * FightDeck = GameManager::getInstance()->getFightDeck();
	for (int i = 0; i < PRE_DECK_MAX; i++)
	{
		FightDeck[i].numofcard = PreDeck[i].numofcard;
		FightDeck[i].type = PreDeck[i].type;
		FightDeck[i].cname = PreDeck[i].cname.c_str();
		FightDeck[i].attribute = PreDeck[i].attribute;
		FightDeck[i].grade = PreDeck[i].grade;
		FightDeck[i].cost = PreDeck[i].cost;
		FightDeck[i].atk = PreDeck[i].atk;
		FightDeck[i].hp = PreDeck[i].hp;
		FightDeck[i].sk1 = PreDeck[i].sk1;
		FightDeck[i].sk2 = PreDeck[i].sk2;
		FightDeck[i].sk3 = PreDeck[i].sk3;
	}
}

void FightScene::showparticle(Ref * pSender)
{
	
	ParticleSystem * particle;
	particle = ParticleFire::create();
	particle->setScale(0.55f);
	particle->setDuration(0.7f);
	particle->setPosition(Vec2(247, 124));
	voidNode4->addChild(particle);
}

void FightScene::showparticle2(Ref * pSender)
{
	ParticleSystem * particle;
	particle = ParticleGalaxy::create();
	particle->setScale(0.7f);
	particle->setDuration(0.4f);
	particle->setPosition(Vec2(430, 240));
	voidNode4->addChild(particle);
}

void FightScene::callEveryFrame(float f)
{
	nNum++;
	nNum2++;
	nNum3++;
	nNum4++;
	nNum5++;
	nNum6++;
	nNum7++;
	nNum8++;
	if (nNum > 900 && isDelay)
	{
		nNum = 1;
		voidNode4->removeAllChildren();
		playerturn();
		isDelay = false;
	}
	else if (nNum2 > 300 && isDelay2)
	{
		nNum2 = 1;
		bosshp = bosshp - e_sprite[1]->getTag();
		showparticle2(this);
		makeupdate();
		if (bosshp < 1)
		{
			bosshp = 0;
			nNum7 = 0;
			isDelay7 = true;
		}
		isDelay2 = false;
	}
	else if (nNum3 > 480 && isDelay3)
	{
		nNum3 = 1;
		bosshp = bosshp - e_sprite[2]->getTag();
		showparticle2(this);
		makeupdate();
		if (bosshp < 1)
		{
			bosshp = 0;
			nNum7 = 0;
			isDelay7 = true;
		}
		isDelay3 = false;
	}
	else if (nNum4 > 660 && isDelay4)
	{
		nNum4 = 1;
		bosshp = bosshp - e_sprite[3]->getTag();
		showparticle2(this);
		makeupdate();
		if (bosshp < 1)
		{
			bosshp = 0;
			nNum7 = 0;
			isDelay7 = true;
		}
		isDelay4 = false;
	}
	else if (nNum5 > 850 && isDelay5)
	{
		nNum5 = 1;
		bosshp = bosshp - e_sprite[4]->getTag();
		showparticle2(this);
		makeupdate();
		if (bosshp < 1)
		{
			bosshp = 0;
			nNum7 = 0;
			isDelay7 = true;
		}
		isDelay5 = false;
	}	
	if (isDelay7 && nNum7 > 200)
	{
		gameclear();
	}
	if (isDelay8 && nNum8 > 150)
	{
		showparticle(this);
		isDelay8 = false;
	}
}

void FightScene::clickHand(Ref * pSender, int i, int j)
{
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	PlayerDeck * FightDeck = GameManager::getInstance()->getFightDeck();

	string str = "Images/basecard.png";
	if (j <= playercost)
	{
		playercost = playercost - j;
		// 카드가 사용되면 화면에 출력되는 코스트 레이블을 최신화 시켜준다
		makeupdate();
		for (int k = 0; k < 5; k++)
		{
			if (e_sprite[k]->getResourceName().c_str() == str)
			{
				voidNode3->removeChild(e_sprite[k], 1);
				e_sprite[k] = Sprite::create(FightDeck[i].cname.c_str());
				e_sprite[k]->setScale(0.8f);
				e_sprite[k]->setAnchorPoint(Vec2::ZERO);
				e_sprite[k]->setPosition(Vec2(10 + PLUS3 * k, 73));
				e_sprite[k]->setTag(FightDeck[i].cost);
				voidNode4->addChild(e_sprite[k]);

				HandMenu[i]->removeAllChildren();
				FightDeck[i].numofcard = 0;
				FightDeck[i].type = 10;
				FightDeck[i].cname = "";
				FightDeck[i].attribute = 0;
				FightDeck[i].grade = 0;
				FightDeck[i].cost = 0;
				FightDeck[i].atk = 0;
				FightDeck[i].hp = 0;
				FightDeck[i].sk1 = 0;
				FightDeck[i].sk2 = 0;
				FightDeck[i].sk3 = 0;
								
				break;
			}
		}
	}
}