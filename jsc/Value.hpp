//
//  Value.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#ifndef jsc_value_hpp
#define jsc_value_hpp

#include <JavaScriptCore/JavaScriptCore.h>

namespace jsc {
    class Context;
    class String;
    class Object;

    class Value {
        Context &context;
        JSValueRef value;

        friend class String;
        friend class Object;
        friend class Context;

        operator JSValueRef () const {
            return value;
        }

        Value &operator = (JSValueRef value);

    public:
        Value(Context &context);
        Value(Context &context, bool boolean);
        Value(Context &context, double number);
        Value(Context &context, const String &string);
        Value(Context &context, const Object &object);

        Value(Context &context, JSValueRef value);

        ~Value();

        Value &operator = (const Value &other);

        bool isUndefined() const;
        bool isNull() const;
        bool isBoolean() const;
        bool isNumber() const;
        bool isString() const;
        bool isObject() const;
        bool isArray() const;

        bool toBoolean() const;
        double toNumber() const;
        String toString() const;
        Object toObject() const;
    };
}

#endif /* jsc_value_hpp */
