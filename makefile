compile: basic_client basic_server persistant_server forking_server

server: force
	./forking_server
	
client: force
	./client

force: ;

basic_client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

basic_server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

persistant_server: persistant_server.o pipe_networking.o
	gcc -o persistant_server persistant_server.o pipe_networking.o

forking_server: forking_server.o pipe_networking.o
	gcc -o forking_server forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

persistant_server.o: persistant_server.c pipe_networking.h
	gcc -c persistant_server.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
