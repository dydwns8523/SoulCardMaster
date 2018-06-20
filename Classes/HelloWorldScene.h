#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui\CocosGUI.h"
#include "network\HttpClient.h"
#include "ui\CocosGUI.h"
#include "PlayerData.h"


USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;
using namespace cocos2d::network;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	Layer * voidNode;
	Sprite * sprite;
	Sprite * sground;
	Sprite * wground;
	ui::ScrollView * pScroll;	
	Label * pLabel;
	Vector<Sprite*> cards;
	Sprite * sprite_1;
	Sprite * sprite_2;
	Sprite * sprite_3;
	Sprite * sprite_4;
	Sprite * sprite_5;
	char  CIstr[100];
	string card;
	string sgold;
	Label * label;

	vector<CardData*> fireDeck1;	



	void clickstore(Ref * pSender);
	void clickstory(Ref * pSender);
	void clickcompliation(Ref * pSender);
	void clickback(Ref * pSender);
	void clickSR(Ref * pSender);
	void clickR(Ref * pSender);
	void clickRA(Ref * pSender);
	void clickN(Ref * pSender);
	void clickB1(Ref * pSender);
	
	void makeStoreView();
	void scrollEvent(Ref * pSender, ui::ScrollView::EventType event);

	void makecard();
	void createButton();
	void createloadbutton();
	void TouchCB(Ref * sender, Widget::TouchEventType type);
	void TouchCB2(Ref * sender, Widget::TouchEventType type);
	void carddatainit();
	void cardfordeck(int i,int num, int ty, int att, int gra, int co, int at, int heal
		, int a, int b, int c);

	virtual ~HelloWorld();
};




#endif // __HELLOWORLD_SCENE_H__
