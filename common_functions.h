#ifndef COMMON_FUNCTIONS_H
#define	COMMON_FUNCTIONS_H


// Because atoi was buggy this day :<
template <typename T>
T StringToNumber ( const std::string &Text, T defValue = T() )
{
    std::stringstream ss;
    for ( std::string::const_iterator i=Text.begin(); i!=Text.end(); ++i )
        if ( isdigit(*i) || *i=='e' || *i=='-' || *i=='+' || *i=='.' )
            ss << *i;
    T result;
    return ss >> result ? result : defValue;
}


#endif	/* COMMON_FUNCTIONS_H */

