#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
typedef struct HTTP_REQUEST {
  char method[8];
  char path[1024];
  char version[16];
  char host[512];
  char user_agent[256];
  char accept[128];
  char accept_encoding[128];
  char accept_language[64];
  char content_type[64];
  char content_length[16];
  char connection[64];
  char cache_control[64];
  char authorization[128];
  char cookie[512];
  char sec_websocket_key[128];
  char sec_websocket_version[16];
  char sec_websocket_protocol[64];
  char referer[256];
  char origin[256];
  // Other headers as needed
  char *request; // Pointer to the raw request string
} HTTP_REQUEST;

#endif
