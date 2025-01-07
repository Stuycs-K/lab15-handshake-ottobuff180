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

int main() {
  int to_client;
  int from_client;
  signal(SIGPIPE, SIG_IGN);
  while(1){
    int from_client = server_setup();
    pid_t p = fork();
    if(p == 0){
      server_handshake_half( &to_client, from_client );
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
      exit(0);
    }
    sleep(1);
  }
}
