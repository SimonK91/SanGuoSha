#ifndef NETWORK_H
#define NETWORK_H

#include "SDL/SDL_net.h"
#include <string>
#include "SDL/SDL_thread.h"
#include <vector>
#include "settings.h"
#include <queue>

class Network
{

 private:
  //servern, skicka data hit
  IPaddress server_ip;
  TCPsocket server_socket;
  SDLNet_SocketSet out_set;
  //programmet, data tas emot här
  IPaddress program_ip;
  TCPsocket program_socket;
  SDLNet_SocketSet in_set;

  //i bufferten landar datat som emot från servern
  

  TCPsocket incomming;
  TCPsocket outgoing;

  std::vector< std::pair<std::string,std::string> >  chat_log;
  std::queue< std::string> command_queue;
  
  //Settings set;
  
 public:
  Network();
  ~Network();

  void sendChat(std::string message);
  void sendCommand(std::string command);
  void getData();
  const std::vector<std::pair<std::string,std::string>>& getLog();
  void showMeDasLog();
  void connectToServer(std::string);



};

#endif
