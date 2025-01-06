#include "pipe_networking.h"

int main() {
  int to_client;
  int to_server;
  to_server = server_handshake( &to_client );
  
  char byte[1];
  read(to_server,byte,sizeof(byte));
  printf("%c\n",byte[0]);
  close(to_server);
  close(to_client);
}
