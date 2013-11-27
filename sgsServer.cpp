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
  received_string = "";
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
	  
	  TCPsocket receive_socket = NULL;
	  receive_socket = SDLNet_TCP_Accept(server_socket);
	  
	  if( SDLNet_TCP_Recv(receive_socket, bufferten, 512) > 0 )
	    {
	      std::cout << "recv" << std::endl;
	      received_string.clear();;
	      received_string = bufferten;
	      std::cout << "strangen: " << received_string << " mottogs" << std::endl;
	      
	      if(received_string != "")
		{
		  //klient som vill bli tillagt
		  if(received_string == "join")
		    {
		      std::cout << "Join" << std::endl;
		      //shift magi för att plocka fram ip addressen från en Uint 32
		      int shift;
		      std::string tmp_address = "";
		      std::stringstream ss;
		      
		      remoteIP = SDLNet_TCP_GetPeerAddress(receive_socket);
		      ipaddr = SDL_SwapBE32(remoteIP->host);
		      shift = ipaddr>>24;
		      ss << shift << ".";
		      shift = (ipaddr>>16)&0xff;
		      ss << shift << ".";
		      shift = (ipaddr>>8)&0xff;
		      ss << shift << ".";
		      shift = ipaddr&0xff;
		      ss << shift;
		      tmp_address = ss.str();
		      std::cout << tmp_address << std::endl;

		      //lägger till den nya klienten i ip_addressens
		      all_clients.push_back(TCPsocket());
		      ip_addresses.push_back(IPaddress());
		      SDLNet_ResolveHost(&ip_addresses.back(), tmp_address.c_str(), 1442);
		      std::cout << "IP: " << tmp_address << std::endl;
		    }
		  else
		    {
		      chat_queue.push(received_string);
		      
		      for(auto i : ip_addresses)
			{
			  
			  TCPsocket send_to_socket = SDLNet_TCP_Open(&i);
			  
			  if( send_to_socket != NULL)
			    {
			      std::string tmp_send = "Client X";
			      tmp_send += chat_queue.front();
			      
			      SDLNet_TCP_Send(send_to_socket, (void*) tmp_send.c_str(), tmp_send.length());
			      SDLNet_TCP_Close(send_to_socket);
			      std::cout << "skicar :" << tmp_send << std::endl;
			    } 
			}
		      if(!chat_queue.empty())
			{
			  chat_queue.pop();
			}
		    }
		}  
	    }//recv
	}//socketReady
    }//running
}
