/*
 * IrcBot.cpp
 *
 *  Created on: 15 Jul 2011
 *      Author: tyler
 */

#include "IrcBot.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctime>
#include <iomanip>

#define MAXDATASIZE 100


IrcBot::IrcBot(const char * _nick, const char * _usr)
{
	nick = _nick;
	usr = _usr;
}

IrcBot::~IrcBot()
{
	close (s);
}

void IrcBot::start()
{
	struct addrinfo hints, *servinfo;
	//Setup run with no errors
	setup = true;
	port = "6667";

	//Ensure that servinfo is clear
	memset(&hints, 0, sizeof hints); // make sure the struct is empty

	//setup hints
	hints.ai_family = AF_INET; // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	//Setup the structs if error print why
	int res;
	if ((res = getaddrinfo("b0xi.eu",port,&hints,&servinfo)) != 0)
	{
		setup = false;
		fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(res));
	}


	//setup the socket
	if ((s = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol)) == -1)
	{
		perror("client: socket");
	}

	//Connect
	if (connect(s,servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close (s);
		perror("Client Connect");
	}


	//We dont need this anymore
	freeaddrinfo(servinfo);


	//Recv some data
	int numbytes;
	char buf[MAXDATASIZE];
    std::vector<std::string> words;

	int count = 0;
	while (1)
	{
		//Count received data
		count++;

		switch (count) {
			case 3:
					//after 3 receives send data to server (as per IRC protocol)
					sendData(nick);
					sendData(usr);
				break;
			case 4:
					//Join a channel after we connect
				sendData("JOIN #tsunku");
                sendData("JOIN #admins");
			default:
				break;
		}

		//Recv & print Data
		numbytes = recv(s,buf,MAXDATASIZE-1,0);
		buf[numbytes]='\0';
        words = splitWords(buf);
        
        //Pass buf to the message handeler
        msgHandle(words);
        
        // Pong if Ping received
        if (words.size() > 0)
        {
            if (words[0].compare("PING") == 0)
                sendData("PONG " + words[1]);
        }
        
        //buf is the data that is recived
        std::cout << getTime() << " " << buf;


		//break if connection closed
		if (numbytes==0)
		{
            std::cout << "----------------------CONNECTION CLOSED---------------------------"<< std::endl;
            std::cout << timeNow() << std::endl;

			break;
		}
	}
}

// Returns the current time
char * IrcBot::timeNow()
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	return asctime (timeinfo);
}

std::string IrcBot::getTime()
{
    std::stringstream now;
    std::time_t localtime =  std::time(nullptr);
    now << std::put_time(std::localtime(&localtime), "%H:%M:%S");
    return now.str();
}

//Send data to the server
bool IrcBot::sendData(std::string msg)
{
	
    msg.append("\r\n");
	unsigned long len = msg.length();
	unsigned long bytes_sent = send(s,msg.c_str(),len,0);

	if (bytes_sent == 0)
		return false;
	else
		return true;
}

//Handle messages
void IrcBot::msgHandle(std::vector<std::string> words)
{
	/*
	 * TODO: add you code to respod to commands here
    */
    if (words.size() >= 4)
    {
        std::string chan = words[2];
        if (words[3].compare(":homo") == 0)
        {
            sendData("PRIVMSG " + chan + " :ite oot!");
        }
        if (words[3].compare(":!quit") == 0)
        {
            sendData("PRIVMSG " + chan + " :Nyt mie lähen!");
            sendData("QUIT :Soronoo!");
            close (s);
            std::exit(0);
        }
        if (words[3].compare(":!time") == 0)
        {
            sendData("PRIVMSG " + chan + " :The local time is: " + getTime());
        }
        if (words.size() == 5 && words[3].compare(":!nick") == 0)
        {
            nick = words[4].c_str();
            sendData("NICK " + std::string(nick));
        }
    }
    

}

// Split sentence to words
std::vector<std::string> IrcBot::splitWords(char *buf)
{
    std::string str(buf);
    std::istringstream stm(str);
    std::vector<std::string> words;
    std::string word;
    
    while( stm >> word ) // read white-space delimited tokens one by one
    {
        words.push_back(word);
        
    }
    return words;
}

