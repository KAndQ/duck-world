//
//  IWXZTerrain.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWXZTerrain__
#define __DuckWorld__IWXZTerrain__

#include "IWXZCell.h"
#include <vector>

class IWXYZCoordinate;
class IWWorld;

/**
 * 地形的定义对象
 * @author Zhenyu Yao
 */
class IWXZTerrainDef
{
public:
	
	IWXZTerrainDef(IWUInt32 wc = 0, IWUInt32 hc = 0, IWFloat32 gs = 0.0f)
	{
		widthCount = wc;
		heightCount = hc;
		gridSize = gs;
	}
	
	IWUInt32 widthCount;
	IWUInt32 heightCount;
	IWFloat32 gridSize;
};

/**
 * XZ 构建的地形
 * x 的坐标区间是 [0, getWidth()), z 的坐标区间是 [0, getHeight())
 * @author Zhenyu Yao
 */
class IWXZTerrain
{
public:
	
	IWXZTerrain(IWUInt32 widthCount, IWUInt32 heightCount, IWFloat32 gridSize);
	~IWXZTerrain();
	
	/**
	 * 根据行列参数得到对应的 IWXZCell 对象
	 * @param col 列, 从 0 开始计数
	 * @param row 行, 从 1 开始计数
	 * @return IWXZCell 对象
	 */
	IWXZCell * cellAt(IWUInt32 col, IWUInt32 row);
	
	/**
	 * 根据实际的 x, z 得到对应的 IWXZCell 对象
	 * @param x 实际 x 坐标
	 * @param y 实际 y 坐标
	 * @return IWXZCell 对象
	 */
	IWXZCell * cellAtXZ(IWFloat32 x, IWFloat32 z);
	
	/// 得到当前 IWXZCell 的列表副本
	std::vector<IWXZCell *> cells();
	
	/// 宽度的格子数量
	IWUInt32 getWidthCount() const { return m_widthCount; }
	
	/// 高度的格子数量
	IWUInt32 getHeightCount() const { return m_heightCount; }
	
	/// 每个格子的大小
	IWFloat32 getGridSize() const { return m_gridSize; }
	
	/// widthCount * gridSize 的大小
	IWFloat32 getWidth() const { return m_widthCount * m_gridSize; }
	
	/// heightCount * gridSize 的大小
	IWFloat32 getHeight() const { return m_heightCount * m_gridSize; }
	
	/// 根据索引得到当前的 row
	IWUInt32 rowWithIndex(IWUInt32 index);
	
	/// 根据索引得到当前的 col
	IWUInt32 colWithIndex(IWUInt32 index);
	
	/// 根据实际的 z 坐标找到对应的 row
	IWUInt32 rowWithZ(IWFloat32 z);
	
	/// 根据实际的 x 坐标找到对应的 col
	IWUInt32 colWithX(IWFloat32 x);
	
	/// IWWorld 对象
	IWWorld * getWorld() const { return m_world; }
	
	/// IWXYZCoordinate 对象
	IWXYZCoordinate * getCoordinate() const { return m_coordinate; }
	
private:
	
	/// 初始化
	void init();
	
	/// 根据索引得到当前的 row, 不验证
	IWUInt32 rowWithIndex_NoCheck(IWUInt32 idx)
	{
		return idx / m_widthCount;
	}
	
	/// 根据索引得到当前的 col, 不验证
	IWUInt32 colWithIndex_NoCheck(IWUInt32 idx)
	{
		return idx % m_widthCount;
	}
	
private:
	
	IWUInt32 m_widthCount;
	IWUInt32 m_heightCount;
	IWFloat32 m_gridSize;
	std::vector<IWXZCell *> m_cells;
	
	IWWorld * m_world;
	IWXYZCoordinate * m_coordinate;
	
	friend class IWWorld;
	friend class IWXYZCoordinate;
};

#endif /* defined(__DuckWorld__IWXZTerrain__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


