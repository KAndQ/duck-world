//
//  IWXYZCoordinate.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-28.
//
//

#ifndef __DuckWorld__IWXYZCoordinate__
#define __DuckWorld__IWXYZCoordinate__

#include "IWXYGradient.h"
#include "IWXZTerrain.h"

class IWWorld;

/**
 * XYZ 坐标系, 负责对传入的 terrain 和 gradient 对象进行资源管理.
 * @author Zhenyu Yao
 */
class IWXYZCoordinate
{
public:
	
	IWXYZCoordinate(IWXZTerrain * terrain, IWXYGradient * gradient);
	~IWXYZCoordinate();
	
	/// IWXZTerrain 对象
	IWXZTerrain * getTerrain() const { return m_terrain; }
	
	/// IWXYGradient 对象
	IWXYGradient * getGradient() const { return m_gradient; }
	
	/// IWWorld 对象
	IWWorld * getWorld() const { return m_world; }
	
	/**
	 * 查询 point 垂直投影到地面的对应点
	 * @param point 空间上的点
	 * @return 投影在地面上的点
	 */
	IWPoint groundPointWithPoint(const IWPoint & point);
	
	/**
	 * 查询 point 距离最近地面的垂直投影点
	 * @param point 空间上的点
	 * @return 距离 point 最近的投影点, 可能是上投影, 也可能是下投影的点
	 */
	IWPoint minPointWithPoint(const IWPoint & point);
	
private:
	
	IWXZTerrain * m_terrain;
	IWXYGradient * m_gradient;
	IWWorld * m_world;
	
	friend class IWWorld;
};

#endif /* defined(__DuckWorld__IWXYZCoordinate__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


