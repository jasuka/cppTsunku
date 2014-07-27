/*
 * IrcBot.cpp
 *
 *  Created on: 15 Jul 2011
 *      Author: tyler
 *
 *  Modified July 2014
 *      Authors: jaska & hrna
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
#include "cstd.h"


#define MAXDATASIZE 100


IrcBot::IrcBot(const char *_nick, const char *_usr)
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
	unsigned int res;
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
	long numbytes;
	char buf[MAXDATASIZE];	;
    std::vector<std::string> words;

	unsigned int count = 0;
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
            {
                sendData("PONG " + words[1]);
            	std::cout << "DEBUG: pong sent: " << words[1] << std::endl;
            }
        }
        
        //buf is the data that is recived
        //std::cout << timeNow() << " " << buf;


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
std::string IrcBot::timeNow()
{
	time_t rawtime;
	struct tm *timeinfo;
    char buffer[80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%H:%M:%S",timeinfo);
    std::string time = buffer;
    return time;
}

//Send data to the server
bool IrcBot::sendData(std::string msg)
{
	
    msg.append("\r\n");
	unsigned long bytes_sent = send(s,msg.c_str(),msg.length(),0);

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
        if (words[3].compare(":kettu") == 0) { sendData("PRIVMSG "+ chan +" :kettu sanottu!"); }
        if (words[3] == ":homo")
        {
            sendData("PRIVMSG " + chan + " :ite oot!");
        }
        if (words[3] == ":!quit")
        {
            sendData("PRIVMSG " + chan + " :Nyt mie lähen!");
            sendData("QUIT :Soronoo!");
            close (s);
            std::exit(0);
        }
        if (words[3] == ":!time")
        {
            sendData("PRIVMSG " + chan + " :The local time is: " + timeNow());
        }
        if (words.size() == 5 && words[3] == ":!nick")
        {
            nick = words[4].c_str();
            sendData("NICK " + std::string(nick));
        }
    }
    

}

// Split sentence to words
std::vector<std::string> IrcBot::splitWords(char *buf)
{
    /**std::string str(buf);
    std::istringstream stm(str);
    std::vector<std::string> words;
    std::string word;
    
    while( stm >> word ) // read white-space delimited tokens one by one
    {
        words.push_back(word);
        
    }
	--THIS IS REPLACED WITH Cstd::explode();--
    **/
    std::vector<std::string> words;
    words = Cstd::explode(buf, " ");
    return words;
}


