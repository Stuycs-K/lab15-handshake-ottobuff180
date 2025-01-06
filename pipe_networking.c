#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  printf("server 1\n");
  mkfifo(WKP, 0644);
  printf("server 2\n");
  int p1 = open(WKP, O_RDONLY);
  printf("server 4\n");
  unlink(WKP);
  return p1;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int to_server = server_setup();
  char pp[100];
  read(to_server,pp,sizeof(pp));
  printf("server 5: %s\n",pp);
  printf("server 6\n");
  *to_client = open(pp, O_WRONLY);
  int synack = getpid();
  printf("server 7: %d\n",synack);
  write(*to_client,&synack,sizeof(synack));
  int finalack;
  printf("server 9\n");
  read(to_server,&finalack,sizeof(finalack));
  printf("server 9: %d\n",finalack);
  return to_server;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char pp[100];
  sprintf(pp,"%d",getpid());
  printf("client 3: %s\n",pp);
  mkfifo(pp, 0644);
  *to_server = open(WKP, O_WRONLY);
  write(*to_server,pp,sizeof(pp));
  int downstream = open(pp, O_RDONLY);
  printf("client 8\n");
  unlink(pp);
  int synack;
  read(downstream,&synack,sizeof(synack));
  printf("client 8: %d\n",synack);
  synack++;
  printf("client 8: %d\n",synack);
  write(*to_server,&synack,sizeof(synack));
  return downstream;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


