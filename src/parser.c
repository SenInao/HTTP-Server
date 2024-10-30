#include <string.h>
#include "../include/Server.h"

Request parse_request(char* request) {
  Request http_req;
  http_req.request = strdup(request);

  const char s[2] = " ";
  const char s1[2] = "\r";
  char* token;

  token = strtok(request, s);
  http_req.method = token;
  token = strtok(NULL, s);
  http_req.path = token;
  token = strtok(NULL, s1);
  http_req.version = token;

  return http_req;
}

void parse_headers(Request* http_req) {
  const char *headers = strstr(http_req->request, "\r\n") + 2;

  http_req->headers_len = 0;
  http_req->headers = malloc(sizeof(HTTP_HEADER*));

  while (*headers != '\r' && *(headers+1) != '\n') {
    char header_name[512], header_value[512];
    sscanf(headers, "%[^:]: %[^\r\n]", header_name, header_value);
    headers = strstr(headers, "\r\n") + 2;

    http_req->headers_len++;
    http_req->headers = realloc(http_req->headers, sizeof(HTTP_HEADER*)*http_req->headers_len);

    HTTP_HEADER *header = malloc(sizeof(HTTP_HEADER));
    header->name = strdup(header_name);
    header->value = strdup(header_value);

    http_req->headers[http_req->headers_len-1] = header;
  }
}
