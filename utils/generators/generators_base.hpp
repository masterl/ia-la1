#ifndef GENERATORS_BASE_H
#define GENERATORS_BASE_H

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_right_alignment.hpp>
#include <boost/spirit/include/karma_symbols.hpp>

//#include <boost/spirit/include/karma_int.hpp>
//#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>

#include <string>

namespace generators
{
    namespace karma = boost::spirit::karma;
    namespace spirit = boost::spirit;
    namespace ascii = boost::spirit::ascii;
    using spirit::long_;
    using spirit::float_;
    using spirit::right_align;

    bool long_to_string(std::string &str,long number);
    bool float_to_string(std::string &str,float number);
}

namespace gen = generators;

#endif
