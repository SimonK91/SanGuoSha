#include "Network.h"
#include <iostream>
#include <sstream>


Network::Network()
{
  SDLNet_Init();
  
 
  SDLNet_ResolveHost(&program_ip, NULL, 1442);
 
  incomming = SDLNet_TCP_Open(&program_ip);
  in_set =  SDLNet_AllocSocketSet(1);
  SDLNet_TCP_AddSocket(in_set, incomming);
 
}


Network::~Network()
{
}

void Network::sendChat(std::string message)
{
  std::string type = "chat";
  std::string name = "ClientX";
  outgoing = SDLNet_TCP_Open(&server_ip);
  if(outgoing == NULL)
    {
      std::cerr << "Kunde inte skicka chat messages till servern" << std::endl;
    }
  else
    {
      std::string complete_message = type;
      complete_message += name;
      complete_message += "|";
      complete_message += message;
      SDLNet_TCP_Send(outgoing, (void*)complete_message.c_str(), complete_message.length());
    }
    SDLNet_TCP_Close(outgoing);
}

void Network::sendCommand(std::string command)
{
  std::string type = "comm";
  
  outgoing = SDLNet_TCP_Open(&server_ip);
  if(outgoing == NULL)
    {
      std::cerr << "Kunde inte skicka kommandon till servern" << std::endl;
    }
  else
    {
      std::string complete_command = type;
      complete_command += command;
      SDLNet_TCP_Send(outgoing, (void*)complete_command.c_str(), complete_command.length());
    }
  SDLNet_TCP_Close(outgoing);
  
}

void Network::getData()
{
  char buffer[512] = {0};
  std::string received = "";
  std::string type_received = "";

  int ready = -1;
  ready = SDLNet_CheckSockets(in_set, 10);

      if(SDLNet_SocketReady(incomming))
	{
	  program_socket = SDLNet_TCP_Accept(incomming);
	  
	  if(SDLNet_TCP_Recv(program_socket, buffer, 512) > 0)
	    {
	      received = buffer;
	      if(received != "")
		{
		  type_received.append(received.begin(), received.begin()+4);
		  if(type_received == "chat")
		    {
		      std::string name = "";
		      std::string message = "";
		      size_t string_pos = received.find_first_of("|");
		      name.append(received.begin()+4, received.begin()+string_pos);
		      message.append(received.begin()+string_pos+1, received.end() );
		      chat_log.push_back(std::make_pair(name,message));
		    }
		  else if(type_received == "comm")
		    {
		      std::string command = "";
		      command.append(received.begin()+4, received.end());
		      command_queue.push(command);
		    }
		  else
		    {
		      std::cerr << "Oväntad data från server: " << received << "  av typ: " << type_received << std::endl;
		    }
		}  
	    }
	  else
	    {
	      SDLNet_TCP_Close(program_socket);
	    }
	}

}


const std::vector<std::pair<std::string,std::string>>& Network::getLog()
{
  return chat_log;
}

std::queue<std::string>& Network::getCommandQueue()
{
  return command_queue;
}

void Network::showMeDasLog()
{
  for(auto i : chat_log)
    {
      std::cout << i.first << "   " << i.second << std::endl;
    }

}

void Network::connectToServer(std::string server_ip_string)
{
  SDLNet_ResolveHost(&server_ip, server_ip_string.c_str(), 1443);
  outgoing = SDLNet_TCP_Open(&server_ip);
  
  std::string name = "ClientX";
  std::string join_server = "join";
  join_server += name;
  SDLNet_TCP_Send(outgoing, (void*)join_server.c_str(),join_server.length());
  SDLNet_TCP_Close(outgoing);
}
