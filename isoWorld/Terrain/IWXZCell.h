//
//  IWXZCell.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWXZCell__
#define __DuckWorld__IWXZCell__

#include "isoWorld/Common/IWTypes.h"

/**
 * 世界坐标中 XZ 坐标系中的地形网格
 * @author Zhenyu Yao
 */
class IWXZCell
{
public:
	
	/// 障碍的类型
	enum ObstacleType
	{
		kObstacleType_None,			// 没有障碍物
		kObstacleType_NoEntry,		// 任何情况都不能通过
	};
	
public:
	
	IWXZCell() : m_obstacleType(kObstacleType_None), m_col(0), m_row(0), m_userData(0)
	{
	}
	
	~IWXZCell()
	{
	}
	
	// 障碍
	ObstacleType getObstacleType() const { return m_obstacleType; }
	void setObstacleType(ObstacleType type) { m_obstacleType = type; }
	
	// 列, 从 0 开始计数
	IWUInt32 getCol() const { return m_col; }
	void setCol(IWUInt32 col) { m_col = col; }
	
	// 行, 从 0 开始计数
	IWUInt32 getRow() const { return m_row; }
	void setRow(IWUInt32 row) { m_row = row; }
	
	// 关联的其他数据
	void * getUserData() { return m_userData; }
	void setUserData(void * userData) { m_userData = userData; }
	
private:
	ObstacleType m_obstacleType;
	IWUInt32 m_col;
	IWUInt32 m_row;
	void * m_userData;
};

#endif /* defined(__DuckWorld__IWXZCell__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


