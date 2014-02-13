//
//  IWEntityDelegate.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#ifndef DuckWorld_IWEntityDelegate_h
#define DuckWorld_IWEntityDelegate_h

class IWEntity;

/**
 * IWEntity 的委托
 * @author Zhenyu Yao
 */
class IWEntityDelegate
{
public:
	
	/// 位置改变
	virtual void positionChanged(IWEntity * entity, const IWPoint & lastPos, const IWPoint & newPos) = 0;
	
};

#endif














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


