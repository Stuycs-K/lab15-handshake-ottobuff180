#include "pipe_networking.h"

int main() {
  int to_server;
  int to_client;
  to_client = client_handshake( &to_server );
  
  char byte[1];
  byte[0] = 'a';
  write(to_server,byte,sizeof(byte));
  close(to_server);
  close(to_client);
}
