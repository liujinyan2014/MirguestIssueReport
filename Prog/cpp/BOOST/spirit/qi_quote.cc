#include <iostream>
#include <boost/spirit/include/qi.hpp>         // Parsing
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted.hpp>

using namespace boost::spirit;

bool quick_parse(std::string str) {

    qi::rule<std::string::iterator, 
             std::string(), 
             ascii::space_type> quoted_string;
    quoted_string %= qi::lexeme[
                     (qi::lit("'")
                  >> +("\\'"|(ascii::char_ - qi::lit("'")))
                  >> qi::lit("'"))
                     |
                     (qi::lit("\"")
                  >> +("\\\""|(ascii::char_ - qi::lit("\"")))
                  >> qi::lit("\""))
                     ];

    std::string result;
    std::string::iterator strbegin;

    strbegin = str.begin();
    bool r = qi::phrase_parse(strbegin, str.end(),
            quoted_string,
            ascii::space,
            result);
    std::cout << "----------------------" << std::endl;
    std::cout << "string: " << str << std::endl;
    std::cout << r << std::endl;
    std::cout << result << std::endl;
    std::cout << "----------------------" << std::endl;

}

int main() {

    // no quote
    // single quote
    std::string str_s_1("'hello, world'");
    std::string str_s_2("'hello,\" world'");
    std::string str_s_3("'hello,\\\" world'");
    std::string str_s_4("'hello,\\' world'");
    std::string str_s_5("'hello,\\\' world'");
    // double quote
    std::string str_d_1("\"hello, world\"");
    std::string str_d_2("\"hello,\" world\"");
    std::string str_d_3("\"hello,\\\" world\"");
    std::string str_d_4("\"hello,\' world\"");
    std::string str_d_5("\"hello,\\\' world\"");

    quick_parse(str_s_1);
    quick_parse(str_s_2);
    quick_parse(str_s_3);
    quick_parse(str_s_4);
    quick_parse(str_s_5);
    quick_parse(str_d_1);
    quick_parse(str_d_2);
    quick_parse(str_d_3);
    quick_parse(str_d_4);
    quick_parse(str_d_5);

}
