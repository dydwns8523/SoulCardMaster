#ifndef __CompliationScene_Scene_H__
#define __CompliationScene_SCENE_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Constans.h"


USING_NS_CC;

class CompliationScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CompliationScene);

	Layer * voidNode;
	Sprite * comp;
	Label * label1;
	Label * label2;

	// AllDeck의 정보를 담아올 AllCard와 그정보를 받아 객체를 생성할 pMenu생성
	MenuItemImage *PreCard[PRE_DECK_MAX];
	MenuItemImage *AllCard[ALL_DECK_MAX];
	Menu *pMenu[ALL_DECK_MAX];
	Menu * pMenu2[PRE_DECK_MAX];
	Layer * pLayer;
	Layer * pLayer2;

	ui::ScrollView * pScroll1;
	ui::ScrollView * pScroll2;


	void clickB2(Ref * pSender);

	void initScene();

	void makealldeckview();
	void makepredeckview();
	void scrollEvent(Ref * pSender, ui::ScrollView::EventType event);
	void clickcard1(Ref * pSender, int i);
	void clickcard2(Ref * pSender, int j);
};

#endif // __HELLOWORLD_SCENE_H__


