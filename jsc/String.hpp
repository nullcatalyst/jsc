//
//  String.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2015 Scott Bennett. All rights reserved.
//

#ifndef jsc_string_hpp
#define jsc_string_hpp

#include <functional>
#include <JavaScriptCore/JavaScriptCore.h>

namespace jsc {
    class String {
        JSStringRef value;

        friend class Object;
        friend class Value;
        friend class Context;

        String(JSStringRef value);

        operator JSStringRef () const {
            return value;
        }

    public:
        String(const char *cString);
        String(const String &other);
        String(String &&other);
        ~String();

        bool operator == (const String &other) const;

        // The value returned from toString() must be deallocated using delete[]
        // Avoid using this whenever possible in favour of useCString()
        const char *copyCString() const;

        void useCString(std::function<void (const char *cString)> callback) const;
    };
}

#endif /* jsc_string_hpp */
