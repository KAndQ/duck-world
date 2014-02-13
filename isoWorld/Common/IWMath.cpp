//
//  IWMath.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-28.
//
//

#include <math.h>
#include "IWMath.h"
#include "IWWorld.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWPoint IWMath::convertPointFromWorld(const IWPoint & point, IWWorld * world)
{
	IWFloat32 xradian = world->getXRadian();
	IWFloat32 yradian = world->getYRadian();
	return rotatePointWithRadian(point, xradian, yradian);
}

IWPoint IWMath::worldPointFromScreenPoint(const IWPoint & spoint, IWWorld * world)
{
	IWFloat32 xradian = -world->getXRadian();
	IWFloat32 yradian = -world->getYRadian();
	
	// 逆旋转, 先 Y 轴, 再 X 轴
	IWPoint point = rotatePointWithRadian(spoint, 0.0f, yradian);
	return rotatePointWithRadian(point, xradian, 0.0f);
}

IWPoint IWMath::rotatePointWithRadian(const IWPoint & point, IWFloat32 xradian, IWFloat32 yradian)
{
	// 1. 垂足点在平面上;
	// 2. 面向垂足点, 指向右的为横轴正方向, 指向上的为纵轴正方向
	// 3. 逆时针为正角, 顺时针为负角;
	// 4. 先旋转 y 轴, 再旋转 x 轴;
	
	// waiting optimize
	
	IWFloat32 x1 = point.x * cos(yradian) - point.z * sin(yradian);
	IWFloat32 z1 = point.z * cos(yradian) + point.x * sin(yradian);
	IWFloat32 y1 = point.y * cos(xradian) - z1 * sin(xradian);
	IWFloat32 z2 = z1 * cos(xradian) + point.y * sin(xradian);
	
//	IWFloat32 y1 = cos(xradian) * point.y - sin(xradian) * point.z;
//	IWFloat32 z1 = cos(xradian) * point.z + sin(xradian) * point.y;
//	IWFloat32 z2 = cos(yradian) * z1 - sin(yradian) * point.x;
//	IWFloat32 x1 = cos(yradian) * point.x + sin(yradian) * z1;
	
	return IWPoint(x1, y1, z2);
}

bool IWMath::floatIsEqual(IWFloat64 val1, IWFloat64 val2)
{
	IWFloat64 result = val1 - val2;
	return fabs(result) < 0.0001;
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


