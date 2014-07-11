/*
 * IrcBot.h
 *
 *  Created on: 15 Jul 2011
 *      Author: tyler
 */
#include <string>
#include <vector>

#ifndef IRCBOT_H_
#define IRCBOT_H_

class IrcBot
{
public:
	IrcBot(const char * _nick, const char * _usr);
	virtual ~IrcBot();

	bool setup;

	void start();

private:
	const char *port;
	int s; //the socket descriptor

	const char *nick;
	const char *usr;

	char * timeNow();

    std::string getTime();
    
	bool sendData(std::string msg);

	void msgHandle(std::vector<std::string>);

    std::vector<std::string> splitWords(char *buf);
    
};

#endif /* IRCBOT_H_ */