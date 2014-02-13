//
//  IWBevelPlaneConverter.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#include "IWBevelPlaneConverter.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWPoint IWBevelPlaneConverter::screenPointFromWorldPoint(const IWPoint & point, IWWorld * world)
{
	return IWPoint(point.x, point.z + point.y, point.z);
}

IWPoint IWBevelPlaneConverter::worldPointFromScreenPoint(const IWPoint & point, IWWorld * world)
{
	return IWPoint(point.x, 0.0f, point.y);
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


