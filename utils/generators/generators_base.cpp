#include "generators_base.hpp"

bool generators::long_to_string(std::string &str,long number)
{
    std::back_insert_iterator<std::string> out(str);
    return karma::generate(out,long_,number);
}

bool generators::float_to_string(std::string &str,float number)
{
    str.clear(); 
    std::back_insert_iterator<std::string> out(str);
    return karma::generate(out,float_,number);
}