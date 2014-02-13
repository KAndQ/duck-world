//
//  IWContactGradient.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-8.
//
//

#ifndef __DuckWorld__IWContactGradient__
#define __DuckWorld__IWContactGradient__

#include "isoWorld/Entities/IWEntityMoveInfo.h"

class IWWorld;

/**
 * 当在 XY 轴方向与障碍格子或者边界发生碰撞时候的回调
 * @author Zhenyu Yao
 */
class IWXYContactGradientCallBack
{
public:
	
	/**
	 * 解除回调
	 * @param entity 触发的 IWEntity 对象
	 * @param newPos1 如果不发生碰撞会到达的位置
	 * @param newPos2 当前的实际位置, 它与当前的 entity->getPos() 得到的值相同
	 * @param lastPos 上次所在的位置
	 */
	virtual void XYContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos) = 0;
};

/**
 * IWEntity 与 IWXYGradient 的碰撞检测
 * @author Zhenyu Yao
 */
class IWContactGradient
{
public:
	
	IWContactGradient(IWWorld * world);
	virtual ~IWContactGradient();
	
	/**
	 * 根据移动数据, 检测 IWEntity 的位置
	 * @param moveInfo IWEntityMoveInfo 对象
	 */
	virtual void detectEntityPosition(IWEntityMoveInfo & moveInfo);
	
	/// IWEntity 与地形的检测, 如果修改了 moveInfo, 则返回 true, 否则返回 false
	virtual bool detectEntityWithGround(IWEntityMoveInfo & moveInfo);
	
private:
	
	IWWorld * m_world;
};

#endif /* defined(__DuckWorld__IWContactGradient__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


