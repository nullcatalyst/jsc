//
//  Value.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#include "Value.hpp"

#include "Context.hpp"

jsc::Value::Value(Context &context, JSValueRef value) : context(context), value(value) {
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context) : context(context) {
    value = JSValueMakeUndefined(context);
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context, bool boolean) : context(context) {
    value = JSValueMakeBoolean(context, boolean);
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context, int number) : context(context) {
    value = JSValueMakeNumber(context, number);
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context, double number) : context(context) {
    value = JSValueMakeNumber(context, number);
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context, const String &string) : context(context) {
    value = JSValueMakeString(context, string);
    JSValueProtect(context, value);
}

jsc::Value::Value(Context &context, const Object &object) : context(context) {
    value = object;
    JSValueProtect(context, value);
}

jsc::Value::Value(const Value &other) : context(other.context) {
    value = other.value;
    JSValueProtect(context, value);
}

jsc::Value::~Value() {
    if (value != nullptr) {
        JSValueUnprotect(context, value);
    }
}

jsc::Value &jsc::Value::operator = (JSValueRef newValue) {
    if (value != nullptr) {
        JSValueUnprotect(context, value);
    }
    value = newValue;
    JSValueProtect(context, value);
    return *this;
}

jsc::Value &jsc::Value::operator = (const Value &other) {
    if (value != nullptr) {
        JSValueUnprotect(context, value);
    }
    value = other.value;
    JSValueProtect(context, value);
    return *this;
}

bool jsc::Value::isUndefined() const {return JSValueIsUndefined(context, value);}
bool jsc::Value::isNull()      const {return JSValueIsNull(context, value);}
bool jsc::Value::isBoolean()   const {return JSValueIsBoolean(context, value);}
bool jsc::Value::isNumber()    const {return JSValueIsNumber(context, value);}
bool jsc::Value::isString()    const {return JSValueIsString(context, value);}
bool jsc::Value::isObject()    const {return JSValueIsObject(context, value);}
bool jsc::Value::isArray()     const {return JSValueIsArray(context, value);}
bool jsc::Value::isFunction()  const {return JSValueIsObject(context, value) && JSObjectIsFunction(context, const_cast<JSObjectRef>(value));}

bool jsc::Value::toBoolean()   const {return JSValueToBoolean(context, value);}
double jsc::Value::toNumber()  const {return JSValueToNumber(context, value, nullptr);}

jsc::String jsc::Value::toString() const {
    JSStringRef jsString = JSValueToStringCopy(context, value, nullptr);
    return String(jsString);
}

jsc::Object jsc::Value::toObject() const {
    return Object(context, const_cast<JSObjectRef>(value));
}
