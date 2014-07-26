#ifndef __CSTD__
#define __CSTD__

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

class Cstd {
public:
	static std::vector<std::string> explode(std::string input, const char *seperator);
};

#endif