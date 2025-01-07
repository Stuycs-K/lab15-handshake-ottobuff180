#include "pipe_networking.h"

int main() {
  int to_server;
  int to_client;
  to_client = client_handshake( &to_server );
  
  while(1){
    int ran;
    int i = read(to_client,&ran,sizeof(ran));
    if(i <= 0){
      exit(1);
    }
    printf("%d\n", ran);
  }
}
