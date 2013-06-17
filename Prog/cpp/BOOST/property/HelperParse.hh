#ifndef HelperParse_hh
#define HelperParse_hh

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace Helper {

// Helper
bool parseQuoted(const std::string& input, std::string& output);

// Parse Scalar
//
template<typename T>
bool
parseScalar(const std::string& input, T& output) {
    std::string noquote_str;
    bool b = parseQuoted(input, noquote_str);
    if (b) {
        // parse the quote str successfully
    } else {
        // maybe no quote exists
        noquote_str = input;
    }

    std::stringstream ss;
    ss << noquote_str;
    ss >> output;

    return not ss.fail();
}

template<>
bool
parseScalar<std::string>(const std::string& input, std::string& output);
// Parse Vector
//

template<typename T>
bool
parseVector(const std::string& input, std::vector<T>& output) {
    // First, parse the string version
    std::vector<std::string> str_vector;
    bool b = parseVector(input, str_vector);
    if (not b) {
        // Fail to parse
        std::cout << "Failed to parse vector<str>" << std::endl;
        return b;
    }
    // Then, convert to the T version.
    T tmp_var;
    for (std::vector<std::string>::iterator it=str_vector.begin();
            it != str_vector.end();
            ++it) {
        std::stringstream ss;
        ss << (*it);
        ss >> tmp_var;
        if (not ss.fail()) {
            output.push_back(tmp_var);
        } else {
            // Failed
            return false;
        }
    }
    return true;
}

template<>
bool
parseVector<std::string>(const std::string& input, 
                         std::vector<std::string>& output);

// Parse Dict
}

#endif
