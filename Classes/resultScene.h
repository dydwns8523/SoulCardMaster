#ifndef __ChoicestoryScene_SCENE_H__
#define __ChoicestoryScene_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class resultScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Layer * voidNode;
	Sprite * cground;
	Sprite * goldbar;
	Label * label;
	string sgold;
	int getgold;

	CREATE_FUNC(resultScene);
	
	void clickcheck(Ref * pSender);

	void makebase();
	void makeparticle();
};

#endif // __ChoicestoryScene_SCENE_H__
