//
//  IWPoint.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWPoint__
#define __DuckWorld__IWPoint__

#include "IWTypes.h"

/**
 * 点
 * @author Zhenyu Yao
 */
class IWPoint
{
public:
	
	/// 创建 IWPoint 对象
	static IWPoint createIWPoint(IWFloat32 x = 0, IWFloat32 y = 0, IWFloat32 z = 0)
	{
		return IWPoint(x, y, z);
	}
	
	IWPoint(IWFloat32 x1 = 0, IWFloat32 y1 = 0, IWFloat32 z1 = 0)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	
	~IWPoint()
	{
	}
	
	/* 和一个自然数的 +-x÷ 元算 */
	
	IWPoint operator + (IWFloat32 value) const
	{
		return IWPoint(this->x + value, this->y + value, this->z + value);
	}
	
	IWPoint operator - (IWFloat32 value) const
	{
		return IWPoint(this->x - value, this->y - value, this->z - value);
	}
	
	IWPoint operator * (IWFloat32 value) const
	{
		return IWPoint(this->x * value, this->y * value, this->z * value);
	}
	
	IWPoint operator / (IWFloat32 value) const
	{
		return IWPoint(this->x / value, this->y / value, this->z / value);
	}
	
	/* 和一个 IWPoint 的 +-x÷ 元算 */
	
	IWPoint operator + (const IWPoint & value) const
	{
		return IWPoint(this->x + value.x, this->y + value.y, this->z + value.z);
	}
	
	IWPoint operator - (const IWPoint & value) const
	{
		return IWPoint(this->x - value.x, this->y - value.y, this->z - value.z);
	}
	
	IWPoint operator * (const IWPoint & value) const
	{
		return IWPoint(this->x * value.x, this->y * value.y, this->z * value.z);
	}
	
	IWPoint operator / (const IWPoint & value) const
	{
		return IWPoint(this->x / value.x, this->y / value.y, this->z / value.z);
	}
	
	/* 双目运算符: 与一个自然数的 += -= *= /= 元算 */

	IWPoint & operator += (IWFloat32 value)
	{
		this->x += value;
		this->y += value;
		this->z += value;
		return *this;
	}
	
	IWPoint & operator -= (IWFloat32 value)
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		return *this;
	}
	
	IWPoint & operator *= (IWFloat32 value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}
	
	IWPoint & operator /= (IWFloat32 value)
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
		return *this;
	}
	
	/* 双目运算符: 与一个 IWPoint 的 += -= *= /= 元算 */
	IWPoint & operator += (const IWPoint & value)
	{
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;
		return *this;
	}
	
	IWPoint & operator -= (const IWPoint & value)
	{
		this->x -= value.x;
		this->y -= value.y;
		this->z -= value.z;
		return *this;
	}
	
	IWPoint & operator *= (const IWPoint & value)
	{
		this->x *= value.x;
		this->y *= value.y;
		this->z *= value.z;
		return *this;
	}
	
	IWPoint & operator /= (const IWPoint & value)
	{
		this->x /= value.x;
		this->y /= value.y;
		this->z /= value.z;
		return *this;
	}
	
	/// 判断两个 IWPoint 是否相等
	bool operator == (const IWPoint & value) const
	{
		return this->x == value.x && this->y == value.y && this->z == value.z;
	}
	
	bool operator != (const IWPoint & value) const
	{
		return !(*this == value);
	}
	
	/// 判断当前的 IWPoint x/y/z 三个数值是否全部为 0
	bool isZero() const
	{
		return this->x == 0.0f && this->y == 0.0f && this->z == 0.0f;
	}
	
	IWPoint clone() const
	{
		return IWPoint(this->x, this->y, this->z);
	}
	
	IWFloat32 x;
	IWFloat32 y;
	IWFloat32 z;
};

#endif /* defined(__DuckWorld__IWPoint__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


