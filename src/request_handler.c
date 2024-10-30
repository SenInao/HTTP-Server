#include "../include/Server.h"
#include "../include/parser.h"
#include "../include/request_handler.h"
#include <stdio.h>
#include <string.h>

Response createResponse(char* version, char*status, char* message, HTTP_HEADER**headers) {
  Response response;
  response.version = strdup(version);
  response.status = strdup(status);
  response.message = strdup(message);
  response.headers = headers;
  return response;
}

void responseToString(Response* response) {
  size_t buff_size = strlen(response->version) + strlen(response->status) + strlen(response->message) + 5;
  response->stringified = malloc(buff_size);
  snprintf(response->stringified, buff_size, "%s %s %s\r\n\r\n", response->version, response->status, response->message);
  response->responseSize = buff_size;
}

Response handle_request(char* raw_req) {
  printf("Handling request:\n%s\n", raw_req);
  Request request = parse_request(raw_req);
  parse_headers(&request);
  
  return handle_get(request);
}

Response handle_get(Request request) {
  Response response = createResponse(request.version, "200", "OK", request.headers);
  responseToString(&response);
  return response;
}
