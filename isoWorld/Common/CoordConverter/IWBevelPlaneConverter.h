//
//  IWBevelPlaneConverter.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-29.
//
//

#ifndef __DuckWorld__IWBevelPlaneConverter__
#define __DuckWorld__IWBevelPlaneConverter__

#include "IWCoordConverter.h"

/**
 * 倾斜地面的转换器, 参考游戏: 龙王, 城堡破坏者
 * @author Zhenyu Yao
 */
class IWBevelPlaneConverter : public IWCoordConverter
{
public: /* override */
	
	virtual IWPoint screenPointFromWorldPoint(const IWPoint & point, IWWorld * world);
	virtual IWPoint worldPointFromScreenPoint(const IWPoint & point, IWWorld * world);
};

#endif /* defined(__DuckWorld__IWBevelPlaneConverter__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


