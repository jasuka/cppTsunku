/**
  cstd.cpp
 
    Created on: 26 Jul 2014
       Author: hrna
       
 **/
#ifndef __CSTRLIB_H__
#define __CSTRLIB_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

class Cstrlib {
public:
	static std::vector<std::string> explode(std::string input, const char *separator);
};

#endif