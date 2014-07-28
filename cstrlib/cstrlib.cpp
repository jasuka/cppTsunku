/**
  cstd.cpp
 
    Created on: 26 Jul 2014
       Author: hrna

	EXPLODE as seen in PHP
	Usage of the explode function as follows:

	Cstd::explode(string, seperator);

	std::vector<std::string> myvar;
	myvar = Cstd::explode("some random strings here", " ");

	myvar[1] would be "random".

	It still bugs if the separator is something else than a whitespace

	compile: g++ -std=c++11 main.cpp cstd.cpp -o cstd

	The character stripper is added to support the IRCbot project

**/
#include "cstrlib.h"

std::vector<std::string> Cstrlib::explode(std::string input, const char *separator) {

	std::vector<std::string> saveVctr;
	std::string saveStr;
	
   char chars[] = "\r\n"; //Characters to be stripped off.

   for (unsigned int i = 0; i < strlen(chars); ++i) //the strip off loop
   {
      input.erase (std::remove(input.begin(), input.end(), chars[i]), input.end());
   }

	for (unsigned int i = 0; i < input.size(); ++i)
	{
		if (input[i] != *separator)
		{
			saveStr += input[i];
		} else {
			saveVctr.push_back (saveStr);
			saveStr.clear();
			//saveStr += input[i]; 	//cases where separator is something else than ' '...
									//dont really know how would i deal with it..
		}
	}
	saveVctr.push_back (saveStr);
	saveStr.clear();
	return saveVctr;
}