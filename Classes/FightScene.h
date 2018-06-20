#ifndef __FightScene_SCENE_H__
#define __FightScene_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class FightScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(FightScene);

	virtual bool init();

	Layer * voidNode;
	Layer * voidNode2;
	Layer * voidNode3;
	Layer * voidNode4;
	Sprite * fground;
	Label * pLabel1;
	Label * pLabel2;
	Label * bLabel1;
	Label * bLabel2;

	Sprite * e_sprite[6];
	Sprite * m_sprite[6];
	
	

	Sprite * pcost;
	Sprite * bcost;
	Sprite * php;
	Sprite * bhp;

	string p_cost;
	string p_hp;
	string b_cost;
	string b_hp;

	MoveTo *patk1;
	MoveTo *patk2;
	MoveTo *patk3;
	MoveTo *patk4;
	MoveTo *patk5;
	MoveTo *patk6;

	MoveTo * catk;
	MoveTo * batk;

	MoveTo *fight;

	MoveTo *set;
	MoveTo *atk;

	MoveTo *out;
	

	DelayTime *delay;
	MoveTo *pback;
	Sequence *pseq1;
	Sequence *pseq2;
	Sequence *pseq3;
	Sequence *pseq4;
	Sequence *pseq5;
	Sequence *pseq6;

	bool isDelay;
	bool isDelay2;
	bool isDelay3;
	bool isDelay4;
	bool isDelay5;
	bool isDelay6;
	bool isDelay7;
	bool isDelay8;

	int playerhp;
	int bosshp;
	int playercost;
	int bosscost;
	int turn_on;
	int pre;

	MenuItemImage * HandDeck[5];
	Menu * HandMenu[5];

	void makebase();
	void makeupdate();
	void clickB(Ref * pSender);
	void clickturn(Ref * pSender);
	void clickHand(Ref * pSender, int i, int j);
	void playerturn();
	void bossturn();
	void fightturn();
	void gameclear();
	void setFightDeck();
	void showparticle(Ref * pSender);
	void showparticle2(Ref * pSender);


	int nNum;
	int nNum2;
	int nNum3;
	int nNum4;
	int nNum5;
	int nNum6;
	int nNum7;
	int nNum8;
	void callEveryFrame(float f);
};

#endif // __FightScene_SCENE_H__
