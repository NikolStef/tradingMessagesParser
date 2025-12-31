#include <string_view> // zero-copy parsing

// Explicit error modeling : Parser state for possible outcomes
// good because we want to know why we failed w/out having any variables created/allocated for ret error msgs
enum class ParserOutcomes {
    done,
    incomplete_input,
    bad_input
};

// Function prototype that can be called from anywhere w/ header
// its declaration (definition can be in any source file)
// Adding it here we only need to include this header for unit testing
// note : this requires manuyally linking all files w/ implemnentation when compiling manually
//        eg. $ g++ -c file1.cpp, $ g++ - c file2.cpp, $ g++ file1.o file2.o - o my_program
ParserOutcomes parseMsg(std::string_view msg);
