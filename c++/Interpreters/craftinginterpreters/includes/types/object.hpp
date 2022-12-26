#pragma once 

#include <string>
#include <variant>


typedef struct null_t
{
    template<typename T>
	bool operator==( T const& rhs ) const
	{
		return typeof(rhs) == typeid(null_t);
	}
	
} null_t;

typedef std::variant<null_t, int, double, std::string> object_t;