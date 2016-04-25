//
//  CFunction.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#ifndef jsc_cfunction_hpp
#define jsc_cfunction_hpp

#include <functional>
#include <JavaScriptCore/JavaScriptCore.h>

#include "Object.hpp"

namespace jsc {
    class Context;

    struct CFunction {
        Context &context;
        std::function<Callback> callback;
    };
}

#endif /* jsc_cfunction_hpp */
