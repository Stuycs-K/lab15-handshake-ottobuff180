#include "pipe_networking.h"
#include <time.h>


int randomint(){
  int r_file = open("/dev/random", O_RDONLY , 0);
  
  int buff;
  int *p = &buff;
  int bytes = read(r_file, p, sizeof(int));
  
  close(r_file);
  
  return buff;
}


void signal_handler(int signum) {
  printf("server exited\n");
  unlink(WKP);
  exit(1);
}

int main() {
  int to_client;
  int from_client;
  signal(SIGINT, signal_handler);
  signal(SIGPIPE, SIG_IGN);
  while(1){
    from_client = server_handshake( &to_client );
    while(1){
      int ran = randomint();
      int i = write(to_client,&ran,sizeof(ran));
      if(i <= 0){
        printf("client exited\n");
        break;
      }
      sleep(1);
    }
    close(from_client);
    close(to_client);
  }
}

