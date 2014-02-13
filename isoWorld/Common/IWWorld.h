//
//  IWWorld.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWWorld__
#define __DuckWorld__IWWorld__

#include <vector>

#include "IWTypes.h"
#include "isoWorld/Terrain/IWXYZCoordinate.h"
#include "isoWorld/Entities/IWEntity.h"
#include "isoWorld/Entities/IWEntityDelegate.h"
#include "isoWorld/Entities/IWEntityMoveController.h"

/**
 * IWWorld, 是一个 3D 的坐标系, X 向右为正方向, Y 向上为正方向, Z 向屏幕里为正方向.
 * IWWorld 的初始化步骤:
 * 1. 首先实例化 IWWorld 对象;
 * 2. 创建 IWXZTerrain 和 IWXYGradient 对象;
 * 3. 使用 2 创建的 IWXZTerrain 实例和 IWXYGradient 实例来创建 IWXYZCoordinate 对象;
 * 4. 将 3 创建的 IWXYZCoordinate 实例配置在 1 实例的 IWWorld 对象中;
 *
 * 用户不要自己 new IWEntity 对象, 必须使用 IWWorld::createEntity 创建 IWEntity 对象, 销毁也必须使用 IWWorld::destroyEntity 方法释放资源.
 * @author Zhenyu Yao
 */
class IWWorld : public IWEntityDelegate
{
	
public:
	
	IWWorld();
	~IWWorld();
	
	/// 逻辑更新
	void update(IWFloat32 dt);
	
	/// 重力参数
	IWFloat32 getGravity() const { return m_gravity; }
	void setGravity(float gravity) { m_gravity = gravity; }
	
	// X 轴的旋转值, 转向脸方向使用负角表示, 远离脸方向使用正角表示
	IWFloat32 getXRadian() const { return m_xradian; }
	void setXRadian(IWFloat32 xradian) { m_xradian = xradian; }
	
	// Y 轴的旋转值, 向左转动使用负角表示, 向右转动使用正角表示
	IWFloat32 getYRadian() const { return m_yradian; }
	void setYRadian(IWFloat32 yradian) { m_yradian = yradian; }
	
	/// IWXYZCoordinate 对象, 当释放 IWWorld 对象的时候会 delete IWXYZCoordinate 对象的资源
	IWXYZCoordinate * getCoordinate() const { return m_coordinate; }
	void setCoordinate(IWXYZCoordinate * coordinate)
	{
		m_coordinate = coordinate;
		if (m_coordinate != NULL)
			m_coordinate->m_world = this;
		
		if (m_coordinate->m_terrain != NULL)
			m_coordinate->m_terrain->m_world = this;
		
		if (m_coordinate->m_gradient != NULL)
			m_coordinate->m_gradient->m_world = this;
	}
	
	/// 创建/销毁 IWXYZCoordinate 对象
	IWXYZCoordinate * createCoordinate(IWXZTerrain * terrain, IWXYGradient * gradient);
	void destroyCoordinate(IWXYZCoordinate * coordinate);
	
	/// 创建/销毁 IWXZTerrain 对象
	IWXZTerrain * createTerrain(const IWXZTerrainDef & def);
	void destroyTerrain(IWXZTerrain * terrain);
	
	/// 创建/销毁 IWXYGragient 对象
	IWXYGradient * createGradient();
	void destroyGradient(IWXYGradient * gradient);
	
	/// 创建/销毁 IWEntity 对象
	IWEntity * createEntity();
	void destroyEntity(IWEntity * entity);
	
	/// 获得 IWEntity 集合的一个副本
	std::vector<IWEntity *> getEntities();
	
	/// 获得 IWEntityMoveController 实例
	IWEntityMoveController * getMoveController() const { return m_moveController; }
	
	/// 设置 XZ 坐标轴的回调函数
	void setXZContactCallBack(IWXZContactTerrainCallBack * callBack) { m_xzContactCallBack = callBack; }
	
	/// 设置 XY 坐标轴的回调函数
	void setXYContactCallBack(IWXYContactGradientCallBack * callBack) { m_xyContactCallBack = callBack; }
	
public: /* IWEntityDelegate */
	
	virtual void positionChanged(IWEntity * entity, const IWPoint & lastPos, const IWPoint & newPos);
	
private:
	
	IWFloat32 m_gravity;
	IWFloat32 m_xradian;		// 沿 x 轴旋转
	IWFloat32 m_yradian;		// 沿 y 轴旋转
	IWXYZCoordinate * m_coordinate;
	std::vector<IWEntity *> m_entities;
	IWEntityMoveController * m_moveController;
	IWXZContactTerrainCallBack * m_xzContactCallBack;
	IWXYContactGradientCallBack * m_xyContactCallBack;
	
	friend class IWEntityMoveController;
	friend class IWContactGradient;
	friend class IWContactTerrain;
};

#endif /* defined(__DuckWorld__IWWorld__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


