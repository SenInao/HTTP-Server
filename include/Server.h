#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

typedef struct HTTP_HEADER {
  char* name;
  size_t name_len;
  char* value;
  size_t value_len;
} HTTP_HEADER;

typedef struct Request{
  char* method;
  char* path;
  char* version;
  HTTP_HEADER **headers;
  int headers_len;

  char* body;
  // Other headers as needed
  char *request; // Pointer to the raw request string
} Request;

#endif
