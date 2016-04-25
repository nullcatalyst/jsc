//
//  String.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#include "String.hpp"

jsc::String::String(const char *cString) {
    value = JSStringCreateWithUTF8CString(cString);
}

jsc::String::String(JSStringRef value) : value(value) {

}

jsc::String::String(const String &other) {
    value = other.value;
    JSStringRetain(value);
}

jsc::String::String(String &&other) {
    value = other.value;
    other.value = nullptr;
}

jsc::String::~String() {
    JSStringRelease(value);
}

bool jsc::String::operator == (const String &other) const {
    return JSStringIsEqual(value, other.value);
}

void jsc::String::useCString(std::function<void (const char *cString)> callback) const {
    size_t length = JSStringGetMaximumUTF8CStringSize(value);
    char *cString = new char[length];
    JSStringGetUTF8CString(value, cString, length);

    callback(cString);

    delete [] cString;
}

const char *jsc::String::copyCString() const {
    size_t length = JSStringGetMaximumUTF8CStringSize(value);
    char *cString = new char[length];
    JSStringGetUTF8CString(value, cString, length);

    return cString;
}
