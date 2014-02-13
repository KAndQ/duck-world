//
//  IWContactGradient.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-10.
//
//

#include "IWContactGradient.h"
#include "isoWorld/Common/IWWorld.h"

static const IWFloat32 BOUND = 0.5f;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWContactGradient::IWContactGradient(IWWorld * world) : m_world(NULL)
{
	m_world = world;
}

IWContactGradient::~IWContactGradient()
{
}

void IWContactGradient::detectEntityPosition(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWEntityMoveInfo tmpInfo = moveInfo;
	IWEntityMoveInfo::XYDirection direction = moveInfo.getXYDirection();
	
	switch (direction)
	{
		case IWEntityMoveInfo::kUp:
			break;
			
		case IWEntityMoveInfo::kDown:
			modified = detectEntityWithGround(tmpInfo);
			break;
			
		case IWEntityMoveInfo::kStand:
			break;
	}
	
	if (modified && m_world->m_xyContactCallBack != NULL)
	{
		m_world->m_xyContactCallBack->XYContactCallBack(moveInfo.entity, moveInfo.newPos, tmpInfo.newPos, tmpInfo.lastPos);
	}
	
	moveInfo = tmpInfo;
}

bool IWContactGradient::detectEntityWithGround(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWXYGradient * gradient = m_world->getCoordinate()->getGradient();
	IWPoint newDownPoint = IWEntity::XYDownPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint lastDownPoint = IWEntity::XYDownPoint(moveInfo.entity, moveInfo.lastPos);
	IWXYPath * searched1 = gradient->pathWithPoint_MinY(newDownPoint, true);
	IWXYPath * searched2 = gradient->pathWithPoint_MinY(lastDownPoint, false);
	
	// 两次位移之间夹着 Y 路径, 可以是同一条或者相连接的路径
	if (searched1 != NULL && searched2 != NULL && (searched1->isConnect(searched2) || searched1->isEqual(searched2)))
	{
		modified = true;
	}
	// 向下没有路径了, 那么只能以上路径为地面
	else if (searched1 != NULL && searched2 == NULL)
	{
		modified = true;
	}
	
	if (modified)
	{
		IWFloat32 y = searched1->YWithPoint(newDownPoint);
		IWPoint newPos = newDownPoint;
		newPos.y = y + moveInfo.entity->m_XYOffset.down;
		moveInfo.entity->m_pos = newPos;
		moveInfo.newPos = newPos;
//		moveInfo.entity->m_vel.y = 0.0f;
	}
	
	return modified;
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


