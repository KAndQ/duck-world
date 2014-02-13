//
//  IWRect.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef DuckWorld_IWRect_h
#define DuckWorld_IWRect_h

#include "IWPoint.h"

/**
 * 3D 长方体
 * @author Zhenyu Yao
 */
class IWRect3D
{
public:
	
	/// 创建 IWRect 对象
	static IWRect3D createIWRect(const IWPoint & o = IWPoint(), IWFloat32 l = 0.0f, IWFloat32 w = 0.0f, IWFloat32 h = 0.0f)
	{
		return IWRect3D(o, l, w, h);
	}
	
	IWRect3D(const IWPoint & o = IWPoint(), IWFloat32 l = 0.0f, IWFloat32 w = 0.0f, IWFloat32 h = 0.0f)
	{
		origin = o;
		length = l;
		width = w;
		height = h;
	}
	
	~IWRect3D()
	{
	}
	
	IWFloat32 length;		// 长
	IWFloat32 width;		// 宽
	IWFloat32 height;		// 高
	IWPoint origin;			// 原点
};

/**
 * 2D 矩形
 * @author Zhenyu Yao
 */
class IWRect2D
{
public:
	
	IWRect2D(IWFloat32 x = 0.0f, IWFloat32 y = 0.0f, IWFloat32 w = 0.0f, IWFloat32 h = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	
	~IWRect2D()
	{
	}
	
	IWFloat32 x;		// x 坐标
	IWFloat32 y;		// y 坐标
	IWFloat32 w;		// 宽
	IWFloat32 h;		// 高
};

#endif














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


