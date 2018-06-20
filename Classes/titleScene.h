#ifndef __titleScene_SCENE_H__
#define __titleScene_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class titleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Layer * voidNode;
	Sprite * cground;

	void clickstart(Ref * pSender);
	

	CREATE_FUNC(titleScene);
};

#endif // __titleScene_SCENE_H__
