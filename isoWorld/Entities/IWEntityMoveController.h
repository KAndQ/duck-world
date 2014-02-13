//
//  IWEntityMoveController.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-2-8.
//
//

#ifndef __DuckWorld__IWEntityMoveController__
#define __DuckWorld__IWEntityMoveController__

#include "IWMacro.h"
#include "IWEntity.h"
#include "IWEntityMoveInfo.h"
#include "isoWorld/Contact/IWContactTerrain.h"
#include "isoWorld/Contact/IWContactGradient.h"
#include <map>

class IWWorld;

/**
 * Entity 的移动控制器
 * @author Zhenyu Yao
 */
class IWEntityMoveController
{
public:
	
	IWEntityMoveController(IWWorld * world);
	virtual ~IWEntityMoveController();
	
	/// 逻辑更新
	virtual void update(float dt);
	
	/**
	 * 改变 Entity 的位置
	 * @param entity 改变位置的 IWEntity 对象
	 * @param lastPos 老位置
	 * @param newPos 新位置
	 */
	virtual void changeEntityPosition(const IWEntityMoveInfo & moveInfo);
	
	/// getter/setter IWContactTerrain
	IWContactTerrain * getContactTerrain() const { return m_contactTerrain; }
	
	/// getter/setter IWContactGradient
	IWContactGradient * getContactGradient() const { return m_contactGradient; }
	
private:
	
	IWContactTerrain * m_contactTerrain;
	IWContactGradient * m_contactGradient;
	IWWorld * m_world;
	std::map<IWEntity *, IWEntityMoveInfo> m_moveInfos;
};

#endif /* defined(__DuckWorld__IWEntityMoveController__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


