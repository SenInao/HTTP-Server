#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8888

int main(int argc, char const* argv[])
{
  int status, client_fd;
  struct sockaddr_in serv_addr;

  if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf(
      "\nInvalid address/ Address not supported \n");
    return -1;
  }


  printf("Connecting to server on port: %d\n", PORT);

  if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  printf("Connected to server\n");

  char * data = 
    "GET / HTTP/1.1\r\n"
    "HOST: example.com:8000\r\n"
    "Upgrade: websocket\r\n"
    "Connection: Upgrade\r\n"
    "Sec-Websocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
    "Sec-WebSocket-Version: 13\r\n"
    "\r\n";

  printf("Sending data\n");
  send(client_fd, data, strlen(data), 0);

  ssize_t valread;
  char buffer[1024] = { 0 };

  valread = read(client_fd, buffer, 1024 - 1);
  if (valread > 0) {
    buffer[valread] = '\0';
  }

  printf("%s\n", buffer);

  // closing the connected socket
  close(client_fd);
  return 0;
}
