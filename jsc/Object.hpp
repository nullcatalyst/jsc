//
//  Object.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#ifndef jsc_object_hpp
#define jsc_object_hpp

#include "String.hpp"

namespace jsc {
    class Context;
    class Object;
    class Value;
    class StringProperty;
    class IndexProperty;

    using Callback = Value (Context &context, Object &thisObject, unsigned int argCount, Value arguments[]);

    enum PropertyAttributes : unsigned int {
        None         = kJSPropertyAttributeNone,
        ReadOnly     = kJSPropertyAttributeReadOnly,
        DontEnum     = kJSPropertyAttributeDontEnum,
        DontDelete   = kJSPropertyAttributeDontDelete
    };

    constexpr PropertyAttributes operator | (PropertyAttributes a, PropertyAttributes b) {
        return a | b;
    }

    class Object {
        Context &context;
        JSObjectRef object;

        friend class String;
        friend class Value;
        friend class Context;
        friend class StringProperty;
        friend class IndexProperty;

        operator JSObjectRef () const {
            return object;
        }

    public:
        Object(Context &context);
        Object(Context &context, std::function<Callback> callback);

        Object(Context &context, JSObjectRef object);

        ~Object();

        // String property accessors
        StringProperty operator [] (const String &property);
        const Value operator [] (const String &property) const;

        const Value get(const String &property) const;
        void set(const String &property, const Value &value, PropertyAttributes attributes = None);
        void set(const String &property, const Object &value, PropertyAttributes attributes = None);

        // Indexed array accessors
        IndexProperty operator [] (unsigned int index);
        const Value operator [] (unsigned int index) const;

        const Value get(unsigned int index) const;
        void set(unsigned int index, const Value &value);
        void set(unsigned int index, const Object &value);

        // Call the object as a function
        Value operator () (unsigned int argCount, Value arguments[]);

        // Convert the object into a more human-readable format
        String toString() const;
        String toJSON(bool prettyPrint = false) const;
    };
}

#endif /* jsc_object_hpp */
