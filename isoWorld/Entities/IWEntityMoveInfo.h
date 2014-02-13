//
//  IWEntityMoveInfo.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-10.
//
//

#ifndef __DuckWorld__IWEntityMoveInfo__
#define __DuckWorld__IWEntityMoveInfo__

#include "IWEntity.h"
#include "isoWorld/Common/IWMath.h"

/**
 * Entity 的移动数据
 * @author Zhenyu Yao
 */
class IWEntityMoveInfo
{
public:
	
	/// XZ 移动的方向
	enum XZDirection
	{
		kNone,			// 无移动
		kTop,			// 上
		kLeftTop,		// 左上
		kLeft,			// 上
		kLeftBottom,	// 左下
		kBottom,		// 下
		kRightBottom,	// 右下
		kRight,			// 右
		kRightTop		// 右上
	};
	
	/// XY 移动方向
	enum XYDirection
	{
		kStand,			// 无移动
		kUp,			// 上
		kDown,			// 下
	};
	
	/**
	 * 根据两点的位置计算当前的方向
	 * @param newPos 新的位置
	 * @param lastPos 之前的位置
	 * @return 方向
	 */
	static IWEntityMoveInfo::XZDirection XZDirectionWithPositions(const IWPoint & newPos, const IWPoint & lastPos)
	{
		if (IWMath::floatIsEqual(lastPos.x, newPos.x) && IWMath::floatIsEqual(lastPos.z, newPos.z))
			return IWEntityMoveInfo::kNone;
		else if (IWMath::floatIsEqual(lastPos.x, newPos.x) && lastPos.z < newPos.z)
			return IWEntityMoveInfo::kTop;
		else if (lastPos.x > newPos.x && lastPos.z < newPos.z)
			return IWEntityMoveInfo::kLeftTop;
		else if (lastPos.x > newPos.x && IWMath::floatIsEqual(lastPos.z, newPos.z))
			return IWEntityMoveInfo::kLeft;
		else if (lastPos.x > newPos.x && lastPos.z > newPos.z)
			return IWEntityMoveInfo::kLeftBottom;
		else if (IWMath::floatIsEqual(lastPos.x, newPos.x) && lastPos.z > newPos.z)
			return IWEntityMoveInfo::kBottom;
		else if (lastPos.x < newPos.x && lastPos.z > newPos.z)
			return IWEntityMoveInfo::kRightBottom;
		else if (lastPos.x < newPos.x && IWMath::floatIsEqual(lastPos.z, newPos.z))
			return IWEntityMoveInfo::kRight;
		else if (lastPos.x < newPos.x && lastPos.z < newPos.z)
			return IWEntityMoveInfo::kRightTop;
		
		return IWEntityMoveInfo::kNone;
	}
	
	static IWEntityMoveInfo::XYDirection XYDirectionWithPositions(const IWPoint & newPos, const IWPoint & lastPos)
	{
		if (IWMath::floatIsEqual(lastPos.x, newPos.x) && IWMath::floatIsEqual(lastPos.y, newPos.y))
			return IWEntityMoveInfo::kStand;
		else if (newPos.y > lastPos.y)
			return IWEntityMoveInfo::kUp;
		else if (newPos.y < lastPos.y)
			return IWEntityMoveInfo::kDown;
		
		return IWEntityMoveInfo::kStand;
	}
	
	IWEntityMoveInfo(IWEntity * entity = NULL, const IWPoint & lastPos = IWPoint(), const IWPoint & newPos = IWPoint())
	{
		this->entity = entity;
		this->lastPos = lastPos;
		this->newPos = newPos;
	}
	
	/// 由 lastPos 和 newPos 得到当前 XZ 轴上的移动方向
	XZDirection getXZDirection() const
	{
		return XZDirectionWithPositions(newPos, lastPos);
	}
	
	XYDirection getXYDirection() const
	{
		return XYDirectionWithPositions(newPos, lastPos);
	}
	
	~IWEntityMoveInfo()
	{
	}
	
	IWEntity * entity;
	IWPoint lastPos;
	IWPoint newPos;
};

#endif /* defined(__DuckWorld__IWEntityMoveInfo__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


