#include "./Server.h"

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

typedef struct Response {
  char* version;
  char* status;
  char* message;

  HTTP_HEADER** headers;
  int header_count;

  char* body;

  char* stringified;
  size_t responseSize;
} Response;

Response handle_get(Request request);
Response handle_request(char* raw_req);
char* stringify_res(Response* response);
void add_header(HTTP_HEADER*** headers, int* header_count, char* name, char* value);
Response build_res(char* version, char* status, char* message, HTTP_HEADER** headers, int* header_count, char* body);

#endif
