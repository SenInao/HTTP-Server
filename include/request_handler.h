#include "./Server.h"

typedef struct Response {
  char* version;
  char* status;
  char* message;

  HTTP_HEADER** headers;

  char* body;

  char* stringified;
  size_t responseSize;
} Response;

Response handle_request(char* request);
Response handle_get(Request request);
