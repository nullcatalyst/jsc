//
//  jscTests.mm
//  jscTests
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <jsc/jsc.h>
using namespace jsc;

@interface jscTests : XCTestCase

@end

@implementation jscTests

- (void) setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void) tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void) testResult {
    // Check that the return value is the last statement executed
    Context ctx;
    
    Value result = ctx.eval("5");
    XCTAssertTrue(result.isNumber(), "5 should be a number");
    XCTAssertTrue(result.toNumber() == 5, "js(5) == cpp(5)");

    result = ctx.eval("5; false");
    XCTAssertTrue(result.isBoolean(), "false should be a boolean");
    XCTAssertTrue(result.toBoolean() == false, "js(false) should be equal to cpp(false)");
}

- (void) testException {
    // Test that the exception handler is correctly getting called with the right value
    Context ctx;
    Value thrownValue(ctx);
    bool wasThrown = false;

    ctx.setExceptionHandler([&wasThrown, &thrownValue] (const Value exception) {
        wasThrown = true;
        thrownValue = exception;
    });

    Value result = ctx.eval("throw 'exception';");
    XCTAssertTrue(result.isNull(), "The result should be null");
    XCTAssertTrue(wasThrown, "A js exception should be thrown");
    XCTAssertTrue(thrownValue.isString(), "The thrown js exception should be a string");
    XCTAssertTrue(thrownValue.toString() == String("exception"), "js('exception') should be equal to cpp('exception')");
}

@end
