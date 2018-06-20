#ifndef __ChoicestoryScene_SCENE_H__
#define __ChoicestoryScene_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ChoicestoryScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Layer * voidNode;
	Sprite * cground;

	void clickback(Ref * pSender);
	void clickchap1(Ref * pSender);
	void clickchap2(Ref * pSender);
	void clickchap3(Ref * pSender);

	CREATE_FUNC(ChoicestoryScene);
};

#endif // __ChoicestoryScene_SCENE_H__
