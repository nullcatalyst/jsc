//
//  file.hpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#ifndef _private_jsc_file_hpp
#define _private_jsc_file_hpp

#include <functional>

void readFile(const char *filename, std::function<void (const char *contents)> callback);

#endif /* _private_jsc_file_hpp */
