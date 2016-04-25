//
//  Context.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#include <vector>
#include "_private/file.hpp"

#include "Context.hpp"

#include "Value.hpp"
#include "CFunction.hpp"

void jsc::Context::defaultExceptionHandler(const Value &exception) {
    jsc::String message = exception.toString();

    message.useCString([] (const char *string) {
        fprintf(stderr, "%s\n", string);
    });
}

void jsc::Context::finalizeCFunction(JSObjectRef object) {
    CFunction *cFunction = static_cast<CFunction *>(JSObjectGetPrivate(object));
    delete cFunction;
}

JSValueRef jsc::Context::callCFunction(JSContextRef jsContext, JSObjectRef jsFunction, JSObjectRef jsThisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception) {
    CFunction *cFunction = static_cast<CFunction *>(JSObjectGetPrivate(jsFunction));
    Context &context = cFunction->context;

    std::vector<Value> values;
    values.reserve(argumentCount);
    for (unsigned int i = 0; i < argumentCount; ++i) {
        values.emplace_back(context, arguments[i]);
    }

    Object thisObject(context, jsThisObject);
    Value result = cFunction->callback(context, thisObject, static_cast<unsigned int>(argumentCount), &values[0]);

    return result.value;
}


jsc::Context::Context() : Context(defaultExceptionHandler) {
    
}

jsc::Context::Context(const std::function<void (const Value exception)> &handler) : context(JSGlobalContextCreate(nullptr)), exceptionHandler(handler) {
    JSClassDefinition definition = kJSClassDefinitionEmpty;
    definition.finalize = finalizeCFunction;
    definition.callAsFunction = callCFunction;
    callbackClass = JSClassCreate(&definition);

    globalThis = new Object(*this, JSContextGetGlobalObject(context));
}

jsc::Context::~Context() {
    delete globalThis;

    JSGlobalContextRelease(const_cast<JSGlobalContextRef>(context));
}

jsc::Value jsc::Context::evalFile(const char *filename) {
    Value result(*this);

    readFile(filename, [this, filename, &result] (const char *contents) {
        JSValueRef error = nullptr;

        JSStringRef scriptName = JSStringCreateWithUTF8CString(filename);
        JSStringRef script = JSStringCreateWithUTF8CString(contents);
        result = JSEvaluateScript(context, script, nullptr, scriptName, 0, &error);
        JSStringRelease(script);
        JSStringRelease(scriptName);

        if (error != nullptr) {
            jsc::Value exception(*this, error);
            exceptionHandler(exception);
        }
    });

    JSGarbageCollect(context);
    return result;
}

jsc::Value jsc::Context::eval(const jsc::String &source) {
    JSValueRef error = nullptr;
    Value result(*this, JSEvaluateScript(context, source, nullptr, nullptr, 0, &error));

    if (error != nullptr) {
        jsc::Value exception(*this, error);
        exceptionHandler(exception);
    }

    JSGarbageCollect(context);
    return result;
}
