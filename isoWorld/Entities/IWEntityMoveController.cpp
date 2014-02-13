//
//  IWEntityMoveController.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-8.
//
//

#include "IWEntityMoveController.h"
#include "isoWorld/Common/IWWorld.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWEntityMoveController::IWEntityMoveController(IWWorld * world) :
m_contactTerrain(NULL),
m_contactGradient(NULL),
m_world(NULL)
{
	m_world = world;
	m_contactTerrain = new IWContactTerrain(m_world);
	m_contactGradient = new IWContactGradient(m_world);
}

IWEntityMoveController::~IWEntityMoveController()
{
	IW_SAFE_DELETE(m_contactTerrain);
	IW_SAFE_DELETE(m_contactGradient);
}

void IWEntityMoveController::update(IWFloat32 dt)
{
	vector<IWEntity *>::iterator beg = m_world->m_entities.begin();
	vector<IWEntity *>::iterator end = m_world->m_entities.end();
	for (; beg != end; ++beg)
	{
		IWEntity * entity = *beg;
		IWPoint lastPos = entity->m_pos;
		
		// 移动
		entity->m_pos += entity->m_vel * dt;
		entity->m_vel += entity->m_acc * dt;
		entity->m_vel.y += m_world->m_gravity * dt;
		
		// 记录移动数据
		IWEntityMoveInfo info;
		info.entity = entity;
		info.lastPos = lastPos;
		info.newPos = entity->m_pos;
		
		m_moveInfos[entity] = info;
	}
	
	// 位置检测
	map<IWEntity *, IWEntityMoveInfo>::iterator infoBeg = m_moveInfos.begin();
	map<IWEntity *, IWEntityMoveInfo>::iterator infoEnd = m_moveInfos.end();
	for (; infoBeg != infoEnd; ++infoBeg)
	{
		IWEntityMoveInfo info = infoBeg->second;
		changeEntityPosition(info);
	}
	
	// 清空记录的移动数据
	m_moveInfos.clear();
}

void IWEntityMoveController::changeEntityPosition(const IWEntityMoveInfo & moveInfo)
{
	IWEntityMoveInfo tmpInfo = moveInfo;
	m_contactTerrain->detectEntityPosition(tmpInfo);
	m_contactGradient->detectEntityPosition(tmpInfo);
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


