#include <iostream>
#include "IrcBot.h"


using namespace std;


int main()
{
	IrcBot bot = IrcBot("NICK cTsunku\r\n","USER pillu pillu pillu :cTsunku\r\n");
    bot.start();

  return 0;

}
