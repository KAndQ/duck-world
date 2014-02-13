//
//  IWXYGradient.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWXYGradient__
#define __DuckWorld__IWXYGradient__

#include "IWXYPath.h"
#include <vector>

class IWXYZCoordinate;
class IWWorld;

/**
 * XY 构成的斜度地形
 * @author Zhenyu Yao
 */
class IWXYGradient
{
public:
	
	IWXYGradient();
	~IWXYGradient();
	
	/**
	 * 添加 IWXYPath 对象, 会在内部对 IWXYPath 对象进行复制, 可以在使用该函数后 delete path 对象.
	 * @param path IWXYPath 对象
	 */
	void addPath(IWXYPath * path);
	
	/**
	 * 添加 IWXYPath 对象
	 * @param front 坡的起始点 - 前端点
	 * @param back 坡的起始点 - 后端点
	 * @param distance 坡的长度
	 * @param radian 坡的斜度
	 * @return IWXYPath 对象
	 */
	IWXYPath * addPath(const IWPoint & front, const IWPoint & back, IWFloat32 distance, IWFloat32 radian);
	
	/**
	 * 添加 IWXYPath 对象
	 * @param x 前后端点的 x 坐标
	 * @param y 前后端点的 y 坐标
	 * @param frontZ 前端点的 z 坐标
	 * @param backZ 后端点的 z 坐标
	 * @param distance 坡的长度
	 * @param radian 坡的斜度
	 * @return IWXYPath 对象
	 */
	IWXYPath * addPath(IWFloat32 x, IWFloat32 y, IWFloat32 frontZ, IWFloat32 backZ, IWFloat32 distance, IWFloat32 radian);
	
	/**
	 * 查询 x 对应的 IWXYPath 对象列表
	 * @param x x坐标
	 * @return IWXYPath 对象列表
	 */
	std::vector<IWXYPath *> pathsWithX(IWFloat32 x);
	
	/**
	 * 查询 x, z 对应的 IWXYPath 对象列表
	 * @param x x坐标
	 * @param z z坐标
	 * @return IWXYPath 对象列表
	 */
	std::vector<IWXYPath *> pathsWithXZ(IWFloat32 x, IWFloat32 z);
	
	/**
	 * 以 point 查询, 与 point Y 轴距离最近的 IWXYPath 对象
	 * @param point 参考点
	 * @param up 如果为 true, 表示 Y 轴方向向上查询; 否则表示 Y 轴方向向下查询
	 * @return IWXYPath 对象, 如果查询不到返回 NULL
	 */
	IWXYPath * pathWithPoint_MinY(const IWPoint & point, bool up);
	
	/**
	 * 以 point 查询, 与 point Y 轴距离最近的 IWXYPath 对象, 并得到 point 投影到 IWXYPath 对象上的 Y 轴值
	 * @param point 参考点
	 * @param up 如果为 true, 表示 Y 轴方向向上查询; 否则表示 Y 轴方向向下查询
	 * @return Y 轴值
	 */
	IWFloat32 minYWithPoint(const IWPoint & point, bool up);
	
	/// IWWorld 对象
	IWWorld * getWorld() const { return m_world; }
	
	/// IWXYZCoordinate 对象
	IWXYZCoordinate * getCoordinate() const { return m_coordinate; }
	
private:
	
	std::vector<IWXYPath *> m_paths;
	
	IWWorld * m_world;
	IWXYZCoordinate * m_coordinate;
	
	friend class IWWorld;
	friend class IWXYZCoordinate;
};


#endif /* defined(__DuckWorld__IWXYGradient__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


