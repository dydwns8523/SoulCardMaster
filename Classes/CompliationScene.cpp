#include "CompliationScene.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "FightScene.h"

USING_NS_CC;

Scene* CompliationScene::createScene()
{
	return CompliationScene::create();
}

bool CompliationScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	voidNode = Layer::create();
	this->addChild(voidNode);

	scheduleUpdate();


	comp = Sprite::create("Images/compliationScene.png");
	comp->setAnchorPoint(Vec2(0, 0));
	voidNode->addChild(comp);

	auto BItem2 = MenuItemImage::create(
		"Images/backbutton.png",
		"Images/backbutton.png",
		CC_CALLBACK_1(CompliationScene::clickB2, this));

	// 카드 편집씬의 백버튼
	auto pSMenu5 = Menu::create(BItem2, nullptr);
	pSMenu5->alignItemsHorizontally();
	pSMenu5->setPosition(Vec2(450, 300));
	voidNode->addChild(pSMenu5);

	makealldeckview();
	makepredeckview();
	initScene();

	return true;
}

void CompliationScene::clickB2(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::create());
}

void CompliationScene::initScene()
{
	string str1 = " 총\n 덱";
	string str2 = " 현\n 재\n 덱";
	label1 = Label::create(str1, "", 20);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(Vec2(10, 230));
	comp->addChild(label1);
	
	label2 = Label::create(str2, "", 20);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(Vec2(10, 100));
	comp->addChild(label2);
	
}

void CompliationScene::makealldeckview()
{
	PlayerDeck * AllDeck = GameManager::getInstance()->getAllDeck();
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();

	// 총덱과 현재덱의 스크롤 뷰 생성
	pScroll1 = ui::ScrollView::create();
	pScroll2 = ui::ScrollView::create();

	// 총덱 레이어 생성
	pLayer = Layer::create();
	pLayer->setAnchorPoint(Vec2::ZERO);
	pLayer->setPosition(Vec2(-170, -90));
	pLayer->setContentSize(Size(11000, 150));

	// 총덱의 스크롤 생성
	pScroll1->setSize(Size(480, 130));
	pScroll1->setInnerContainerSize(pLayer->getContentSize());
	pScroll1->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	pScroll1->setBounceEnabled(true);
	pScroll1->setScrollBarAutoHideEnabled(true);
	pScroll1->addEventListener(CC_CALLBACK_2(CompliationScene::scrollEvent, this));
	pScroll1->jumpToPercentHorizontal(0);
	pScroll1->setPosition(Vec2(0, 140));
	pScroll1->addChild(pLayer);
	comp->addChild(pScroll1);

	// 총덱의 스크롤 내부의 아이템 이미지 생성
	for (int i = 0; i < ALL_DECK_MAX; i++)
	{
		AllCard[i] = MenuItemImage::create(
			AllDeck[i].cname.c_str(),
			AllDeck[i].cname.c_str(),
			CC_CALLBACK_1(CompliationScene::clickcard1, this, i));
		pMenu[i] = Menu::create(AllCard[i], nullptr);
		AllCard[i]->setPosition(Vec2((PLUS2 * i), 30));
		pLayer->addChild(pMenu[i]);
	}
}

void CompliationScene::makepredeckview()
{
	PlayerDeck * AllDeck = GameManager::getInstance()->getAllDeck();
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();

	// 현재덱 레이어 생성
	pLayer2 = Layer::create();
	pLayer2->setAnchorPoint(Vec2::ZERO);
	pLayer2->setPosition(Vec2(-170, -90));
	pLayer2->setContentSize(Size(2640, 130));


	// 현재 덱의 스크롤 생성
	pScroll2->setSize(Size(480, 130));
	pScroll2->setInnerContainerSize(pLayer->getContentSize());
	pScroll2->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	pScroll2->setBounceEnabled(true);
	pScroll2->setScrollBarAutoHideEnabled(true);
	pScroll2->addEventListener(CC_CALLBACK_2(CompliationScene::scrollEvent, this));
	pScroll2->jumpToPercentHorizontal(0);
	pScroll2->setPosition(Vec2(0, 30));
	pScroll2->addChild(pLayer2);
	comp->addChild(pScroll2);

	// 현재 덱 스크롤 내부의 아이템 이미지 생성
	for (int j = 0; j < PRE_DECK_MAX; j++)
	{
		PreCard[j] = MenuItemImage::create(
			PreDeck[j].cname.c_str(),
			PreDeck[j].cname.c_str(),
			CC_CALLBACK_1(CompliationScene::clickcard2, this, j));
		pMenu[j] = Menu::create(PreCard[j], nullptr);
		PreCard[j]->setPosition(Vec2((PLUS2 * j), 10));
		pLayer2->addChild(pMenu[j]);
	}
}

void CompliationScene::clickcard1(Ref * pSender, int i)
{
	PlayerDeck * AllDeck = GameManager::getInstance()->getAllDeck();
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	for (int j = 0; j < PRE_DECK_MAX; j++)
	{
		if (PreDeck[j].cname == "")
		{
			// 현재 덱 멤버에 총덱에 있는 카드 정보 복사
			PreDeck[j].numofcard = AllDeck[i].numofcard;
			PreDeck[j].type = AllDeck[i].type;
			PreDeck[j].cname = AllDeck[i].cname.c_str();
			PreDeck[j].attribute = AllDeck[i].attribute;
			PreDeck[j].grade = AllDeck[i].grade;
			PreDeck[j].cost = AllDeck[i].cost;
			PreDeck[j].atk = AllDeck[i].atk;
			PreDeck[j].hp = AllDeck[i].hp;
			PreDeck[j].sk1 = AllDeck[i].sk1;
			PreDeck[j].sk2 = AllDeck[i].sk2;
			PreDeck[j].sk3 = AllDeck[i].sk3;

			// 복사후 총덱에 카드 정보 삭제
			AllDeck[i].numofcard = 0;
			AllDeck[i].type = 10;
			AllDeck[i].cname = "";
			AllDeck[i].attribute = 0;
			AllDeck[i].grade = 0;
			AllDeck[i].cost = 0;
			AllDeck[i].atk = 0;
			AllDeck[i].hp = 0;
			AllDeck[i].sk1 = 0;
			AllDeck[i].sk2 = 0;
			AllDeck[i].sk3 = 0;
			
			// 카드 복사후 총덱의 카드들을 한장씩 앞으로 당김
			for (int k = 0; k < ALL_DECK_MAX - i; k++)
			{
				if (AllDeck[i + k].cname == "")
				{
					AllDeck[i + k].numofcard = AllDeck[i + 1 + k].numofcard;
					AllDeck[i + k].type = AllDeck[i + 1 + k].type;
					AllDeck[i + k].cname = AllDeck[i + 1 + k].cname.c_str();
					AllDeck[i + k].attribute = AllDeck[i + 1 + k].attribute;
					AllDeck[i + k].grade = AllDeck[i + 1 + k].grade;
					AllDeck[i + k].cost = AllDeck[i + 1 + k].cost;
					AllDeck[i + k].atk = AllDeck[i + 1 + k].atk;
					AllDeck[i + k].hp = AllDeck[i + 1 + k].hp;
					AllDeck[i + k].sk1 = AllDeck[i + 1 + k].sk1;
					AllDeck[i + k].sk2 = AllDeck[i + 1 + k].sk2;
					AllDeck[i + k].sk3 = AllDeck[i + 1 + k].sk3;
					AllDeck[i + 1 + k].numofcard = 0;
					AllDeck[i + 1 + k].type = 10;
					AllDeck[i + 1 + k].cname = "";
					AllDeck[i + 1 + k].attribute = 0;
					AllDeck[i + 1 + k].grade = 0;
					AllDeck[i + 1 + k].cost = 0;
					AllDeck[i + 1 + k].atk = 0;
					AllDeck[i + 1 + k].hp = 0;
					AllDeck[i + 1 + k].sk1 = 0;
					AllDeck[i + 1 + k].sk2 = 0;
					AllDeck[i + 1 + k].sk3 = 0;
					if (AllDeck[k].cname == "")
					{
						break;
					}
				}
			}
			break;
		}
	}

	for (int j = 0; j < 10; j++)
	{
		log("PreDeck[%d].numofcard : %d\nPreDeck[%d].type : %d\nPreDeck[%d].cname : %s",
			j, PreDeck[j].numofcard, j, PreDeck[j].type, j, PreDeck[j].cname.c_str());
	}


	pLayer->removeAllChildren();
	pScroll1->removeAllChildren();
	comp->removeAllChildren();

	makealldeckview();
	makepredeckview();
	initScene();

}

void CompliationScene::clickcard2(Ref * pSender, int j)
{
	PlayerDeck * AllDeck = GameManager::getInstance()->getAllDeck();
	PlayerDeck * PreDeck = GameManager::getInstance()->getPreDeck();
	for (int i = 0; i < ALL_DECK_MAX; i++)
	{
		if (AllDeck[i].cname == "")
		{
			// 현재 덱 멤버에 총덱에 있는 카드 정보 복사
			AllDeck[i].numofcard = PreDeck[j].numofcard;
			AllDeck[i].type = PreDeck[j].type;
			AllDeck[i].cname = PreDeck[j].cname.c_str();
			AllDeck[i].attribute = PreDeck[j].attribute;
			AllDeck[i].grade = PreDeck[j].grade;
			AllDeck[i].cost = PreDeck[j].cost;
			AllDeck[i].atk = PreDeck[j].atk;
			AllDeck[i].hp = PreDeck[j].hp;
			AllDeck[i].sk1 = PreDeck[j].sk1;
			AllDeck[i].sk2 = PreDeck[j].sk2;
			AllDeck[i].sk3 = PreDeck[j].sk3;

			// 복사후 총덱에 카드 정보 삭제
			PreDeck[j].numofcard = 0;
			PreDeck[j].type = 10;
			PreDeck[j].cname = "";
			PreDeck[j].attribute = 0;
			PreDeck[j].grade = 0;
			PreDeck[j].cost = 0;
			PreDeck[j].atk = 0;
			PreDeck[j].hp = 0;
			PreDeck[j].sk1 = 0;
			PreDeck[j].sk2 = 0;
			PreDeck[j].sk3 = 0;

			// 카드 복사후 총덱의 카드들을 한장씩 앞으로 당김
			for (int k = 0; k < PRE_DECK_MAX - i; k++)
			{
				if (PreDeck[j + k].cname == "")
				{
					PreDeck[j + k].numofcard = PreDeck[j + 1 + k].numofcard;
					PreDeck[j + k].type = PreDeck[j + 1 + k].type;
					PreDeck[j + k].cname = PreDeck[j + 1 + k].cname.c_str();
					PreDeck[j + k].attribute = PreDeck[j + 1 + k].attribute;
					PreDeck[j + k].grade = PreDeck[j + 1 + k].grade;
					PreDeck[j + k].cost = PreDeck[j + 1 + k].cost;
					PreDeck[j + k].atk = PreDeck[j + 1 + k].atk;
					PreDeck[j + k].hp = PreDeck[j + 1 + k].hp;
					PreDeck[j + k].sk1 = PreDeck[j + 1 + k].sk1;
					PreDeck[j + k].sk2 = PreDeck[j + 1 + k].sk2;
					PreDeck[j + k].sk3 = PreDeck[j + 1 + k].sk3;
					PreDeck[j + 1 + k].numofcard = 0;
					PreDeck[j + 1 + k].type = 10;
					PreDeck[j + 1 + k].cname = "";
					PreDeck[j + 1 + k].attribute = 0;
					PreDeck[j + 1 + k].grade = 0;
					PreDeck[j + 1 + k].cost = 0;
					PreDeck[j + 1 + k].atk = 0;
					PreDeck[j + 1 + k].hp = 0;
					PreDeck[j + 1 + k].sk1 = 0;
					PreDeck[j + 1 + k].sk2 = 0;
					PreDeck[j + 1 + k].sk3 = 0;
					if (PreDeck[k].cname == "")
					{
						break;
					}
				}
			}
			break;
		}
	}

	for (int j = 0; j < 10; j++)
	{
		log("AllDeck[%d].numofcard : %d\nAllDeck[%d].type : %d\nAllDeck[%d].cname : %s",
			j, AllDeck[j].numofcard, j, AllDeck[j].type, j, AllDeck[j].cname.c_str());
	}

	

	pLayer2->removeAllChildren();
	pScroll2->removeAllChildren();
	comp->removeAllChildren();
	
	makealldeckview();
	makepredeckview();
	initScene();

}

void CompliationScene::scrollEvent(Ref * pSender, ui::ScrollView::EventType event)
{
	switch (event)
	{
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_TOP:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_LEFT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_RIGHT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLLING:
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_LEFT:
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_RIGHT:
		break;
	case cocos2d::ui::ScrollView::EventType::CONTAINER_MOVED:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLLING_BEGAN:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLLING_ENDED:
		break;
	case cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED:
		break;
	default:
		break;
	}
}



