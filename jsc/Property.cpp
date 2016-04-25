//
//  Property.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#include "Property.hpp"

jsc::StringProperty::StringProperty(const Object &object, const String &name) : Value(object.context), object(object), name(name) {

}

jsc::StringProperty::StringProperty(const Object &object, const String &name, const JSValueRef value) : Value(object.context, value), object(object), name(name) {

}

jsc::StringProperty &jsc::StringProperty::operator = (const bool value) {
    object.set(name, Value(object.context, value));
    return *this;
}

jsc::StringProperty &jsc::StringProperty::operator = (const int value) {
    object.set(name, Value(object.context, static_cast<double>(value)));
    return *this;
}

jsc::StringProperty &jsc::StringProperty::operator = (const double value) {
    object.set(name, Value(object.context, value));
    return *this;
}

jsc::StringProperty &jsc::StringProperty::operator = (const Value &value) {
    object.set(name, value);
    return *this;
}


jsc::IndexProperty::IndexProperty(const Object &object, const unsigned int &index) : Value(object.context), object(object), index(index) {

}

jsc::IndexProperty::IndexProperty(const Object &object, const unsigned int &index, const JSValueRef value) : Value(object.context, value), object(object), index(index) {

}

jsc::IndexProperty &jsc::IndexProperty::operator = (const bool value) {
    object.set(index, Value(object.context, value));
    return *this;
}

jsc::IndexProperty &jsc::IndexProperty::operator = (const int value) {
    object.set(index, Value(object.context, static_cast<double>(value)));
    return *this;
}

jsc::IndexProperty &jsc::IndexProperty::operator = (const double value) {
    object.set(index, Value(object.context, value));
    return *this;
}

jsc::IndexProperty &jsc::IndexProperty::operator = (const Value &value) {
    object.set(index, value);
    return *this;
}
