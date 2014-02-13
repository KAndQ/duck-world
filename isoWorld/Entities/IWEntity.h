//
//  IWEntity.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#ifndef __DuckWorld__IWEntity__
#define __DuckWorld__IWEntity__

#include "isoWorld/Common/IWPoint.h"
#include "isoWorld/Common/IWRect.h"
#include "IWEntityDelegate.h"

class IWWorld;

/**
 * Entity XZ 坐标中的判断区域, 必须非 0.
 * @author Zhenyu Yao
 */
class IWXZOffset
{
public:
	
	IWXZOffset(IWFloat32 t = 1.0f, IWFloat32 b = 1.0f, IWFloat32 l = 1.0f, IWFloat32 r = 1.0f)
	{
		top = t;
		bottom = b;
		left = l;
		right = r;
	}
	
	~IWXZOffset()
	{
	}
	
	IWFloat32 top;
	IWFloat32 bottom;
	IWFloat32 left;
	IWFloat32 right;
};

/**
 * Entity XY 坐标中的偏移量, 必须非 0
 * @author Zhenyu Yao
 */
class IWXYOffset
{
public:
	
	IWXYOffset(IWFloat32 u = 1.0f, IWFloat32 d = 1.0f)
	{
		up = u;
		down = d;
	}
	
	~IWXYOffset()
	{
	}
	
	IWFloat32 up;
	IWFloat32 down;
};

/**
 * 世界中的实体
 * @author Zhenyu Yao
 */
class IWEntity
{
public:
	
	/* 使用 Entity 的 offset 计算 XZ 坐标轴上的 pos 对应的点 */
	
	static IWPoint XZTopPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZLeftTopPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZLeftPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZLeftBottomPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZBottomPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZRightBottomPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZRightPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XZRightTopPoint(const IWEntity * entity, const IWPoint & pos);
	
	/* 使用 Entity 的 XYOffset 计算 XY 坐标轴上的 pos 对应的点 */
	
	static IWPoint XYUpPoint(const IWEntity * entity, const IWPoint & pos);
	static IWPoint XYDownPoint(const IWEntity * entity, const IWPoint & pos);
	
public:
	
	IWEntity();
	~IWEntity();
	
	/// 当前实体所在的 IWWorld
	IWWorld * getWorld() { return m_world; }
	
	const IWPoint & getPos() const { return m_pos; }
	void setPos(const IWPoint & pos);
	
	IWPoint & getVel() { return m_vel; }
	void setVel(const IWPoint & vel) { m_vel = vel; }
	
	IWPoint & getAcc() { return m_acc; }
	void setAcc(const IWPoint & acc) { m_acc = acc; }
	
	IWXZOffset & getOffset() { return m_offset; }
	void setOffset(const IWXZOffset & offset) { m_offset = offset; }
	
	IWXYOffset & getXYOffset() { return m_XYOffset; }
	void setOffset(const IWXYOffset & offset) { m_XYOffset = offset; }
	
	IWEntityDelegate * getDelegate() const { return m_delegate; }
	void setDelegate(IWEntityDelegate * delegate) { m_delegate = delegate; }
	
private:
	
	IWPoint m_pos;
	IWPoint m_vel;
	IWPoint m_acc;
	IWXZOffset m_offset;
	IWXYOffset m_XYOffset;
	IWWorld * m_world;
	IWEntityDelegate * m_delegate;
	
	friend class IWWorld;
	friend class IWEntityMoveController;
	friend class IWContactTerrain;
	friend class IWContactGradient;
};

#endif /* defined(__DuckWorld__IWEntity__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


