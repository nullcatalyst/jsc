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
    JSValueUnprotect(context, object);
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

    return Value(context, JSObjectCallAsFunction(context, object, nullptr, argCount, values, nullptr));
}
