//
//  IWXYGradient.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#include "IWXYGradient.h"
#include "isoWorld/Common/IWMacro.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWXYGradient::IWXYGradient() :
m_world(NULL),
m_coordinate(NULL)
{
}

IWXYGradient::~IWXYGradient()
{
	vector<IWXYPath *>::iterator beg = m_paths.begin();
	vector<IWXYPath *>::iterator end = m_paths.end();
	for (; beg != end; ++beg)
		IW_SAFE_DELETE(*beg);
}

void IWXYGradient::addPath(IWXYPath * path)
{
	IWXYPath * newPath = path->clone();
	m_paths.push_back(newPath);
}

IWXYPath * IWXYGradient::addPath(const IWPoint & front, const IWPoint & back, IWFloat32 distance, IWFloat32 radian)
{
	IWXYPath * path = new IWXYPath(front, back);
	path->setDistance(distance);
	path->setRadian(radian);
	m_paths.push_back(path);
	return path;
}

IWXYPath * IWXYGradient::addPath(IWFloat32 x, IWFloat32 y, IWFloat32 frontZ, IWFloat32 backZ, IWFloat32 distance, IWFloat32 radian)
{
	return addPath(IWPoint(x, y, frontZ), IWPoint(x, y, backZ), distance, radian);
}

vector<IWXYPath *> IWXYGradient::pathsWithX(IWFloat32 x)
{
	vector<IWXYPath *> backup;
	vector<IWXYPath *>::iterator beg = m_paths.begin();
	vector<IWXYPath *>::iterator end = m_paths.end();
	for (; beg != end; ++beg)
	{
		IWXYPath * path = *beg;
		const IWPoint & maxPoint = path->maxXStartPoint();
		if (maxPoint.x < x && x < maxPoint.x + path->getDistance())
			backup.push_back(path);
	}
	
	return backup;
}

vector<IWXYPath *> IWXYGradient::pathsWithXZ(IWFloat32 x, IWFloat32 z)
{
	vector<IWXYPath *> paths = pathsWithX(x);
	vector<IWXYPath *> backup;
	vector<IWXYPath *>::iterator beg = paths.begin();
	vector<IWXYPath *>::iterator end = paths.end();
	for (; beg != end; ++beg)
	{
		IWXYPath * path = *beg;
		const IWPoint & front = path->getFront();
		const IWPoint & back = path->getBack();
		if (front.z < z && z < back.z)
			backup.push_back(path);
	}
	
	return backup;
}

IWXYPath * IWXYGradient::pathWithPoint_MinY(const IWPoint & point, bool up)
{
	vector<IWXYPath *> paths = pathsWithXZ(point.x, point.z);
	IWXYPath * minPath = NULL;
	vector<IWXYPath *>::iterator beg = paths.begin();
	vector<IWXYPath *>::iterator end = paths.end();
	for (; beg != end; ++beg)
	{
		IWXYPath * path = *beg;
		if (path->checkPointInPath(point))
		{
			if (up)
			{
				if (path->YWithPoint(point) >= point.y)
				{
					if (minPath == NULL)
					{
						minPath = path;
					}
					else
					{
						if (minPath->YWithPoint(point) >= path->YWithPoint(point))
							minPath = path;
					}
				}
			}
			else
			{
				if (path->YWithPoint(point) <= point.y)
				{
					if (minPath == NULL)
					{
						minPath = path;
					}
					else
					{
						if (minPath->YWithPoint(point) <= path->YWithPoint(point))
							minPath = path;
					}
				}
			}
		}
	}
	
	return minPath;
}

IWFloat32 IWXYGradient::minYWithPoint(const IWPoint & point, bool up)
{
	IWXYPath * path = pathWithPoint_MinY(point, up);
	if (path == NULL)
		return 0.0f;
	else
		return path->YWithPoint(point);
}









































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


