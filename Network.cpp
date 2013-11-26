#include "Network.h"
#include <iostream>
#include <sstream>

Network::Network()
{
  SDLNet_Init();
  
  SDLNet_ResolveHost(&server_ip, "130.236.226.197", 1443);
  SDLNet_ResolveHost(&program_ip, NULL, 1442);
 
  incomming = SDLNet_TCP_Open(&program_ip);
  in_set =  SDLNet_AllocSocketSet(1);
  SDLNet_TCP_AddSocket(in_set, incomming);
 
  /* out_set = SDLNet_AöllocSocketSet(1);
  SDLNet_TCP_AddSocket(out_set, outgoing);
  */
}


Network::~Network()
{
}

void Network::sendChat(std::string message)
{
  std::string name = "";
  outgoing = SDLNet_TCP_Open(&server_ip);
  if(outgoing ==  NULL)
    {
      std::cout << "nope" << std::endl;
    }
  if( outgoing != NULL )
    {
      //message += "|";
      // message += name;
      SDLNet_TCP_Send(outgoing, (void*)message.c_str(), message.length());
	  std::cout << "message: " << message << "  length: " << message.length() << "  size: " << message.size() << std::endl;
    }
  
    SDLNet_TCP_Close(outgoing);
}

void Network::sendCommand(std::string command)
{
  
  
}

void Network::getChat()
{
	char buffer[512] = {0};
  std::string recieved = "";
  std::string name = "";
  std::string message = "";
  int ready = -1;
  ready = SDLNet_CheckSockets(in_set, 10);
 
      std::cout << "ready: " << ready << std::endl;
      if(SDLNet_SocketReady(incomming))
	{
	  program_socket = SDLNet_TCP_Accept(incomming);
	  
	  if(SDLNet_TCP_Recv(program_socket, buffer, 512) > 0)
	    {
	      recieved = buffer;
	      if(recieved != "")
		{
		  
		  name = recieved.substr(0,8);
		  message = recieved.substr(8,recieved.size());
		  chat_log.push_back(std::make_pair(name,message));
		}  
	      
	    }
	  else
	    {
	      SDLNet_TCP_Close(program_socket);
	    }
	}

}

bool Network::getCommand()
{
  return false;
}

const std::vector<std::pair<std::string,std::string>>& Network::getLog()
{
  return chat_log;
}

void Network::showMeDasLog()
{
  for(auto i : chat_log)
    {
      std::cout << i.first << "   " << i.second << std::endl;
    }

  Uint32* dotQuad = &program_ip.host;
 
  std::stringstream ss;
  ss << dotQuad;
  
  std::string my_ip_address;
  my_ip_address = ss.str();
  /*
  my_ip_address += (unsigned short)dotQuad[0];
  my_ip_address += ".";
  my_ip_address += (unsigned short)dotQuad[1];
  my_ip_address += ".";
  my_ip_address += (unsigned short)dotQuad[2];
  my_ip_address += ".";
  my_ip_address += (unsigned short)dotQuad[3];
  */
  std::cout << "my ip is:  " << my_ip_address  << std::endl;

}
