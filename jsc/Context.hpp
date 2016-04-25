//
//  Context.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#ifndef jsc_context_hpp
#define jsc_context_hpp

#include <functional>

#include "String.hpp"
#include "Object.hpp"
#include "Value.hpp"

namespace jsc {
    class Context {
        JSContextRef context;
        Object *globalThis;
        JSClassRef callbackClass;
        std::function<void (const Value exception)> exceptionHandler;

        friend class String;
        friend class Object;
        friend class Value;

        operator JSContextRef () const {
            return context;
        }

        static void defaultExceptionHandler(const Value &exception);
        static void finalizeCFunction(JSObjectRef object);
        static JSValueRef callCFunction(JSContextRef jsContext, JSObjectRef jsFunction, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);

    public:
        Context();
        Context(const std::function<void (const Value exception)> &handler);
        ~Context();

        void setExceptionHandler(const std::function<void (const Value exception)> &handler) {
            exceptionHandler = handler;
        }

        Object &getGlobal() {
            return *globalThis;
        }

        const Object &getGlobal() const {
            return *globalThis;
        }

        Value evalFile(const char *filename);
        Value eval(const String &source);
    };
}

#endif /* jsc_context_hpp */
