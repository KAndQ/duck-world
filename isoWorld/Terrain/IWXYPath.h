//
//  IWXYPath.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef DuckWorld_IWXYPath_h
#define DuckWorld_IWXYPath_h

#include "isoWorld/Common/IWMacro.h"
#include "isoWorld/Common/IWPoint.h"

/**
 * XY 轴上的单位路径
 * @author Zhenyu Yao
 */
class IWXYPath
{
public:
	
	/**
	 * 构造函数
	 * @param front 前端点, front.z 必须小于 back.z
	 * @param back 后端点, front.z 必须小于 back.z
	 */
	IWXYPath(const IWPoint & front, const IWPoint & back) :
	m_front(IWPoint()), m_back(IWPoint()), m_distance(0.0f), m_radian(0.0f), m_userData(0), m_next(NULL), m_prev(NULL)
	{
		IWAssert(front.z <= back.z);
		IWAssert(front.x == back.x);
		IWAssert(front.y == back.y);
		m_front = front;
		m_back = back;
	}
	
	/// 析构函数
	~IWXYPath()
	{
	}
	
	// 坡的起始点 - 前端点
	const IWPoint & getFront() const { return m_front; }
	
	// 坡的起始点 - 后端点
	const IWPoint & getBack() const { return m_back; }
	
	// 坡的长度
	IWFloat32 getDistance() const { return m_distance; }
	void setDistance(IWFloat32 distance) { m_distance = distance; }
	
	// 坡的斜度
	IWFloat32 getRadian() const { return m_radian; }
	void setRadian(IWFloat32 radian) { m_radian = radian; }
	
	// 关联的数据
	void * getUserData() const { return m_userData; }
	void setUserData(void * userData) { m_userData = userData; }
	
	// 连接的下一个路径
	IWXYPath * getNext() const { return m_next; }
	void setNext(IWXYPath * next) { m_next = next; }
	
	// 连接的上一个路径
	IWXYPath * getPrev() const { return m_prev; }
	void setPrev(IWXYPath * prev) { m_prev = prev; }
	
	/// front 和 back 比较, 返回 X 坐标最小的点
	IWPoint minXStartPoint() { return m_front.x < m_back.x ? m_front : m_back; }
	
	/// front 和 back 比较, 返回 X 坐标最大的点
	IWPoint maxXStartPoint() { return m_front.x > m_back.x ? m_front : m_back; }
	
	/// 判断 point 是否在 Path 表示的范围内
	IWBool checkPointInPath(const IWPoint & point)
	{
		return (m_front.x <= point.x && point.x <= m_front.x + m_distance)
			&& (m_front.z <= point.z && point.z <= m_back.z);
	}
	
	/// 判断 point 在 Path 中对应的 Y 值
	IWFloat32 YWithPoint(const IWPoint & point)
	{
		IWAssert(checkPointInPath(point));
		IWFloat32 x = point.x - m_front.x;
		IWFloat32 y = 0.0f;
		if (m_radian != 0.0f && x != 0.0f)
			y = tanf(m_radian) * x;
		
		return m_front.y + y;
	}
	
	/// 对当前对象创建一个副本, 需要自己手动 delete 生成的对象
	IWXYPath * clone()
	{
		IWXYPath * path = new IWXYPath(m_front, m_back);
		path->m_distance = m_distance;
		path->m_radian = m_radian;
		path->m_userData = m_userData;
		return path;
	}
	
	/// 判断是否是相同的 path
	bool isEqual(const IWXYPath * path) const
	{
		IWAssert(path != NULL);
		
		return m_front == path->m_front
		&& m_back == path->m_back
		&& m_distance == path->m_distance
		&& m_radian == path->m_radian
		&& m_userData == path->m_userData;
	}
	
	/// 判断与路径 path 是否连接
	bool isConnect(const IWXYPath * path) const
	{
		if (path == NULL)
			return false;
		
		return m_next == path || m_prev == path;
	}
	
private:
	
	IWPoint m_front;
	IWPoint m_back;
	IWFloat32 m_distance;
	IWFloat32 m_radian;
	void * m_userData;
	IWXYPath * m_next;
	IWXYPath * m_prev;
};

#endif














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


