//
//  IWMacro.h
//  DuckWorld
//
//  Created by Zhenyu Yao on 14-1-27.
//
//

#ifndef __DuckWorld__IWMacro__
#define __DuckWorld__IWMacro__

#include <assert.h>
#include <math.h>

/// 安全 Delete 对象
#define IW_SAFE_DELETE(x)		if (x) { delete x; x = NULL; }

#ifdef IW_DEBUG
#define IWAssert(x) assert(x)
#else
#define IWAssert(x)
#endif // IW_DEBUG

#endif /* defined(__DuckWorld__IWMacro__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


