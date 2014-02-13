//
//  IWContactTerrain.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-8.
//
//

#ifndef __DuckWorld__IWContactTerrain__
#define __DuckWorld__IWContactTerrain__

#include "isoWorld/Entities/IWEntityMoveInfo.h"

class IWWorld;

/**
 * 当在 XZ 轴方向与障碍格子或者边界发生碰撞时候的回调
 * @author Zhenyu Yao
 */
class IWXZContactTerrainCallBack
{
public:
	
	/**
	 * 解除回调
	 * @param entity 触发的 IWEntity 对象
	 * @param newPos1 如果不发生碰撞会到达的位置
	 * @param newPos2 当前的实际位置, 它与当前的 entity->getPos() 得到的值相同
	 * @param lastPos 上次所在的位置
	 */
	virtual void XZContactCallBack(IWEntity * entity, const IWPoint & newPos1, const IWPoint & newPos2, const IWPoint & lastPos) = 0;
};

/**
 * IWEntity 与 IWXZTerrain 的碰撞检测
 * @author Zhenyu Yao
 */
class IWContactTerrain
{
public:
	
	IWContactTerrain(IWWorld * world);
	virtual ~IWContactTerrain();
	
	/**
	 * 根据移动数据, 检测 IWEntity 的位置
	 * @param moveInfo IWEntityMoveInfo 对象
	 */
	virtual void detectEntityPosition(IWEntityMoveInfo & moveInfo);
	
	/// Top 方向移动, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithTop(IWEntityMoveInfo & moveInfo);
	
	/// Left Top, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithLeftTop(IWEntityMoveInfo & moveInfo);
	
	/// Left, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithLeft(IWEntityMoveInfo & moveInfo);
	
	/// Left Bottom, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithLeftBottom(IWEntityMoveInfo & moveInfo);
	
	/// Bottom, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithBottom(IWEntityMoveInfo & moveInfo);
	
	/// Right Bottom, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithRightBottom(IWEntityMoveInfo & moveInfo);
	
	/// Right, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithRight(IWEntityMoveInfo & moveInfo);
	
	/// Right Top, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithRightTop(IWEntityMoveInfo & moveInfo);
	
	/// 边界检测, 如果修改了 newPos 则返回 true
	virtual bool detectEntityWithBorder(IWEntityMoveInfo & moveInfo);
	
private:
	
	IWWorld * m_world;
};

#endif /* defined(__DuckWorld__IWContactTerrain__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


