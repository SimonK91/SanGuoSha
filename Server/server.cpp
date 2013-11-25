#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <fstream>
#include <vector>
#include "StringInput.h"
#include <iostream>
#include <queue>
#include <sstream>

int main(int argc, char* argv[])
{
  //initerar SDL och de använda biblioteken
  SDL_Init(SDL_INIT_EVERYTHING);
  SDLNet_Init();
  TTF_Init();

  std::string chosenIP = "130.236.211.138";
  
  //de surfuces och font/color som används för att rita ut fönstret och texten
  SDL_Surface* screen = nullptr;
  SDL_Surface* background = nullptr;
  SDL_Event ev;

  //laddar surfuces, sätter textfärgen och laddar in fonten
  screen = SDL_SetVideoMode(400,480,32,SDL_SWSURFACE);
  SDL_WM_SetCaption("Server", NULL);

  //positionen för backgrunden
  SDL_Rect backRect;
  backRect.x = 0;
  backRect.y = 0;

  //positionen där ett nytt medelande ritas ut

  //SDLNet variabler  
  TCPsocket sd, csd;
  IPaddress ip, ip2;
  int len;
  char buffer[512];
  TCPsocket newsocket = NULL;
  
  std::vector<TCPsocket> all_clients; 
  //ta emot via denna port
  SDLNet_ResolveHost(&ip, NULL, 1443);
  //skicka till denna ip och port
  SDLNet_ResolveHost(&ip2,chosenIP.c_str(), 1442);

  sd = SDLNet_TCP_Open(&ip);

  //det inkomna medelandet
  std::string receivedStr = "";
  //medelandet som ska skickas
  std::string sendStr = "";
  std::vector<std::string> inV;

  background = IMG_Load("background.png");
  bool running = true;





  SDLNet_SocketSet clients;
  SDLNet_SocketSet server_set;
  server_set = SDLNet_AllocSocketSet(2);
  SDLNet_TCP_AddSocket(server_set, sd);
  TCPsocket client1;
  IPaddress ip11;
  TCPsocket client2;
  IPaddress ip22;
  IPaddress* remoteIP;
  IPaddress new_ip;
  Uint32 ipaddr;
  
  clients = SDLNet_AllocSocketSet(3);
  
  std::vector<std::queue<std::string>> chatlog;
  // chatlog.push_back( std::queue<std::string>);
  std::queue<std::string> chat_queue;
  //mainloop
  while(running)
    {
      while(SDL_PollEvent(&ev))
	{
	  if(ev.type == SDL_QUIT)
	    {
	      running = false;
	    }
	}
      
      //tar emot en sträng
       int ready = -1;
      ready = SDLNet_CheckSockets(server_set, 1000);
      //socketset test---------------      
      if(SDLNet_SocketReady(sd))
	{
	  char bufferten[512];
	  TCPsocket recieve_socket = NULL;
	  recieve_socket = SDLNet_TCP_Accept(sd);
	  std::cout << "förbi accept" << std::endl;

	  if(SDLNet_TCP_Recv(recieve_socket, bufferten, 512) > 0)
	    { 
	      std::cout << "förbi recv" << std::endl;
	      receivedStr = bufferten;
	      std::cout << receivedStr << std::endl;
	      if(receivedStr != "")
		{
		  if(receivedStr.substr(0,4) == "join")
		    {
		      int shift;
		      std::string tmp_address = "";
		      std::stringstream ss;
		      remoteIP = SDLNet_TCP_GetPeerAddress(recieve_socket);
		      ipaddr = SDL_SwapBE32(remoteIP->host);
		      // std::cout << SDLNet_Read32(&remoteIP->host) << std::endl;
		      shift = ipaddr>>24;
		      ss << shift << ".";
		      // std::cout << shift << ".";
		      shift = (ipaddr>>16)&0xff;
		      ss << shift << ".";
		      //std::cout << shift << ".";
		      shift = (ipaddr>>8)&0xff;
		      ss << shift << ".";
		      //std::cout << shift << ".";
		      shift = ipaddr&0xff;
		      ss << shift;
		      //std::cout << shift << " : ";
		      //shift = remoteIP->port;
		      //std::cout << shift << std::endl;
		      //std::cout << "client has joined" << std::endl;
		      tmp_address = ss.str();
		      std::cout << tmp_address << std::endl;
		      all_clients.push_back(TCPsocket());
		      SDLNet_ResolveHost(&new_ip, tmp_address.c_str(), 1442);
		      SDLNet_TCP_AddSocket(clients, all_clients.back());
		    }
		  else 
		    {
		      chat_queue.push(receivedStr);
		      std::cout << "tagit emot en strang" << std::endl;
		      newsocket = SDLNet_TCP_Open(&new_ip);
		      if( newsocket != NULL)
			{
			  std::cout << "skickar sträng" << std::endl;
			  std::string tmp_send =  chat_queue.front();;
			  chat_queue.pop();
		      
			  SDLNet_TCP_Send(newsocket, (void*) tmp_send.c_str(), tmp_send.length());
			  
			  SDLNet_TCP_Close(newsocket);
			}
		    }
		}
	    }
	  delete bufferten;
	}
      



	  //socketsettest-.------------
      if(( csd = SDLNet_TCP_Accept(sd)))
	{
	  char bufferten[512];

	  if(SDLNet_TCP_Recv(csd, bufferten, 512) > 0)
	    { 
	      receivedStr = bufferten;
	      if(receivedStr != "")
		{
		  if(receivedStr.substr(0,4) == "join")
		    {
		      std::cout << "client has joined" << std::endl;
		      all_clients.push_back(TCPsocket());
		      
		      SDLNet_TCP_AddSocket(clients, all_clients.back());
		    }
		}
	    }
	  else
	    {
	      SDLNet_TCP_Close(csd);
	    }
	}

      
      SDL_BlitSurface(background,NULL,screen, &backRect);
      
      //ritar ut alla inkomna medelanden
     
      SDL_Flip(screen);
    }//mainloop
  
  //städar inför avslut
  std::cout << chat_queue.front() << std::endl;
  SDL_FreeSurface(background);
  TTF_Quit();
  SDLNet_TCP_Close(sd);
  SDLNet_Quit();
  SDL_Quit();
  
  return 0;
}

