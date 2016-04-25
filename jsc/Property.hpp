//
//  Property.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#ifndef jsc_property_hpp
#define jsc_property_hpp

#include "Object.hpp"
#include "String.hpp"
#include "Value.hpp"

namespace jsc {
    class Object;
    class String;
    class Value;

    // This is a helper class to make it easier to assign to an object
    // It is not recommended to keep references to these objects
    class StringProperty : public Value {
        Object object;
        String name;

        friend class Object;

        StringProperty(const Object &object, const String &name);
        StringProperty(const Object &object, const String &name, const JSValueRef value);

    public:
        ~StringProperty() = default;

        StringProperty &operator = (const bool value);
        StringProperty &operator = (const int value);
        StringProperty &operator = (const double value);
        StringProperty &operator = (const Value &value);
    };


    // This is a helper class to make it easier to assign to an object
    // It is not recommended to keep references to these objects
    class IndexProperty : public Value {
        Object object;
        unsigned int index;

        friend class Object;

        IndexProperty(const Object &object, const unsigned int &index);
        IndexProperty(const Object &object, const unsigned int &index, const JSValueRef value);

    public:
        ~IndexProperty() = default;

        IndexProperty &operator = (const bool value);
        IndexProperty &operator = (const int value);
        IndexProperty &operator = (const double value);
        IndexProperty &operator = (const Value &value);
    };
}

#endif /* jsc_property_hpp */
