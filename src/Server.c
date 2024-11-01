#include "../include/Server.h"
#include "../include/parser.h"
#include "../include/request_handler.h"

void* handle_client(void*arg) {
  int client = *(int *)arg;
  free(arg);
  ssize_t valread;
  char buffer[1024] = { 0 };

  valread = read(client, buffer, 1024 - 1);
  if (valread > 0) {
    buffer[valread] = '\0';
  }

  Response res = handle_request(buffer);
  printf("%s\n", res.stringified);

  send(client, res.stringified, res.responseSize, 0);

  close(client);
  return NULL;
}

int main(int argc, char const* argv[])
{
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  socklen_t addrlen = sizeof(address);

  //create socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  //bind to port
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening for connections on port: %d\n", PORT);


  while (1) {
    int *client = malloc(sizeof(int));

    if ((*client = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    pthread_t thread;
    if (pthread_create(&thread, NULL, handle_client, client) != 0) {
      perror("Failed to create thread");
      return 1;
    }

    pthread_detach(thread);
  }

  close(server_fd);

  return 0;
}

