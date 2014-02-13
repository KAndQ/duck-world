//
//  IWMath.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-28.
//
//

#ifndef __DuckWorld__IWMath__
#define __DuckWorld__IWMath__

#include "IWTypes.h"

class IWWorld;
class IWPoint;

/**
 * 一些数据工具
 * @author Zhenyu Yao
 */
class IWMath
{
public:
	
	/**
	 * 从世界坐标的点转化为屏幕坐标系中使用的点
	 * @param point 世界坐标系的点
	 * @param world IWWorld 对象
	 * @return IWPoint 对象, 对于屏幕坐标系, x, y 是屏幕上对应的点, z 用来景深排序
	 */
	static IWPoint convertPointFromWorld(const IWPoint & point, IWWorld * world);
	
	/**
	 * 从屏幕坐标系转化为世界坐标系的点, 这个点的 Y 轴坐标为 0
	 * @param spoint 屏幕坐标系的点
	 * @param world IWWorld 对象
	 * @return world 中的点
	 */
	static IWPoint worldPointFromScreenPoint(const IWPoint & spoint, IWWorld * world);
	
	/**
	 * 将 point 做 x, y 轴的旋转
	 * @param point 待旋转的点
	 * @param xradian x轴的旋转弧度
	 * @param yradian y轴的旋转弧度
	 * @return 经过旋转后的坐标点
	 */
	static IWPoint rotatePointWithRadian(const IWPoint & point, IWFloat32 xradian, IWFloat32 yradian);
	
	/**
	 * 判断两个浮点数是否相等
	 * @param val1 值1
	 * @param val2 值2
	 * @return 相等返回 true, 否则返回 false
	 */
	static bool floatIsEqual(IWFloat64 val1, IWFloat64 val2);
};

#endif /* defined(__DuckWorld__IWMath__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


