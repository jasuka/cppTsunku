/*
 * main.cpp
 *
 *  Created on: 15 Jul 2011
 *      Author: tyler
 *
 *  Modified July 2014
 *      Authors: jaska & hrna
 */

#include <iostream>
#include "IrcBot.h"

int main()
{
	IrcBot bot = IrcBot("NICK cTsunku\r\n","USER pillu pillu pillu :cTsunku\r\n");
    bot.start();

  return 0;

}
