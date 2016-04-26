//
//  Object.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#include "Object.hpp"

#include "Value.hpp"
#include "Context.hpp"
#include "Property.hpp"
#include "CFunction.hpp"

jsc::Object::Object(Context &context) : context(context) {
    object = JSObjectMake(context, nullptr, nullptr);
    JSValueProtect(context, object);
}

jsc::Object::Object(Context &context, JSObjectRef object) : context(context), object(object) {
    JSValueProtect(context, object);
}

jsc::Object::Object(Context &context, std::function<Callback> callback) : context(context) {
    object = JSObjectMake(context, context.callbackClass, new CFunction{context, callback});
    JSValueProtect(context, object);
}

jsc::Object::~Object() {
    if (object != nullptr) {
        JSValueUnprotect(context, object);
    }
}

jsc::StringProperty jsc::Object::operator [] (const String &property) {
    JSValueRef propertyValue = JSObjectGetProperty(context, object, property, nullptr);

    if (propertyValue != nullptr) {
        return StringProperty(*this, property, propertyValue);
    }

    // Failed to retrieve the property, return undefined
    return StringProperty(*this, property);
}

const jsc::Value jsc::Object::operator [] (const String &property) const {
    return get(property);
}

const jsc::Value jsc::Object::get(const String &property) const {
    JSValueRef propertyValue = JSObjectGetProperty(context, object, property, nullptr);

    if (propertyValue != nullptr) {
        return Value(context, propertyValue);
    }

    // Failed to retrieve the property, return undefined
    return Value(context);
}

void jsc::Object::set(const String &property, const Value &value, PropertyAttributes attributes) {
    JSObjectSetProperty(context, object, property, value, static_cast<JSPropertyAttributes>(attributes), nullptr);
}

void jsc::Object::set(const String &property, const Object &value, PropertyAttributes attributes) {
    JSObjectSetProperty(context, object, property, value, static_cast<JSPropertyAttributes>(attributes), nullptr);
}

const jsc::Value jsc::Object::operator [] (unsigned int index) const {
    return get(index);
}

const jsc::Value jsc::Object::get(unsigned int index) const {
    JSValueRef indexValue = JSObjectGetPropertyAtIndex(context, object, index, nullptr);

    if (indexValue != nullptr) {
        return Value(context, indexValue);
    }

    // Failed to retrieve the property, return undefined
    return jsc::Value(context);
}

void jsc::Object::set(unsigned int index, const Value &value) {
    JSObjectSetPropertyAtIndex(context, object, index, value, nullptr);
}

void jsc::Object::set(unsigned int index, const Object &value) {
    JSObjectSetPropertyAtIndex(context, object, index, value, nullptr);
}

jsc::Value jsc::Object::operator () (unsigned int argCount, Value arguments[]) {
    JSValueRef values[argCount];

    for (unsigned int i = 0; i < argCount; ++i) {
        values[i] = arguments[i];
    }

    JSValueRef result = JSObjectCallAsFunction(context, object, nullptr, argCount, values, nullptr);
    return Value(context, result);
}

jsc::String jsc::Object::toString() const {
    JSStringRef jsString = JSValueToStringCopy(context, object, nullptr);
    return String(jsString);
}

jsc::String jsc::Object::toJSON(bool prettyPrint) const {
    JSStringRef jsString = JSValueCreateJSONString(context, object, prettyPrint ? 4 : 0, nullptr);
    return String(jsString);
}
