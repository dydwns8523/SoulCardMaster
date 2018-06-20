#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "network\HttpClient.h"
#include "Constans.h"
#include "GameManager.h"
#include "TemplateSingleton.h"
#include "CompliationScene.h"
#include "ChoicestoryScene.h"
#include "resultScene.h"


USING_NS_CC;
using namespace std;
using namespace cocos2d::network;
using namespace ui;
using namespace rapidjson;

Player player;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
	
	if (!Scene::init())
	{
		return false;
	}

	voidNode = Layer::create();
	this->addChild(voidNode);
	
	

	// 대기실 레이어
	wground = Sprite::create("Images/wBack1.png");
	wground->setAnchorPoint(Vec2(0, 0));
	wground->setPosition(Vec2(0, 0));

	// 상점 레이어
	sground = Sprite::create("Images/instore2.png");
	sground->setAnchorPoint(Vec2(0, 0));
	sground->setPosition(Vec2(480, 0));

	voidNode->addChild(wground);
	voidNode->addChild(sground);

	PlayerDeck* testDeck = GameManager::getInstance()->gettestDeck();
	if (testDeck[0].atk == 1)
	{
	player.gold = player.gold + 1500;
	testDeck[0].atk = 0;
	}
	// 대기실 메뉴 생성
	auto storeItem = MenuItemImage::create(
		"Images/store1.png",
		"Images/store2.png",
		CC_CALLBACK_1(HelloWorld::clickstore, this));

	auto storyItem = MenuItemImage::create(
		"Images/story1.png",
		"Images/story2.png",
		CC_CALLBACK_1(HelloWorld::clickstory, this));

	auto compliationItem = MenuItemImage::create(
		"Images/compliation1.png",
		"Images/compliation2.png",
		CC_CALLBACK_1(HelloWorld::clickcompliation, this));

	// 상점 메뉴 생성

	auto BACKItem = MenuItemImage::create(
		"Images/backbutton.png",
		"Images/backbutton.png",
		CC_CALLBACK_1(HelloWorld::clickback, this));

	auto SRItem = MenuItemImage::create(
		"Images/SRpack1.png",
		"Images/SRpack2.png",
		CC_CALLBACK_1(HelloWorld::clickSR, this));

	auto RItem = MenuItemImage::create(
		"Images/Rpack1.png",
		"Images/Rpack2.png",
		CC_CALLBACK_1(HelloWorld::clickR, this));

	auto RAItem = MenuItemImage::create(
		"Images/RApack1.png",
		"Images/RApack2.png",
		CC_CALLBACK_1(HelloWorld::clickRA, this));

	auto NItem = MenuItemImage::create(
		"Images/Npack1.png",
		"Images/Npack2.png",
		CC_CALLBACK_1(HelloWorld::clickN, this));

	auto BItem1 = MenuItemImage::create(
		"Images/Bpack1.png",
		"Images/Bpack2.png",
		CC_CALLBACK_1(HelloWorld::clickB1, this));

	

	

	// 메뉴 크기 설정
	storeItem->setScale(0.167f);
	storyItem->setScale(0.167f);
	compliationItem->setScale(0.167f);
	SRItem->setScale(0.65f);
	RItem->setScale(0.65f);
	RAItem->setScale(0.65f);
	NItem->setScale(0.65f);
	BItem1->setScale(0.65f);
	

	// 메뉴 생성
	auto pMenu = Menu::create(storeItem, storyItem, compliationItem, nullptr);
	auto pSMenu1 = Menu::create(BACKItem, nullptr);
	auto pSMenu2 = Menu::create(SRItem, RItem, nullptr);
	auto pSMenu3 = Menu::create(RAItem, NItem, nullptr);
	auto pSMenu4 = Menu::create(BItem1, nullptr);
	

	// 메뉴배치 
	pMenu->alignItemsHorizontally();
	pMenu->setPosition(Vec2(330, 30));
	pSMenu1->alignItemsHorizontally();
	pSMenu1->setPosition(Vec2(450, 300));
	pSMenu2->alignItemsHorizontally();
	pSMenu2->setPosition(Vec2(320, 127));
	pSMenu3->alignItemsHorizontally();
	pSMenu3->setPosition(Vec2(320, 78));
	pSMenu4->alignItemsHorizontally();
	pSMenu4->setPosition(Vec2(237, 29));
	

	// 메뉴 객체 추가
	wground->addChild(pMenu);
	sground->addChild(pSMenu1);
	sground->addChild(pSMenu2);
	sground->addChild(pSMenu3);
	sground->addChild(pSMenu4);


	
	makecard();
	createButton();
	createloadbutton();
	carddatainit();

	
}

void HelloWorld::clickstore(Ref * pSender)
{
	
	int iGold;
	char * sGold;

	log("상점 메뉴가 눌렸습니다.");
	auto go = MoveTo::create(0.001, Vec2(-480, 0));
	voidNode->runAction(go);
	sground->removeChild(label, 1);
	
	// 상점에 아이템 목록 스크롤 뷰 생성
	makeStoreView();
	sgold = to_string(player.gold);
	label = Label::create(sgold, "", 20);
	label->setColor(Color3B::YELLOW);
	label->setPosition(Vec2(430, 23));
	sground->addChild(label);
	
}

void HelloWorld::clickstory(Ref * pSender)
{
	log("스토리 메뉴가 눌렸습니다.");
	Director::getInstance()->replaceScene(ChoicestoryScene::create());
}

void HelloWorld::clickcompliation(Ref * pSender)
{
	Director::getInstance()->replaceScene(CompliationScene::create());
}

void HelloWorld::clickback(Ref * pSender)
{
	log("뒤로가기가 눌렸습니다.");
	auto go = MoveTo::create(0.001, Vec2(0, 0));
	voidNode->runAction(go);
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	sground->removeChild(sprite_1, 1);
	sground->removeChild(sprite_2, 1);
	sground->removeChild(sprite_3, 1);
	sground->removeChild(sprite_4, 1);
	sground->removeChild(sprite_5, 1);
}

void HelloWorld::clickSR(Ref * pSender)
{
	log("슈퍼레어 뽑기를 눌렀습니다.");
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	
	
	int state2 = 1;
	int state3 = 1;
	int state4 = 1;
	int state5 = 1;

	srand((unsigned)time(NULL));
 	if (player.gold >= 100000)
	{
		sground->removeChild(label, 1);
		player.gold -= 100000;
		// 상점레이블에서 골드 표시
		sgold = to_string(player.gold);
		label = Label::create(sgold, "", 20);
		label->setColor(Color3B::YELLOW);
		label->setPosition(Vec2(430, 23));
		sground->addChild(label);
		PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();
		

		if (sprite_1 != nullptr 
			&& sprite_2 != nullptr
			&& sprite_3 != nullptr
			&& sprite_4 != nullptr
			&& sprite_5 != nullptr)
		{
			sground->removeChild(sprite_1, 1);
			sground->removeChild(sprite_2, 1);
			sground->removeChild(sprite_3, 1);
			sground->removeChild(sprite_4, 1);
			sground->removeChild(sprite_5, 1);
		}	
		
		// 1번 카드
		sprite_1 = cards.at(rand() % 5);
		sprite_1->setAnchorPoint(Vec2::ZERO);
		sprite_1->setPosition(Vec2(80, 100));
		sground->addChild(sprite_1);
		auto Ac1 = MoveTo::create(0.2f, Vec2(10, 170));
		sprite_1->runAction(Ac1);
		for (int i = 0; i < 100; i++)
		{
			if (AllDeck[i].cname == "")
			{
				AllDeck[i].cname = sprite_1->getResourceName().c_str();
				for (int j = 0; j < 20; j++)
				{
					if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
					{
						cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
							fireDeck1[j]->attribute, fireDeck1[j]->grade,
							fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
							fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
					}
				}
				break;
			}
		}

		// 2번 카드
		while (state2 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_2 = cards.at(rand() % 5 + 20);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_2 = cards.at(rand() % 5 + 25);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_2 = cards.at(rand() % 5 + 30);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_2 = cards.at(rand() % 5 + 35);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state2 = 0;
		}

		// 3번 카드
		while (state3 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_3 = cards.at(rand() % 5 + 40);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_3 = cards.at(rand() % 5 + 45);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_3 = cards.at(rand() % 5 + 50);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_3 = cards.at(rand() % 5 + 55);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state3 = 0;
		}
		
		// 4번 카드
		while (state4 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_4 = cards.at(rand() % 5 + 60);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_4 = cards.at(rand() % 5 + 65);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_4 = cards.at(rand() % 5 + 70);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_4 = cards.at(rand() % 5 + 75);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state4 = 0;
		}

		// 5번 카드
		while (state5 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_5 = cards.at(rand() % 5 + 80);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_5 = cards.at(rand() % 5 + 85);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_5 = cards.at(rand() % 5 + 90);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_5 = cards.at(rand() % 5 + 95);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state5 = 0;
		}
	}
}

void HelloWorld::clickR(Ref * pSender)
{
	log("레어 뽑기를 눌렀습니다.");
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();

	int state2 = 1;
	int state3 = 1;
	int state4 = 1;
	int state5 = 1;

	srand((unsigned)time(NULL));
	if (player.gold >= 20000)
	{
		sground->removeChild(label, 1);
		player.gold -= 20000;
		// 상점레이블에서 골드 표시
		sgold = to_string(player.gold);
		label = Label::create(sgold, "", 20);
		label->setColor(Color3B::YELLOW);
		label->setPosition(Vec2(430, 23));
		sground->addChild(label);
		log("플레이어의 골드 = %d", player.gold);

		if (sprite_1 != nullptr
			&& sprite_2 != nullptr
			&& sprite_3 != nullptr
			&& sprite_4 != nullptr
			&& sprite_5 != nullptr)
		{
			sground->removeChild(sprite_1, 1);
			sground->removeChild(sprite_2, 1);
			sground->removeChild(sprite_3, 1);
			sground->removeChild(sprite_4, 1);
			sground->removeChild(sprite_5, 1);
		}

		// 1번 카드
		sprite_1 = cards.at(rand() % 5 + 5);
		sprite_1->setAnchorPoint(Vec2::ZERO);
		sprite_1->setPosition(Vec2(80, 100));
		sground->addChild(sprite_1);
		auto Ac1 = MoveTo::create(0.2f, Vec2(10, 170));
		sprite_1->runAction(Ac1);
		for (int i = 0; i < 100; i++)
		{
			if (AllDeck[i].cname == "")
			{
				AllDeck[i].cname = sprite_1->getResourceName().c_str();
				for (int j = 0; j < 20; j++)
				{
					if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
					{
						cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
							fireDeck1[j]->attribute, fireDeck1[j]->grade,
							fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
							fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
					}
				}
				break;
			}
		}

		// 2번 카드
		while (state2 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_2 = cards.at(rand() % 5 + 25);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_2 = cards.at(rand() % 5 + 30);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_2 = cards.at(rand() % 5 + 35);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state2 = 0;
		}

		// 3번 카드
		while (state3 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_3 = cards.at(rand() % 5 + 45);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_3 = cards.at(rand() % 5 + 50);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_3 = cards.at(rand() % 5 + 55);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state3 = 0;
		}

		// 4번 카드
		while (state4 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_4 = cards.at(rand() % 5 + 65);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_4 = cards.at(rand() % 5 + 70);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_4 = cards.at(rand() % 5 + 75);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state4 = 0;
		}

		// 5번 카드
		while (state5 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_5 = cards.at(rand() % 5 + 85);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_5 = cards.at(rand() % 5 + 90);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_5 = cards.at(rand() % 5 + 95);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state5 = 0;
		}
	}
}


void HelloWorld::clickRA(Ref * pSender)
{
	log("랜덤 뽑기를 눌렀습니다.");
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();


	int state1 = 1;
	int state2 = 1;
	int state3 = 1;
	int state4 = 1;
	int state5 = 1;

	srand((unsigned)time(NULL));
	if (player.gold >= 10000)
	{
		sground->removeChild(label, 1);
		player.gold -= 10000;
		sgold = to_string(player.gold);
		label = Label::create(sgold, "", 20);
		label->setColor(Color3B::YELLOW);
		label->setPosition(Vec2(430, 23));
		sground->addChild(label);

		if (sprite_1 != nullptr
			&& sprite_2 != nullptr
			&& sprite_3 != nullptr
			&& sprite_4 != nullptr
			&& sprite_5 != nullptr)
		{
			sground->removeChild(sprite_1, 1);
			sground->removeChild(sprite_2, 1);
			sground->removeChild(sprite_3, 1);
			sground->removeChild(sprite_4, 1);
			sground->removeChild(sprite_5, 1);
		}

		// 1번 카드
		while (state1 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_1 = cards.at(rand() % 5);
				sprite_1->setAnchorPoint(Vec2::ZERO);
				sprite_1->setPosition(Vec2(80, 100));
				sground->addChild(sprite_1);
				auto Ac2 = MoveTo::create(0.2f, Vec2(10, 170));
				sprite_1->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_1->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_1 = cards.at(rand() % 5 + 5);
				sprite_1->setAnchorPoint(Vec2::ZERO);
				sprite_1->setPosition(Vec2(80, 100));
				sground->addChild(sprite_1);
				auto Ac2 = MoveTo::create(0.2f, Vec2(10, 170));
				sprite_1->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_1->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_1 = cards.at(rand() % 5 + 10);
				sprite_1->setAnchorPoint(Vec2::ZERO);
				sprite_1->setPosition(Vec2(80, 100));
				sground->addChild(sprite_1);
				auto Ac2 = MoveTo::create(0.2f, Vec2(10, 170));
				sprite_1->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_1->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_1 = cards.at(rand() % 5 + 15);
				sprite_1->setAnchorPoint(Vec2::ZERO);
				sprite_1->setPosition(Vec2(80, 100));
				sground->addChild(sprite_1);
				auto Ac2 = MoveTo::create(0.2f, Vec2(10, 170));
				sprite_1->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_1->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state1 = 0;
		}

		// 2번 카드
		while (state2 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_2 = cards.at(rand() % 5 + 20);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_2 = cards.at(rand() % 5 + 25);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_2 = cards.at(rand() % 5 + 30);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_2 = cards.at(rand() % 5 + 35);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state2 = 0;
		}

		// 3번 카드
		while (state3 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_3 = cards.at(rand() % 5 + 40);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_3 = cards.at(rand() % 5 + 45);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_3 = cards.at(rand() % 5 + 50);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_3 = cards.at(rand() % 5 + 55);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state3 = 0;
		}

		// 4번 카드
		while (state4 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_4 = cards.at(rand() % 5 + 60);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_4 = cards.at(rand() % 5 + 65);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_4 = cards.at(rand() % 5 + 70);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_4 = cards.at(rand() % 5 + 75);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state4 = 0;
		}

		// 5번 카드
		while (state5 == 1)
		{
			int a = rand() % 100;
			if (5 > a)
			{
				sprite_5 = cards.at(rand() % 5 + 80);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (5 < a && a < 16)
			{
				sprite_5 = cards.at(rand() % 5 + 85);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else if (16 < a && a < 33)
			{
				sprite_5 = cards.at(rand() % 5 + 90);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_5 = cards.at(rand() % 5 + 95);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}

			}
			state5 = 0;
		}
	}
	
}

void HelloWorld::clickN(Ref * pSender)
{
	log("노말 뽑기를 눌렀습니다.");
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();

	int state2 = 1;
	int state3 = 1;
	int state4 = 1;
	int state5 = 1;

	srand((unsigned)time(NULL));
	if (player.gold >= 2000)
	{
		sground->removeChild(label, 1);
		player.gold -= 2000;
		sgold = to_string(player.gold);
		label = Label::create(sgold, "", 20);
		label->setColor(Color3B::YELLOW);
		label->setPosition(Vec2(430, 23));
		sground->addChild(label);

		if (sprite_1 != nullptr
			&& sprite_2 != nullptr
			&& sprite_3 != nullptr
			&& sprite_4 != nullptr
			&& sprite_5 != nullptr)
		{
			sground->removeChild(sprite_1, 1);
			sground->removeChild(sprite_2, 1);
			sground->removeChild(sprite_3, 1);
			sground->removeChild(sprite_4, 1);
			sground->removeChild(sprite_5, 1);
		}

		// 1번 카드
		sprite_1 = cards.at(rand() % 5 + 10);
		sprite_1->setAnchorPoint(Vec2::ZERO);
		sprite_1->setPosition(Vec2(80, 100));
		sground->addChild(sprite_1);
		auto Ac1 = MoveTo::create(0.2f, Vec2(10, 170));
		sprite_1->runAction(Ac1);
		for (int i = 0; i < 100; i++)
		{
			if (AllDeck[i].cname == "")
			{
				AllDeck[i].cname = sprite_1->getResourceName().c_str();
				for (int j = 0; j < 20; j++)
				{
					if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
					{
						cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
							fireDeck1[j]->attribute, fireDeck1[j]->grade,
							fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
							fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
					}
				}
				break;
			}
		}

		// 2번 카드
		while (state2 == 1)
		{
			int a = rand() % 100;
			if (25 > a)
			{
				sprite_2 = cards.at(rand() % 5 + 30);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_2 = cards.at(rand() % 5 + 35);
				sprite_2->setAnchorPoint(Vec2::ZERO);
				sprite_2->setPosition(Vec2(80, 100));
				sground->addChild(sprite_2);
				auto Ac2 = MoveTo::create(0.2f, Vec2(100, 170));
				sprite_2->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_2->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state2 = 0;
		}

		// 3번 카드
		while (state3 == 1)
		{
			int a = rand() % 100;
			if (25 > a)
			{
				sprite_3 = cards.at(rand() % 5 + 50);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_3 = cards.at(rand() % 5 + 55);
				sprite_3->setAnchorPoint(Vec2::ZERO);
				sprite_3->setPosition(Vec2(80, 100));
				sground->addChild(sprite_3);
				auto Ac2 = MoveTo::create(0.2f, Vec2(190, 170));
				sprite_3->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_3->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state3 = 0;
		}

		// 4번 카드
		while (state4 == 1)
		{
			int a = rand() % 100;
			if (25 > a)
			{
				sprite_4 = cards.at(rand() % 5 + 70);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_4 = cards.at(rand() % 5 + 75);
				sprite_4->setAnchorPoint(Vec2::ZERO);
				sprite_4->setPosition(Vec2(80, 100));
				sground->addChild(sprite_4);
				auto Ac2 = MoveTo::create(0.2f, Vec2(280, 170));
				sprite_4->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_4->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state4 = 0;
		}

		// 5번 카드
		while (state5 == 1)
		{
			int a = rand() % 100;
			if (25 > a)
			{
				sprite_5 = cards.at(rand() % 5 + 90);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			else
			{
				sprite_5 = cards.at(rand() % 5 + 95);
				sprite_5->setAnchorPoint(Vec2::ZERO);
				sprite_5->setPosition(Vec2(80, 100));
				sground->addChild(sprite_5);
				auto Ac2 = MoveTo::create(0.2f, Vec2(370, 170));
				sprite_5->runAction(Ac2);
				for (int i = 0; i < 100; i++)
				{
					if (AllDeck[i].cname == "")
					{
						AllDeck[i].cname = sprite_5->getResourceName().c_str();
						for (int j = 0; j < 20; j++)
						{
							if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
							{
								cardfordeck(i, fireDeck1[j]->numofcard, fireDeck1[j]->type,
									fireDeck1[j]->attribute, fireDeck1[j]->grade,
									fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
									fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
							}
						}
						break;
					}
				}
			}
			state5 = 0;
		}
	}
}

void HelloWorld::clickB1(Ref * pSender)
{
	log("베이직 뽑기를 눌렀습니다.");
	// 상점에 생성된 스크롤 뷰 삭제
	sground->removeChild(pScroll, 1);
	PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();

	srand((unsigned)time(NULL));
	if (player.gold >= 500)
	{
		sground->removeChild(label, 1);
		player.gold -= 500;
		sgold = to_string(player.gold);
		label = Label::create(sgold, "", 20);
		label->setColor(Color3B::YELLOW);
		label->setPosition(Vec2(430, 23));
		sground->addChild(label);

		if (sprite_1 != nullptr)
		{
			sground->removeChild(sprite_1, 1);
			sground->removeChild(sprite_2, 1);
			sground->removeChild(sprite_3, 1);
			sground->removeChild(sprite_4, 1);
			sground->removeChild(sprite_5, 1);
		}

		// 오직 하나의 카드
		sprite_1 = cards.at(rand() % 5 + 15);
		sprite_1->setAnchorPoint(Vec2::ZERO);
		sprite_1->setPosition(Vec2(80, 100));
		sground->addChild(sprite_1);
		auto Ac1 = MoveTo::create(0.2f, Vec2(190, 170));
		sprite_1->runAction(Ac1);

		

		for (int i = 0; i < 100; i++)
		{
			if (AllDeck[i].cname == "")
			{
				AllDeck[i].cname = sprite_1->getResourceName().c_str();
				for (int j = 0; j < 20; j++)
				{
					if (AllDeck[i].cname == fireDeck1[j]->cname.c_str())
					{
						cardfordeck(i,fireDeck1[j]->numofcard, fireDeck1[j]->type,
							fireDeck1[j]->attribute, fireDeck1[j]->grade,
							fireDeck1[j]->cost, fireDeck1[j]->atk, fireDeck1[j]->hp,
							fireDeck1[j]->sk1, fireDeck1[j]->sk2, fireDeck1[j]->sk3);
					}
				}
				break;
			}
		}
		
		log("%s", sprite_1->getResourceName().c_str());
	}
	for (int i = 0; i < 10; i++)
	{
		log("AllDeck[%d].numofcard : %d\nAllDeck[%d].type : %d\nAllDeck[%d].cname : %s",
			i, AllDeck[i].numofcard, i, AllDeck[i].type, i, AllDeck[i].cname.c_str());
	}
	
}




void HelloWorld::makeStoreView()
{

	auto pLayer = Layer::create();
	pLayer->setAnchorPoint(Vec2::ZERO);
	pLayer->setPosition(Vec2(0, 10));
	pLayer->setContentSize(Size(2370, 120));

	for (int i = 0; i < 20; i++)
	{
		sprintf(CIstr, "Images/storefire/%02d.png", i + 1);
		Sprite * caSprite = Sprite::create(CIstr);
		caSprite->setPosition(Vec2((PLUS * i), 10));
		caSprite->setAnchorPoint(Vec2::ZERO);
		pLayer->addChild(caSprite);
	}
	
	// 스크롤 뷰 생성
	pScroll = ui::ScrollView::create();
	pScroll->setSize(Size(480, 130));
	pScroll->setInnerContainerSize(pLayer->getContentSize());
	pScroll->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	pScroll->addChild(pLayer);
	pScroll->setBounceEnabled(true);
	pScroll->setScrollBarAutoHideEnabled(true);
	pScroll->addEventListener(CC_CALLBACK_2(HelloWorld::scrollEvent, this));
	pScroll->jumpToPercentHorizontal(0);
	pScroll->setPosition(Vec2(0, 150));
	sground->addChild(pScroll);
}

void HelloWorld::scrollEvent(Ref * pSender, ui::ScrollView::EventType event)
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

void HelloWorld::makecard()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 1; i < 21; i++)
		{
			sprintf(CIstr, "Images/storefire/%02d.png", i);
			Sprite * cSprite = Sprite::create(CIstr);
			cards.pushBack(cSprite);
		}
	} 
}

void HelloWorld::createButton()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto button = Button::create(
		"Images/저장버튼.png",
		"Images/저장버튼2.png",
		"Images/저장버튼2.png");
	button->setPosition(Vec2(170,15));
	button->setScale(0.1f);
	button->setAnchorPoint(Vec2::ZERO);
	button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TouchCB, this));

	wground->addChild(button);
}

void HelloWorld::createloadbutton()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto button = Button::create(
		"Images/loaddata.png",
		"Images/loaddata2.png",
		"Images/loaddata2.png");
	button->setPosition(Vec2(80, 10));
	button->setScale(0.15f);
	button->setAnchorPoint(Vec2::ZERO);
	button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TouchCB2, this));

	wground->addChild(button);

}

void HelloWorld::TouchCB2(Ref * sender, Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		// 플레이어 정보 읽어오기
		FileUtils * util = FileUtils::getInstance();
		PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();
		PlayerDeck* PreDeck = GameManager::getInstance()->getPreDeck();

		string playerData = util->getStringFromFile("data/character_data.json");
		//log("%s\n", playerData.c_str());

		rapidjson::Document doc;
		doc.Parse<0>(playerData.c_str());
		if (doc.HasParseError())
		{
			log("에러가 있다 %s\n", doc.HasParseError());
		}
		player.gold = doc["gold"].GetInt();
		const rapidjson::Value & arr1 = doc["arr_AllDeck"];
		if (arr1.IsArray())
		{
			for (rapidjson::SizeType i = 0; i < arr1.Size(); i++)
			{
				AllDeck[i].numofcard = arr1[i]["NumofCard"].GetInt();
				AllDeck[i].type = arr1[i]["Type"].GetInt();
				AllDeck[i].cname = arr1[i]["Filename"].GetString();
				AllDeck[i].attribute = arr1[i]["Atrribute"].GetInt();
				AllDeck[i].grade = arr1[i]["Grade"].GetInt();
				AllDeck[i].cost = arr1[i]["Cost"].GetInt();
				AllDeck[i].atk = arr1[i]["Attack"].GetInt();
				AllDeck[i].hp = arr1[i]["Health"].GetInt();
				AllDeck[i].sk1 = arr1[i]["Skill1"].GetInt();
				AllDeck[i].sk2 = arr1[i]["Skill2"].GetInt();
				AllDeck[i].sk3 = arr1[i]["Skill3"].GetInt();
			}

		}

		const rapidjson::Value & arr2 = doc["arr_PreDeck"];
		if (arr2.IsArray())
		{
			for (rapidjson::SizeType i = 0; i < arr2.Size(); i++)
			{
				PreDeck[i].numofcard = arr2[i]["NumofCard"].GetInt();
				PreDeck[i].type = arr2[i]["Type"].GetInt();
				PreDeck[i].cname = arr2[i]["Filename"].GetString();
				PreDeck[i].attribute = arr2[i]["Atrribute"].GetInt();
				PreDeck[i].grade = arr2[i]["Grade"].GetInt();
				PreDeck[i].cost = arr2[i]["Cost"].GetInt();
				PreDeck[i].atk = arr2[i]["Attack"].GetInt();
				PreDeck[i].hp = arr2[i]["Health"].GetInt();
				PreDeck[i].sk1 = arr2[i]["Skill1"].GetInt();
				PreDeck[i].sk2 = arr2[i]["Skill2"].GetInt();
				PreDeck[i].sk3 = arr2[i]["Skill3"].GetInt();
			}

		}
	}
	break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void HelloWorld::TouchCB(Ref * sender, Widget::TouchEventType type)
{
	
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		PlayerData * pData = GameManager::getInstance()->getPlayerData();
		

		pData->_name = "Player";
		pData->_hp = 10;
		pData->_atk = 0;
		pData->_dead = false;
		pData->_gold = player.gold;


		for (int i = 1; i < PRE_DECK_MAX; i++)
		{
			char str1[30], str2[30];
			sprintf(str1, "key%02d", i);
			sprintf(str2, "val%02d", i);
			pData->_PreDeck[str1] = cocos2d::Value(str2);
		}

		for (int i = 0; i < ALL_DECK_MAX; i++)
		{
			char str1[30], str2[30];
			sprintf(str1, "key%02d", i);
			sprintf(str2, "val%02d", i);
			pData->_AllDeck[str1] = cocos2d::Value(str2);
		}
		

		
		/*pdata->_map["key1"] = cocos2d::value("val1");
		pdata->_map["key2"] = cocos2d::value("val2");*/
		

		// 데이터 저장
		GameManager::getInstance()->savePlayerData();

		// 씬 전환
		//Director::getInstance()->replaceScene(TestScene::create());
	}
	break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void HelloWorld::carddatainit()
{
	string filename[20];
	filename[0] = "Images/storefire/01.png";
	filename[1] = "Images/storefire/02.png";
	filename[2] = "Images/storefire/03.png";
	filename[3] = "Images/storefire/04.png";
	filename[4] = "Images/storefire/05.png";
	filename[5] = "Images/storefire/06.png";
	filename[6] = "Images/storefire/07.png";
	filename[7] = "Images/storefire/08.png";
	filename[8] = "Images/storefire/09.png";
	filename[9] = "Images/storefire/10.png";
	filename[10] = "Images/storefire/11.png";
	filename[11] = "Images/storefire/12.png";
	filename[12] = "Images/storefire/13.png";
	filename[13] = "Images/storefire/14.png";
	filename[14] = "Images/storefire/15.png";
	filename[15] = "Images/storefire/16.png";
	filename[16] = "Images/storefire/17.png";
	filename[17] = "Images/storefire/18.png";
	filename[18] = "Images/storefire/19.png";
	filename[19] = "Images/storefire/20.png";

	CardData *pData1 = new CardData(3300, 1, filename[0], 1, 83, 10, 100, 200, 0, 0, 0);
	fireDeck1.push_back(pData1);
	CardData *pData2 = new CardData(3201, 1, filename[1], 1, 83, 4, 70, 60, 0, 0, 0);
	fireDeck1.push_back(pData2);
	CardData *pData3 = new CardData(3202, 2, filename[2], 1, 83, 1, 40, 0, 0, 0, 0);
	fireDeck1.push_back(pData3);
	CardData *pData4 = new CardData(3203, 1, filename[3], 1, 83, 2, 40, 10, 0, 0, 0);
	fireDeck1.push_back(pData4);
	CardData *pData5 = new CardData(3204, 2, filename[4], 1, 83, 4, 25, 0, 0, 0, 0);
	fireDeck1.push_back(pData5);
	CardData *pData6 = new CardData(2200, 1, filename[5], 1, 82, 10, 100, 180, 0, 0, 0);
	fireDeck1.push_back(pData6);
	CardData *pData7 = new CardData(2201, 1, filename[6], 1, 82, 4, 70, 50, 0, 0, 0);
	fireDeck1.push_back(pData7);
	CardData *pData8 = new CardData(2202, 2, filename[7], 1, 82, 1, 30, 0, 0, 0, 0);
	fireDeck1.push_back(pData8);
	CardData *pData9 = new CardData(2203, 1, filename[8], 1, 82, 2, 30, 10, 0, 0, 0);
	fireDeck1.push_back(pData9);
	CardData *pData10 = new CardData(2204, 2, filename[9], 1, 82, 4, 20, 0, 0, 0, 0);
	fireDeck1.push_back(pData10);
	CardData *pData11 = new CardData(1200, 1, filename[10], 1, 81, 10, 80, 160, 0, 0, 0);
	fireDeck1.push_back(pData11);
	CardData *pData12 = new CardData(1201, 1, filename[11], 1, 81, 4, 60, 40, 0, 0, 0);
	fireDeck1.push_back(pData12);
	CardData *pData13 = new CardData(1202, 2, filename[12], 1, 81, 1, 20, 0, 0, 0, 0);
	fireDeck1.push_back(pData13);
	CardData *pData14 = new CardData(1203, 1, filename[13], 1, 81, 2, 20, 10, 0, 0, 0);
	fireDeck1.push_back(pData14);
	CardData *pData15 = new CardData(1204, 2, filename[14], 1, 81, 4, 15, 0, 0, 0, 0);
	fireDeck1.push_back(pData15);
	CardData *pData16 = new CardData(200, 1, filename[15], 1, 80, 10, 50, 100, 0, 0, 0);
	fireDeck1.push_back(pData16);
	CardData *pData17 = new CardData(201, 1, filename[16], 1, 80, 4, 50, 40, 0, 0, 0);
	fireDeck1.push_back(pData17);
	CardData *pData18 = new CardData(202, 2, filename[17], 1, 80, 1, 10, 0, 0, 0, 0);
	fireDeck1.push_back(pData18);
	CardData *pData19 = new CardData(203, 1, filename[18], 1, 80, 2, 25, 5, 0, 0, 0);
	fireDeck1.push_back(pData19);
	CardData *pData20 = new CardData(204, 2, filename[19], 1, 80, 4, 5, 0, 0, 0, 0);
	fireDeck1.push_back(pData20);
}

void HelloWorld::cardfordeck(int i,int num, int ty, int att, int gra, int co, int at, int heal
	, int a, int b, int c)
{
	PlayerDeck* AllDeck = GameManager::getInstance()->getAllDeck();
	AllDeck[i].numofcard = num;
	AllDeck[i].type = ty;
	AllDeck[i].attribute = att;
	AllDeck[i].grade = gra;
	AllDeck[i].cost = co;
	AllDeck[i].atk = at;
	AllDeck[i].hp = heal;
	AllDeck[i].sk1 = a;
	AllDeck[i].sk2 = b;
	AllDeck[i].sk3 = c;
}

HelloWorld::~HelloWorld()
{
	for (auto item : fireDeck1)
	{
		delete item;
	}

	fireDeck1.clear();
}



PlayerDeck::~PlayerDeck()
{
}
