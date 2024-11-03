#include "../include/Server.h"
#include "../include/parser.h"
#include "../include/request_handler.h"
#include "../include/get_content.h"
#include "../include/server_err.h"
#include <stdio.h>
#include <string.h>

void add_header(HTTP_HEADER*** headers, int* header_count, char* name, char* value) {
  (*header_count)++;
  *headers = realloc(*headers, sizeof(HTTP_HEADER*) * (*header_count));

  (*headers)[*header_count-1] = malloc(sizeof(HTTP_HEADER));

  (*headers)[*header_count-1]->name = strdup(name);
  (*headers)[*header_count-1]->name_len = strlen(name);
  (*headers)[*header_count-1]->value = strdup(value);
  (*headers)[*header_count-1]->value_len = strlen(value);
}

char* stringify_res(Response* response) {
  int i;
  
  size_t res_len = strlen(response->version) + strlen(response->status) + strlen(response->message) + 5;

  for (i = 0; i<response->header_count; i++) {
    res_len += response->headers[i]->name_len+2;
    res_len += response->headers[i]->value_len+2;
  }
  res_len += 2;
  res_len += strlen(response->body) + 2;

  char *string = malloc(res_len);

  snprintf(string, res_len, "%s %s %s\r\n", response->version, response->status, response->message);

  size_t current_pos = strlen(string);
  for (i = 0; i < response->header_count; i++) {
    snprintf(string + current_pos, res_len - current_pos, "%s: %s\r\n", response->headers[i]->name, response->headers[i]->value);
    current_pos = strlen(string);
  }

  snprintf(string + current_pos, res_len - current_pos, "\r\n%s\r\n", response->body);

  response->responseSize = res_len;
  return string;
}

Response build_res(char* version, char* status, char* message, HTTP_HEADER** headers, int* header_count, char* body) {
  Response response;
  response.version = strdup(version);
  response.status = strdup(status);
  response.message = strdup(message);
  response.headers = headers;
  response.header_count = *header_count;
  response.body = strdup(body);

  response.stringified = stringify_res(&response);
  return response;
}

Response handle_request(char* raw_req) {
  printf("Handling request:\n%s\n", raw_req);
  Request request = parse_request(raw_req);
  parse_headers(&request);
  
  return handle_get(request);
}

Response handle_get(Request request) {
  HTTP_HEADER** headers = malloc(sizeof(HTTP_HEADER*));
  int header_count = 0;

  char* body = get_content(request.path);

  char* status;
  char* message;

  if (body == NULL) {
    return not_found();
  } else {
    status = strdup("200");
    message = strdup("OK");
  }

  // Add standard headers
  char date_buf[32];
  time_t now = time(NULL);
  strftime(date_buf, sizeof(date_buf), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&now));
  add_header(&headers, &header_count, "Date", date_buf);
  add_header(&headers, &header_count, "Server", "C-Custom-Server/1.0");

  char content_length[32];
  snprintf(content_length, sizeof(content_length), "%zu", strlen(body));
  add_header(&headers, &header_count, "Content-Length", content_length);

  Response response = build_res(request.version, status, message, headers, &header_count, body);
  return response;
}
