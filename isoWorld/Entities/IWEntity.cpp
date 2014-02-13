//
//  IWEntity.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#include "IWEntity.h"
#include "isoWorld/Common/IWWorld.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWPoint IWEntity::XZTopPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z += entity->m_offset.top;
	return newPos;
}

IWPoint IWEntity::XZLeftTopPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z += entity->m_offset.top;
	newPos.x -= entity->m_offset.left;
	return newPos;
}

IWPoint IWEntity::XZLeftPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.x -= entity->m_offset.left;
	return newPos;
}

IWPoint IWEntity::XZLeftBottomPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z -= entity->m_offset.bottom;
	newPos.x -= entity->m_offset.left;
	return newPos;
}

IWPoint IWEntity::XZBottomPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z -= entity->m_offset.bottom;
	return newPos;
}

IWPoint IWEntity::XZRightBottomPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z -= entity->m_offset.bottom;
	newPos.x += entity->m_offset.right;
	return newPos;
}

IWPoint IWEntity::XZRightPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.x += entity->m_offset.right;
	return newPos;
}

IWPoint IWEntity::XZRightTopPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.z += entity->m_offset.top;
	newPos.x += entity->m_offset.right;
	return newPos;
}

IWPoint IWEntity::XYUpPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.y += entity->m_XYOffset.up;
	return newPos;
}

IWPoint IWEntity::XYDownPoint(const IWEntity * entity, const IWPoint & pos)
{
	IWPoint newPos = pos;
	newPos.y -= entity->m_XYOffset.down;
	return newPos;
}

IWEntity::IWEntity() : m_world(NULL), m_delegate(NULL)
{
}

IWEntity::~IWEntity()
{
}

void IWEntity::setPos(const IWPoint & pos)
{
	if (m_pos != pos)
	{
		IWPoint lastPos = m_pos;
		IWPoint newPos = pos;
		
		m_pos = pos;
		if (m_delegate != NULL)
			m_delegate->positionChanged(this, lastPos, newPos);
	}
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


