#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "isoWorld/Common/IWWorld.h"
#include "isoWorld/Common/CoordConverter/IWBevelPlaneConverter.h"

class HelloWorld : public cocos2d::CCLayer, public cocos2d::CCStandardTouchDelegate, public IWXZContactTerrainCallBack, public IWXYContactGradientCallBack
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	
	virtual void update(float dt);
	
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	
	virtual void XZContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos);
	virtual void XYContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos);
	
private:
	
	void drawCells();
	
	cocos2d::CCNode * m_container;
	cocos2d::CCDrawNode * m_drawNode;
	cocos2d::CCSprite * m_role;
	cocos2d::CCSprite * m_shadow;
	
	IWWorld * m_world;
	IWEntity * m_roleEntity;
	IWBevelPlaneConverter * m_converter;
};

#endif // __HELLOWORLD_SCENE_H__
