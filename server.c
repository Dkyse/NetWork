#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()  {

  int s = socket(AF_INET, SOCK_STREAM, 0);

  if(s == -1) {
    perror("socket failed");
    exit(2);
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4444);

  if(bind(s, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) {
    perror("bind failed");
    exit(2);
  }

  if(listen(s, 2)) {
    perror("listen failed");
    exit(2);
  }

  struct sockaddr_in client_addr;
  socklen_t client_addr_length = sizeof(struct sockaddr_in);
  int client_socket = accept(s, (struct sockaddr*)&client_addr, &client_addr_length);

  if(client_socket == -1) {
    perror("accept failed");
    exit(2);
  }


  char buffer[256];
  int bytes_read = read(s, buffer, 256);
  if(bytes_read < 0) {
    perror("read failed");
    exit(2);
  }

  printf("Client sent: %s\n", buffer);


  char* msg = "Hello client.\n";
  write(client_socket, msg, strlen(msg));



  close(client_socket);
  close(s);

}
