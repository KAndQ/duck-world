//
//  IWWorld.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#include "IWWorld.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWWorld::IWWorld() :
m_gravity(0.0f),
m_xradian(0.0f),
m_yradian(0.0f),
m_coordinate(NULL),
m_moveController(NULL),
m_xzContactCallBack(NULL),
m_xyContactCallBack(NULL)
{
	m_moveController = new IWEntityMoveController(this);
}

IWWorld::~IWWorld()
{
	vector<IWEntity *>::iterator beg = m_entities.begin();
	vector<IWEntity *>::iterator end = m_entities.end();
	for (; beg != end; ++beg)
		IW_SAFE_DELETE(*beg);
	
	IW_SAFE_DELETE(m_coordinate);
	IW_SAFE_DELETE(m_moveController);
}

void IWWorld::update(IWFloat32 dt)
{
	m_moveController->update(dt);
}

IWXYZCoordinate * IWWorld::createCoordinate(IWXZTerrain * terrain, IWXYGradient * gradient)
{
	IWXYZCoordinate * coordinate = new IWXYZCoordinate(terrain, gradient);
	return coordinate;
}

void IWWorld::destroyCoordinate(IWXYZCoordinate * coordinate)
{
	IW_SAFE_DELETE(coordinate);
}

IWXZTerrain * IWWorld::createTerrain(const IWXZTerrainDef & def)
{
	IWXZTerrain * terrain = new IWXZTerrain(def.widthCount, def.heightCount, def.gridSize);
	return terrain;
}

void IWWorld::destroyTerrain(IWXZTerrain * terrain)
{
	IW_SAFE_DELETE(terrain);
}

IWXYGradient * IWWorld::createGradient()
{
	IWXYGradient * gradient = new IWXYGradient();
	return gradient;
}

void IWWorld::destroyGradient(IWXYGradient * gradient)
{
	IW_SAFE_DELETE(gradient);
}

IWEntity * IWWorld::createEntity()
{
	IWEntity * entity = new IWEntity();
	entity->m_world = this;
	entity->setDelegate(this);
	m_entities.push_back(entity);
	return entity;
}

void IWWorld::destroyEntity(IWEntity * entity)
{
	IWAssert(entity != NULL);
	vector<IWEntity *>::iterator beg = m_entities.begin();
	vector<IWEntity *>::iterator end = m_entities.end();
	for (; beg != end; ++beg)
	{
		if (*beg == entity)
		{
			m_entities.erase(beg);
			IW_SAFE_DELETE(entity);
			continue;
		}
	}
}

vector<IWEntity *> IWWorld::getEntities()
{
	vector<IWEntity *> copy;
	copy.assign(m_entities.begin(), m_entities.end());
	return copy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface - IWEntityDelegate
////////////////////////////////////////////////////////////////////////////////////////////////////

void IWWorld::positionChanged(IWEntity * entity, const IWPoint & lastPos, const IWPoint & newPos)
{
	m_moveController->changeEntityPosition(IWEntityMoveInfo(entity, lastPos, newPos));
}








































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


