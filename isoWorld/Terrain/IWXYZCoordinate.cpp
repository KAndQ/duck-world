//
//  IWXYZCoordinate.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-28.
//
//

#include "isoWorld/Common/IWMacro.h"
#include "IWXYZCoordinate.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWXYZCoordinate::IWXYZCoordinate(IWXZTerrain * terrain, IWXYGradient * gradient)
{
	m_terrain = terrain;
	m_gradient = gradient;
	
	m_terrain->m_coordinate = this;
	m_gradient->m_coordinate = this;
}

IWXYZCoordinate::~IWXYZCoordinate()
{
	IW_SAFE_DELETE(m_terrain);
	IW_SAFE_DELETE(m_gradient);
}

IWPoint IWXYZCoordinate::groundPointWithPoint(const IWPoint & point)
{
	IWAssert(0 <= point.x && point.x < m_terrain->getWidth());
	IWAssert(0 <= point.z && point.z < m_terrain->getHeight());
	IWFloat32 y = m_gradient->minYWithPoint(point, false);
	IWPoint tmp = point.clone();
	tmp.y = y;
	return tmp;
}

IWPoint IWXYZCoordinate::minPointWithPoint(const IWPoint & point)
{
	IWAssert(0 <= point.x && point.x < m_terrain->getWidth());
	IWAssert(0 <= point.z && point.z < m_terrain->getHeight());
	IWXYPath * topPath = m_gradient->pathWithPoint_MinY(point, true);
	IWXYPath * bottomPath = m_gradient->pathWithPoint_MinY(point, false);
	IWFloat32 minY = 0.0f;
	if (topPath != NULL && bottomPath != NULL)
	{
		IWFloat32 topY = topPath->YWithPoint(point);
		IWFloat32 bottomY = bottomPath->YWithPoint(point);
		minY = (topY - point.y < point.y - bottomY) ? topY : bottomY;
	}
	else if (topPath == NULL && bottomPath != NULL)
		minY = bottomPath->YWithPoint(point);
	else if (bottomPath == NULL && topPath != NULL)
		minY = topPath->YWithPoint(point);
	
	IWPoint tmp = point.clone();
	tmp.y = minY;
	return tmp;
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


