// tradingMessagesParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
// zero-copy parser, delimiter based
// Assumptions : input is a complete msg buffer, format "tag=value|...", no memory allocation

#include "tradingMessagesParser.h"

#include <iostream>
#include <cstddef> // size_t
#include <cctype> // std::isdigit fun
#include <charconv>

// Reads current field starting at start and ending at next '|' -> out
bool readMsgField(std::string_view msg, std::size_t& start, std::string_view& out) {

    // buffer ptr for current field
    if (start >= msg.size()) return false;
    const std::size_t end = msg.find('|', start);
    if (end == std::string_view::npos) return false;
    out = msg.substr(start, end - start);
    start = end + 1;

    return true;
}

// validate field has numeric digits
// no value validation here
// no atoi, no mem allocation
bool parseField(std::string_view field, int& tag, std::string_view& value) {
    
    // buffer field value
    const std::size_t pos = field.find('=');
    if (pos == std::string_view::npos or pos == 0) return false;

    // .data() returns a ptr to the (beginning of) string_view obj
    const char* begin = field.data();
    const char* end = field.data() + pos;

    // Parse tag using from_chars
    std::from_chars_result result = std::from_chars(begin, end, tag, 10);

    // from_chars_result has an error code filed .ec that is empty (==errc()) if successful
    // it also has a .ptr field that points at the first char not matching the pattern
    // or begin if nothing matches the pattern (+errc::invalid_argument)
    if (result.ec == std::errc::invalid_argument or result.ec == std::errc::result_out_of_range) return false;

    // parse value
    value = field.substr(pos + 1);
    return true;
}

// parse msg
// no dynamic mem allocation (no recursion)
// Explicit error modeling : handle unkonwn and incomplete fields/tags
ParserOutcomes parseMsg(std::string_view msg) {
    std::size_t pos = 0;
    std::string_view field;

    // read each field in msg
    while (readMsgField(msg, pos, field)) {
        
        // read tag and value
        int tag;
        std::string_view value;
        if (!parseField(field, tag, value)) return ParserOutcomes::bad_input;

        // tag type and values
        switch (tag) {
        case 35:
            if (value.size() < 1) return ParserOutcomes::bad_input;
            break;
        case 44:
            break;
        default:
            break;
        }
    }

    // IMPORTANT: msg missing fields or detect unterminated final field
    if (pos == 0 or pos != msg.size()) return ParserOutcomes::incomplete_input;
    
    return ParserOutcomes::done;
    
}


//
//int main()
//{
//    std::cout << "Hello World!\n";
//    const std::string_view msg = "35=D|55=AAPL|44|";
//
//    const ParserOutcomes result = parseMsg(msg);
//
//    if (result == ParserOutcomes::done) {
//        std::cout << "Message parsed successfully 2" << std::endl;
//    }
//    else if(result == ParserOutcomes::incomplete_input) {
//        std::cout << "incomplete_input" << std::endl;
//    }
//    else{
//        std::cout << "Message parse failed" << std::endl;
//    }
//
//    return 0;
//}
//

