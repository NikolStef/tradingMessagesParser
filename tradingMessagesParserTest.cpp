// Manual unit testing - need to pass before RNG fuzz testing

#include "tradingMessagesParser.h"
#include <iostream>
#include <string_view>
#include <string>

// macro
#define ASSERT_TRUE(cond) if (!(cond)) return false;

// function taking a testing function as input
void run(bool (*fun)(), std::string name, int& total, int& passed) {
    if (fun()) {
        passed++;
        std::cout << "[PASSED] " << name << std::endl;
    }
    else std::cout << "[FAILED] " << name << std::endl;
    total++;
}

bool test_valid_message()
{
    std::string_view msg = "35=D|55=AAPL|44=195.12|";
    ASSERT_TRUE(parseMsg(msg) == ParserOutcomes::done);
    return true;
}

bool test_missing_delimiter()
{
    std::string_view msg = "35=D|55=AAPL|44=195.12";
    ASSERT_TRUE(parseMsg(msg) != ParserOutcomes::done);
    return true;
}

bool test_missing_equals()
{
    std::string_view msg = "35D|";
    ASSERT_TRUE(parseMsg(msg) == ParserOutcomes::bad_input);
    return true;
}

bool test_empty_messag()
{
    std::string_view msg = "";
    ASSERT_TRUE(parseMsg(msg) == ParserOutcomes::incomplete_input);
    return true;
}

bool testInvalidTag() {
    std::string_view msg = "abc=D|55=AAPL|44=195.12|"; // 'abc' is not a number
    ASSERT_TRUE(parseMsg(msg) == ParserOutcomes::bad_input);
    return true;
}

bool testMissingValue() {
    std::string_view msg = "35=|55=AAPL|44=195.12|"; // 35 has empty value
    ASSERT_TRUE(parseMsg(msg) == ParserOutcomes::bad_input);
    return true;
}


int main()
{
    int passed = 0;
    int total = 0;

    run(test_valid_message, "valid message", total, passed);
    run(test_missing_delimiter, "missing delimiter", total, passed);
    run(test_missing_equals, "missing equals", total, passed);
    run(test_empty_messag, "empty msg", total, passed);
    run(testInvalidTag, "invalid tag", total, passed);
    run(testMissingValue, "missing value", total, passed);

    std::cout << passed << "/" << total << " tests successfully passed\n";
    if (passed == total) return 0;
    else return 1;
}

