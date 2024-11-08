/*
 * Profiler.ino
 *
 * Example Arduino sketch for the Arduino Profiler library
 *
 * version 1.0 - August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * version 1.6 - August 2024
 *    added optional custom output text support
 * version 1.7 - November 2024
 *    added human readable time format
 *
 */

#include <Profiler.h>

#define   DEBUG_LED   13

// forward declarations (function prototypes):
void foo();
void bar();
void baz();
void disabled_example();
void ms_example();
void day_example();

void setup() {
    Serial.begin(115200);
    while (!Serial);

    foo();

    bar();

    baz();

    disabled_example();
    ms_example();
    day_example();
}

void loop() {

}


// Example function that will be profiled including debug pin output:
// (the debug output pin is HIGH for one second in this example usage)
void foo() {
    profiler_t profiler(DEBUG_LED);

    delay(1000);
}

// Example function where only a smaller part of the code
// will be profiled using a temporary scope. Also makes use 
// of the new custom output text support:
//
void bar() {
    // this code will NOT be profiled.
    // yes the code is pointless heh
    for (int i=0; i < 10; i++) {
        delay(100);
    }

    // create a temporary scope just to contain the instantiation of a profiler_t
    // object in order to time a smaller section of code inside a larger section
    // and customize the output text:
    {
        profiler_t profiler("Partial Scoped Profile");
        // ... some other code you want profiled

        delay(500);
    }

    // more pointless code that will NOT be profiled
    for (int i=0; i < 10; i++) {
        delay(100);
    }
}

// Example function that will be profiled and use customized text output
// to automatically include the enclosing function name, so you can reuse 
// this same code in many functions and it will automatically output each
// function's correct name:
//
void baz() {
    profiler_t profiler(
        (String("Time spent in ") + 
        String(__FUNCTION__) + 
        String("()")).c_str());

    delay(2000);
}

// Demonstration of the method "disable()"
//
void disabled_example() {
    profiler_t profiler(DEBUG_LED, "This will not be printed");
    profiler.disable();

    delay(1000);
}

// Demonstration of the method "inMilliseconds()"
//
void ms_example() {
    profiler_t profiler(DEBUG_LED, "This will print in milliseconds");
    profiler.inMilliseconds();

    delay(1500);
}

// Demonstration of profiling a function that takes a day
// This example will take some time ...
//
void day_example() {
    profiler_t profiler(DEBUG_LED, "Finally");
    
    delay(86400101);
}