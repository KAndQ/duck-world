//
//  IWCoordConverter.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#ifndef __DuckWorld__IWCoordConverter__
#define __DuckWorld__IWCoordConverter__

#include "isoWorld/Common/IWPoint.h"
#include "isoWorld/Common/IWMacro.h"
#include "isoWorld/Common/IWWorld.h"

/**
 * 坐标转换工具的抽象类
 * @author Zhenyu Yao
 */
class IWCoordConverter
{
public:
	
	IWCoordConverter() {}
	virtual ~IWCoordConverter() {}
	
	/**
	 * 世界中的一个点到屏幕点的位置
	 * @param point 世界中的 point
	 * @param world IWWorld 对象
	 * @return 屏幕上的 point
	 */
	virtual IWPoint screenPointFromWorldPoint(const IWPoint & point, IWWorld * world) = 0;
	
	/**
	 * 屏幕上的一点转换到世界中的点
	 * @param point 屏幕上的 point
	 * @param world IWWorld 对象
	 * @return 世界中的 point
	 */
	virtual IWPoint worldPointFromScreenPoint(const IWPoint & point, IWWorld * world) = 0;
};

#endif /* defined(__DuckWorld__IWCoordConverter__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


