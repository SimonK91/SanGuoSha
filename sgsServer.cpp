#include "sgsServer.h"


SgsServer::SgsServer()
{
  SDLNet_Init();

  //ställer in så att vi är redo att ta emot via angiven port
  SDLNet_ResolveHost(&server_ip, NULL, 1443);
  server_socket = SDLNet_TCP_Open(&server_ip);

  //allokerar plats och lägger till server_socket i ett socketset
  server_set = SDLNet_AllocSocketSet(2);
  SDLNet_TCP_AddSocket(server_set, server_socket);

  //mottagen / skickad
  send_string = "";

  running = true;
}

SgsServer::~SgsServer()
{
}


void SgsServer::run()
{
  while(running)
    {
      
      int ready = -1;
      ready = SDLNet_CheckSockets(server_set, 1000);
      
      if( SDLNet_SocketReady(server_socket) )
	{
	  std::cout << "socket ready" << std::endl;
	  char bufferten[512] = {0};
	  std::string received_string = "";
	  TCPsocket receive_socket = NULL;
	  receive_socket = SDLNet_TCP_Accept(server_socket);
	  
	  if( SDLNet_TCP_Recv(receive_socket, bufferten, 512) > 0 )
	    {
	      received_string.clear();
	      received_string = bufferten;
	      
	      if(received_string != "")
		{
		  std::string type_received = "";
		  type_received.append(received_string.begin(), received_string.begin()+4);
		  std::cout << "TYPE: " << type_received << std::endl;
		  
		  //en klient som vill ansluta
		  if(std::string(received_string.begin(),received_string.begin()+4) == "join")
		    {
		      remoteIP = SDLNet_TCP_GetPeerAddress(receive_socket);
		      ipaddr = SDL_SwapBE32(remoteIP->host);
		      
		      bool add_new_ip = true;
		      std::string ip_to_be_added = calculateIp(ipaddr);
		      for(auto i : ip_and_name)
			{
			  if(i.first == ip_to_be_added)
			    {
			      add_new_ip = false;
			    }
			}
		      if(add_new_ip == true)
			{
			  //lägger till den nya klienten i ip_addressens
			  std::string name(received_string.begin()+4, received_string.end());
			  ip_and_name.push_back(std::make_pair(ip_to_be_added, name));
			  all_clients.push_back(TCPsocket());
			  ip_addresses.push_back(IPaddress());
			  SDLNet_ResolveHost(&ip_addresses.back(), ip_to_be_added.c_str(), 1442);
			  
			}
		    }
		  
		  //ett chat meddelande togs emot
		  if(type_received == "chat")
		    {
		      addChat(received_string);
		    }
		  //ett kommando togs emot
		  else if( type_received == "command" )
		    {
		      addCommand(received_string);
		    }
		}  
	    }//recv
	}//socketReady

      sendToClients();
    }//running
}

void SgsServer::addChat(std::string chat_message)
{
  std::string message = "";
  message.append(chat_message.begin()+4, chat_message.end());
  
  chat_queue.push(message);
}

void SgsServer::addCommand(std::string received_command)
{
  std::string command = "";
  command.append(received_command.begin()+4, received_command.end());
  
  command_queue.push(command);		 
}

void SgsServer::sendToClients()
{
  //chat till klienter
  while( !chat_queue.empty() )
    {
      std::string send_chat = "chat"; 
      for(auto i : ip_addresses)
	{
	  TCPsocket send_to_socket = SDLNet_TCP_Open(&i);
	  send_chat += chat_queue.front();
	  
	  if( send_to_socket != NULL)
	    {
	      SDLNet_TCP_Send(send_to_socket, (void*) send_chat.c_str(), send_chat.length());
	      SDLNet_TCP_Close(send_to_socket);
	      std::cout << "skickar chat:" << send_chat << std::endl;
	    } 
	}
      chat_queue.pop();
    }
  //commandon till klienter
  while( !command_queue.empty() )
    {
      std::string send_command = "comm";
      for(auto i : ip_addresses)
	{
	  TCPsocket send_to_socket = SDLNet_TCP_Open(&i);
	  send_command += command_queue.front();
	  
	  if( send_to_socket != NULL)
	    {
	      SDLNet_TCP_Send(send_to_socket, (void*)send_command.c_str(), send_command.length());
	      SDLNet_TCP_Close(send_to_socket);
	      std::cout << "skickar kommando: " << send_command << std::endl;
	    }
	}
      command_queue.pop();
    }


}
std::string SgsServer::calculateIp(Uint32 raw_ip)
{
  //shift magi för att plocka fram ip addressen från en Uint32
  int shift;
  std::stringstream uint32_to_string;

  shift = ipaddr>>24;
  uint32_to_string << shift << ".";
  shift = (ipaddr>>16)&0xff;
  uint32_to_string << shift << ".";
  shift = (ipaddr>>8)&0xff;
  uint32_to_string << shift << ".";
  shift = ipaddr&0xff;
  uint32_to_string << shift;
  
  std::string calculated_ip = "";
  calculated_ip = uint32_to_string.str();

  std::cout << "IP: " << calculated_ip << std::endl;
  return calculated_ip;
}
