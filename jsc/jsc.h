//
//  jsc.h
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#ifndef FOUNDATION_EXTERN
#define FOUNDATION_EXTERN
#endif

//! Project version number for jsc.
FOUNDATION_EXPORT double jscVersionNumber;

//! Project version string for jsc.
FOUNDATION_EXPORT const unsigned char jscVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <jsc/PublicHeader.h>


#include "Context.hpp"
#include "Value.hpp"
#include "String.hpp"
#include "Object.hpp"
#include "CFunction.hpp"
