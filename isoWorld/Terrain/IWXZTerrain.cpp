//
//  IWXZTerrain.cpp
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#include "IWXZTerrain.h"
#include "isoWorld/Common/IWMacro.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

IWXZTerrain::IWXZTerrain(IWUInt32 widthCount, IWUInt32 heightCount, IWFloat32 gridSize) :
m_world(NULL),
m_coordinate(NULL)
{
	m_widthCount = widthCount;
	m_heightCount = heightCount;
	m_gridSize = gridSize;
	
	init();
}

IWXZTerrain::~IWXZTerrain()
{
	vector<IWXZCell *>::iterator beg = m_cells.begin();
	vector<IWXZCell *>::iterator end = m_cells.end();
	for (; beg != end; ++beg)
		IW_SAFE_DELETE(*beg);
}

IWXZCell * IWXZTerrain::cellAt(IWUInt32 col, IWUInt32 row)
{
	if (col >= m_widthCount || row >= m_heightCount)
		return NULL;
	
	IWUInt32 index = col + row * m_widthCount;
	return m_cells[index];
}

IWXZCell * IWXZTerrain::cellAtXZ(IWFloat32 x, IWFloat32 z)
{
	IWUInt32 col = colWithX(x);
	IWUInt32 row = rowWithZ(z);
	return cellAt(col, row);
}

vector<IWXZCell *> IWXZTerrain::cells()
{
	vector<IWXZCell *>::iterator beg = m_cells.begin();
	vector<IWXZCell *>::iterator end = m_cells.end();
	vector<IWXZCell *> backupCells;
	for (; beg != end; ++beg)
		backupCells.push_back(*beg);
	return backupCells;
}

IWUInt32 IWXZTerrain::rowWithIndex(IWUInt32 index)
{
	IWAssert(index < m_cells.size());
	return rowWithIndex_NoCheck(index);
}

IWUInt32 IWXZTerrain::colWithIndex(IWUInt32 index)
{
	IWAssert(index < m_cells.size());
	return colWithIndex_NoCheck(index);
}

IWUInt32 IWXZTerrain::rowWithZ(IWFloat32 z)
{
	if (z < 0.0f)
		return 0;
	
	IWUInt32 row = z / m_gridSize;
	
	if (row >= m_heightCount)
		return m_heightCount - 1;
	
	return row;
}

IWUInt32 IWXZTerrain::colWithX(IWFloat32 x)
{
	if (x < 0.0f)
		return 0;
	
	IWUInt32 col = x / m_gridSize;
	
	if (col >= m_widthCount)
		return m_widthCount - 1;
	
	return col;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void IWXZTerrain::init()
{
	IWUInt32 size = m_widthCount * m_heightCount;
	for (IWUInt32 i = 0; i < size; ++i)
	{
		IWXZCell * cell = new IWXZCell();
		cell->setRow(rowWithIndex_NoCheck(i));
		cell->setCol(colWithIndex_NoCheck(i));
		m_cells.push_back(cell);
	}
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


