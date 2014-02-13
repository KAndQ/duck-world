#include "HelloWorldScene.h"
#include "isoWorld/Terrain/IWXZTerrain.h"
#include "isoWorld/Terrain/IWXYGradient.h"
#include "isoWorld/Terrain/IWXYZCoordinate.h"
#include "isoWorld/Common/IWWorld.h"
#include "isoWorld/Common/IWMath.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static IWPoint testConvert(const IWPoint & point, IWWorld * world)
{
	IWFloat32 yradian = world->getYRadian();
	IWFloat32 xradian = world->getXRadian();
	IWFloat32 sx = point.x * cos(yradian) - point.z * sin(yradian);
	IWFloat32 z1 = point.z * cos(yradian) + point.x * sin(yradian);
	IWFloat32 z2 = point.y * cos(xradian) - z1 * sin(xradian);
	IWFloat32 sy = z1 * cos(xradian) - point.y * sin(xradian);
	
	return IWPoint(sx, sy, z2);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	
	IWWorld * world = new IWWorld();
	
	// terrain
	IWXZTerrain * terrain = world->createTerrain(IWXZTerrainDef(4, 4, 16));
//	terrain->cellAt(2, 4)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(3, 4)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(4, 4)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(2, 3)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(4, 3)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(2, 2)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(3, 2)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	terrain->cellAt(4, 2)->setObstacleType(IWXZCell::kObstacleType_NoEntry);
//	
	// gradient
	IWXYGradient * gradient = world->createGradient();
	IWXYPath * path1 = gradient->addPath(0, 0, 0, 64, 32, 0.0f);
	IWXYPath * path2 = gradient->addPath(32, 0, 0, 64, 64, M_PI / 6.0f);
	path1->setNext(path2);
	path2->setPrev(path1);
	
	IWXYZCoordinate * coordinate = world->createCoordinate(terrain, gradient);
	world->setCoordinate(coordinate);
	m_world = world;
	m_world->setXZContactCallBack(this);
	m_world->setXYContactCallBack(this);
	m_world->setGravity(-300.0f);
	
	m_converter = new IWBevelPlaneConverter();
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width * 0.5f, winSize.height * 0.5f);
	
	m_container = CCNode::create();
	m_container->setPosition(center);
	this->addChild(m_container);
	
	CCSprite * background = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("Background.png"));
	m_container->addChild(background);
	
	m_drawNode = CCDrawNode::create();
	m_container->addChild(m_drawNode);
	
	m_shadow = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("shadow.png"));
	m_container->addChild(m_shadow);
	
	m_role = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("Icon-57.png"));
	m_container->addChild(m_role);
	
	m_role->setScale(0.15f);
	m_shadow->setScale(0.15f);
	
	CCMenuItemLabel * label = CCMenuItemLabel::create(CCLabelTTF::create("Jump", "Arial", 20),
													  this, callfuncO_selector(HelloWorld::menuCloseCallback));
	label->setPosition(ccp(50, 300));
	CCMenu * menu = CCMenu::createWithItem(label);
	menu->setPosition(CCPointZero);
	menu->setAnchorPoint(CCPointZero);
	this->addChild(menu);
	
	this->scheduleUpdate();
	
	this->setTouchEnabled(true);
	
	m_roleEntity = world->createEntity();
//	m_roleEntity->setPos(IWPoint(0 * terrain->getGridSize() + terrain->getGridSize() * 0.5f,
//								 0.0f,
//								 0 * terrain->getGridSize() + terrain->getGridSize() * 0.5f));
	m_roleEntity->getOffset().top = 2;
	m_roleEntity->getOffset().bottom = 2;
	m_roleEntity->getOffset().left = 2;
	m_roleEntity->getOffset().right = 2;
//	m_roleEntity->getXYOffset().down = 2;
//	m_roleEntity->getXYOffset().up = 2;
	
	drawCells();
	
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	m_roleEntity->getVel().y = 150.0f;
}

void HelloWorld::update(float dt)
{
	dt = 0.016;
	
	m_world->update(dt);
	
	IWPoint position = m_roleEntity->getPos();
	IWPoint point = m_converter->screenPointFromWorldPoint(position, m_world);
	m_role->setPosition(ccp(point.x, point.y));
	
//	point = m_converter->screenPointFromWorldPoint(IWPoint(position.x, 0.0f, position.z), m_world);
//	m_shadow->setPosition(ccp(point.x, point.y));
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch * touch = (CCTouch *)pTouches->anyObject();
	CCPoint touchPoint = this->convertTouchToNodeSpace(touch);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	// 左
	if (touchPoint.x < winSize.width * 0.33f)
	{
		m_roleEntity->getVel().x = -100.0f;
//		m_roleEntity->getVel().z = 100.0f;
	}
	else if (winSize.width * 0.33f < touchPoint.x && touchPoint.x < winSize.width * 0.66f)
	{
		// 上
		if (winSize.height * 0.5f < touchPoint.y)
		{
			m_roleEntity->getVel().z = 100.0f;
		}
		// 下
		else
		{
			m_roleEntity->getVel().z = -100.0f;
		}
	}
	// 右
	else if (winSize.width * 0.66f < touchPoint.x)
	{
		m_roleEntity->getVel().x = 100.0f;
//		m_roleEntity->getVel().z = 100.0f;
	}
}

void HelloWorld::ccTouchesEnded(CCSet * pTouches, CCEvent * pEvent)
{
	m_roleEntity->getVel().x = m_roleEntity->getVel().z = 0.0f;
}

void HelloWorld::drawCells()
{
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	for (int c = 0; c < terrain->getWidthCount(); ++c)
	{
		for (int r = 0; r < terrain->getHeightCount(); ++r)
		{
			IWXZCell * cell = terrain->cellAt(c, r);
			ccColor4F fillColor;
			if (cell->getObstacleType() == IWXZCell::kObstacleType_None)
				fillColor = ccc4f(0.0f, 1.0f, 0.0f, 1.0f);
			else
				fillColor = ccc4f(1.0f, 0.0f, 0.0f, 1.0f);
			
			CCPoint verts[4];
			IWFloat32 gridSize = terrain->getGridSize();
			verts[0] = ccp(c * gridSize, r * gridSize);
			verts[1] = ccp((c + 1) * gridSize, r * gridSize);
			verts[2] = ccp((c + 1) * gridSize, (r + 1) * gridSize);
			verts[3] = ccp(c * gridSize, (r + 1) * gridSize);
			
			m_drawNode->drawPolygon(verts, 4, fillColor, 0.3f, ccc4f(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

void HelloWorld::XZContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos)
{
	static unsigned int s_count = 0;
	CCLOG("---- XZ: 发生碰撞 %u ----", ++s_count);
}

void HelloWorld::XYContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos)
{
//	static unsigned int s_count = 0;
//	CCLOG("---- XY: 发生碰撞 %u ----", ++s_count);
}





































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


