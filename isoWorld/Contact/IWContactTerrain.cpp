//
//  IWContactTerrain.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-10.
//
//

#include "IWContactTerrain.h"
#include "isoWorld/Common/IWWorld.h"
#include "isoWorld/Common/IWMath.h"

static IWFloat32 BOUND = 0.5f;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWContactTerrain::IWContactTerrain(IWWorld * world)
{
	m_world = world;
}

IWContactTerrain::~IWContactTerrain()
{
}

void IWContactTerrain::detectEntityPosition(IWEntityMoveInfo & moveInfo)
{
	bool modified1 = false;
	bool modified2 = false;
	IWEntityMoveInfo tmpInfo = moveInfo;
	modified1 = detectEntityWithBorder(tmpInfo);
	IWEntityMoveInfo::XZDirection direction = tmpInfo.getXZDirection();
	
	// 八向检测
	switch (direction)
	{
		case IWEntityMoveInfo::kTop:
			modified2 = detectEntityWithTop(tmpInfo);
			break;
		case IWEntityMoveInfo::kLeftTop:
			modified2 = detectEntityWithLeftTop(tmpInfo);
			break;
		case IWEntityMoveInfo::kLeft:
			modified2 = detectEntityWithLeft(tmpInfo);
			break;
		case IWEntityMoveInfo::kLeftBottom:
			modified2 = detectEntityWithLeftBottom(tmpInfo);
			break;
		case IWEntityMoveInfo::kBottom:
			modified2 = detectEntityWithBottom(tmpInfo);
			break;
		case IWEntityMoveInfo::kRightBottom:
			modified2 = detectEntityWithRightBottom(tmpInfo);
			break;
		case IWEntityMoveInfo::kRight:
			modified2 = detectEntityWithRight(tmpInfo);
			break;
		case IWEntityMoveInfo::kRightTop:
			modified2 = detectEntityWithRightTop(tmpInfo);
			break;
		default:
			break;
	}
	
	if ((modified1 || modified2) && m_world->m_xzContactCallBack != NULL)
	{
		m_world->m_xzContactCallBack->XZContactCallBack(moveInfo.entity, moveInfo.newPos, tmpInfo.newPos, tmpInfo.lastPos);
	}
	
	// 更新的移动信息数据
	moveInfo = tmpInfo;
}

bool IWContactTerrain::detectEntityWithBorder(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	
	IWEntity * entity = moveInfo.entity;
	IWPoint & newPos = moveInfo.newPos;
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	
	if (newPos.x - entity->getOffset().left < 0)
	{
		newPos.x = entity->getOffset().left + BOUND;
		modified = true;
	}
	else if (newPos.x + entity->getOffset().right > terrain->getWidth())
	{
		newPos.x = terrain->getWidth() - entity->getOffset().right - BOUND;
		IWAssert(!IWMath::floatIsEqual(newPos.x, terrain->getWidth()));
		modified = true;
	}
	
	if (newPos.z - entity->getOffset().bottom < 0)
	{
		newPos.z = entity->getOffset().bottom + BOUND;
		modified = true;
	}
	else if (newPos.z + entity->getOffset().top > terrain->getHeight())
	{
		newPos.z = terrain->getHeight() - entity->getOffset().top - BOUND;
		IWAssert(!IWMath::floatIsEqual(newPos.z, terrain->getHeight()));
		modified = true;
	}
	
	if (modified)
		entity->m_pos = newPos;
	
	return modified;
}

bool IWContactTerrain::detectEntityWithTop(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	
	// 从 左顶点到右顶点 检测, 判断是否有障碍单元阻碍
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint leftTop = IWEntity::XZLeftTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint rightTop = IWEntity::XZRightTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint newPos = leftTop;
	IWFloat32 step = rightTop.x - leftTop.x;
	step = step < terrain->getGridSize() ? step : terrain->getGridSize();
	
	for (; newPos.x <= rightTop.x; newPos.x += step)
	{
		IWXZCell * cell = terrain->cellAtXZ(newPos.x, newPos.z);
		if (cell->getObstacleType() == IWXZCell::kObstacleType_NoEntry)
		{
			IWFloat32 z = cell->getRow() * terrain->getGridSize();
			newPos = moveInfo.newPos;
			newPos.z = z - moveInfo.entity->m_offset.top - BOUND;
			IWAssert(newPos.z != z);
			modified = true;
			break;
		}
	}
	
	if (modified)
	{
		moveInfo.entity->m_pos = newPos;
		moveInfo.newPos = newPos;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithLeft(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	
	// 从 左顶点到左下点 检测, 判断是否有障碍单元阻碍
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint leftTop = IWEntity::XZLeftTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint leftBottom = IWEntity::XZLeftBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint newPos = leftTop;
	IWFloat32 step = leftTop.z - leftBottom.z;
	step = step < terrain->getGridSize() ? step : terrain->getGridSize();
	
	for (; newPos.z >= leftBottom.z; newPos.z -= step)
	{
		IWXZCell * cell = terrain->cellAtXZ(newPos.x, newPos.z);
		if (cell->getObstacleType() == IWXZCell::kObstacleType_NoEntry)
		{
			IWFloat32 x = (cell->getCol() + 1) * terrain->getGridSize();
			newPos = moveInfo.newPos;
			newPos.x = x + moveInfo.entity->m_offset.left + BOUND;
			IWAssert(newPos.x != x);
			modified = true;
			break;
		}
	}
	
	if (modified)
	{
		moveInfo.entity->m_pos = newPos;
		moveInfo.newPos = newPos;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithBottom(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	
	// 从 左下点到右下点 检测, 判断是否有障碍单元阻碍
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint leftBottom = IWEntity::XZLeftBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint rightBottom = IWEntity::XZRightBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint newPos = leftBottom;
	IWFloat32 step = rightBottom.x - leftBottom.x;
	step = step < terrain->getGridSize() ? step : terrain->getGridSize();
	
	for (; newPos.x <= rightBottom.x; newPos.x += step)
	{
		IWXZCell * cell = terrain->cellAtXZ(newPos.x, newPos.z);
		if (cell->getObstacleType() == IWXZCell::kObstacleType_NoEntry)
		{
			IWFloat32 z = (cell->getRow() + 1) * terrain->getGridSize();
			newPos = moveInfo.newPos;
			newPos.z = z + moveInfo.entity->m_offset.bottom + BOUND;
			modified = true;
			break;
		}
	}
	
	if (modified)
	{
		moveInfo.entity->m_pos = newPos;
		moveInfo.newPos = newPos;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithRight(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	
	// 从 右上点到右下点 检测, 判断是否有障碍单元阻碍
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint rightTop = IWEntity::XZRightTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint rightBottom = IWEntity::XZRightBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint newPos = rightTop;
	IWFloat32 step = rightTop.z - rightBottom.z;
	step = step < terrain->getGridSize() ? step : terrain->getGridSize();
	
	for (; newPos.z >= rightBottom.z; newPos.z -= step)
	{
		IWXZCell * cell = terrain->cellAtXZ(newPos.x, newPos.z);
		if (cell->getObstacleType() == IWXZCell::kObstacleType_NoEntry)
		{
			IWFloat32 x = cell->getCol() * terrain->getGridSize();
			newPos = moveInfo.newPos;
			newPos.x = x - moveInfo.entity->m_offset.right - BOUND;
			modified = true;
			break;
		}
	}
	
	if (modified)
	{
		moveInfo.entity->m_pos = newPos;
		moveInfo.newPos = newPos;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithLeftTop(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWPoint delta = moveInfo.newPos - moveInfo.lastPos;
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint newLeftTop = IWEntity::XZLeftTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint lastLeftTop = IWEntity::XZLeftTopPoint(moveInfo.entity, moveInfo.lastPos);
	IWXZCell * newCell = terrain->cellAtXZ(newLeftTop.x, newLeftTop.z);
	IWXZCell * lastCell = terrain->cellAtXZ(lastLeftTop.x, lastLeftTop.z);
	
	// 根据位移的绝对大小判断使用的检测方式, 思路一样, 体验上会有略微的差别
	if (fabs(delta.x) >= fabs(delta.z))
	{
		// 新位置和上次的位置如果是在同一列, 则不用做 X 轴方向判断
		if (newCell->getCol() != lastCell->getCol())
			modified = detectEntityWithLeft(moveInfo);
		
		if (detectEntityWithTop(moveInfo) && !modified)
			modified = true;
	}
	else
	{
		// 新位置和上次的位置如果是在同一行, 则不用做 Z 轴方向的判断
		if (newCell->getRow() != lastCell->getRow())
			modified = detectEntityWithTop(moveInfo);
		
		if (detectEntityWithLeft(moveInfo) && !modified)
			modified = true;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithLeftBottom(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWPoint delta = moveInfo.newPos - moveInfo.lastPos;
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint newLeftBottom = IWEntity::XZLeftBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint lastLeftBottom = IWEntity::XZLeftBottomPoint(moveInfo.entity, moveInfo.lastPos);
	IWXZCell * newCell = terrain->cellAtXZ(newLeftBottom.x, newLeftBottom.z);
	IWXZCell * lastCell = terrain->cellAtXZ(lastLeftBottom.x, lastLeftBottom.z);
	
	// 参考 detectEntityWithLeftTop 函数
	if (fabs(delta.x) >= fabs(delta.z))
	{
		if (newCell->getCol() != lastCell->getCol())
			modified = detectEntityWithLeft(moveInfo);

		if (detectEntityWithBottom(moveInfo) && !modified)
			modified = true;
	}
	else
	{
		if (newCell->getRow() != lastCell->getRow())
			modified = detectEntityWithBottom(moveInfo);
		
		if (detectEntityWithLeft(moveInfo) && !modified)
			modified = true;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithRightBottom(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWPoint delta = moveInfo.newPos - moveInfo.lastPos;
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint newRightBottom = IWEntity::XZRightBottomPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint lastRightBottom = IWEntity::XZRightBottomPoint(moveInfo.entity, moveInfo.lastPos);
	IWXZCell * newCell = terrain->cellAtXZ(newRightBottom.x, newRightBottom.z);
	IWXZCell * lastCell = terrain->cellAtXZ(lastRightBottom.x, lastRightBottom.z);
	
	// 参考 detectEntityWithLeftTop 函数
	if (fabs(delta.x) >= fabs(delta.z))
	{
		if (newCell->getCol() != lastCell->getCol())
			modified = detectEntityWithRight(moveInfo);
		
		if (detectEntityWithBottom(moveInfo) && !modified)
			modified = true;
	}
	else
	{
		if (newCell->getRow() != lastCell->getRow())
			modified = detectEntityWithBottom(moveInfo);
		
		if (detectEntityWithRight(moveInfo) && !modified)
			modified = true;
	}
	
	return modified;
}

bool IWContactTerrain::detectEntityWithRightTop(IWEntityMoveInfo & moveInfo)
{
	bool modified = false;
	IWPoint delta = moveInfo.newPos - moveInfo.lastPos;
	IWXZTerrain * terrain = m_world->getCoordinate()->getTerrain();
	IWPoint newRightTop = IWEntity::XZRightTopPoint(moveInfo.entity, moveInfo.newPos);
	IWPoint lastRightTop = IWEntity::XZRightTopPoint(moveInfo.entity, moveInfo.lastPos);
	IWXZCell * newCell = terrain->cellAtXZ(newRightTop.x, newRightTop.z);
	IWXZCell * lastCell = terrain->cellAtXZ(lastRightTop.x, lastRightTop.z);
	
	if (fabs(delta.x) >= fabs(delta.z))
	{
		if (newCell->getCol() != lastCell->getCol())
			modified = detectEntityWithRight(moveInfo);
		
		if (detectEntityWithTop(moveInfo) && !modified)
			modified = true;
	}
	else
	{
		if (newCell->getRow() != lastCell->getRow())
			modified = detectEntityWithTop(moveInfo);
		
		if (detectEntityWithRight(moveInfo) && !modified)
			modified = true;
	}
	
	return modified;
}








































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


