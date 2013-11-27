
#ifndef SGSSERVER_H
#define SGSSERVER_H

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


class SgsServer
{
private:
  //anv�nds f�r att ta fram ip fr�n anslutande klient
  IPaddress* remoteIP;
  Uint32 ipaddr;

  //vektor med alla anslutana klienter
  std::vector<IPaddress> ip_addresses;
  std::vector<TCPsocket> all_clients;

  //anv�nds ej
  SDLNet_SocketSet clients;

  //socketen som alla klienter skickar till (den servern tar emot fr�n) och dess ip
  TCPsocket server_socket;
  IPaddress server_ip;
  SDLNet_SocketSet server_set;
  
  std::string received_string;
  std::string send_string;

  //tempor�r lagring av inkommen chat
  std::queue< std::string> chat_queue; 


  bool running;
public:
  SgsServer();
  ~SgsServer();

  void run();
  

};
#endif
