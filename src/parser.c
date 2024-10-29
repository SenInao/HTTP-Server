#include <string.h>
#include "../include/Server.h"

HTTP_REQUEST parse_request(char* request) {
  HTTP_REQUEST http_req;
  http_req.request = request;
  int i = 0;

  while (i < sizeof(http_req.method)-1) {
    if (request[i] == ' ') {
      break;
    }
    http_req.method[i] = request[i];
    i++;
  }

  i++;
  http_req.method[i] = '\0';
  int j = 0;
  
  while (i < sizeof(http_req.path)-1) {
    if (request[i] == ' ') {
      break;
    }
    http_req.path[j] = request[i];
    i++;
    j++;
  }

  j++;
  i++;
  http_req.path[j] = '\0';
  j = 0;
  
  while (i < sizeof(http_req.version)-1) {
    if (request[i] == ' ') {
      break;
    }
    http_req.version[j] = request[i];
    i++;
    j++;
  }

  j++;
  http_req.version[j] = '\0';

  return http_req;
}

void parse_headers(HTTP_REQUEST* http_req) {
  const char *headers = strstr(http_req->request, "\r\n") + 2;

  while (*headers != '\r' && *(headers+1) != '\n') {
    char header_name[512], header_value[512];
    sscanf(headers, "%[^:]: %[^\r\n]", header_name, header_value);
    headers = strstr(headers, "\r\n") + 2;

    if (strcasecmp(header_name, "Host") == 0) {
      strncpy(http_req->host, header_value, sizeof(http_req->host) - 1);
    } else if (strcasecmp(header_name, "User-Agent") == 0) {
      strncpy(http_req->user_agent, header_value, sizeof(http_req->user_agent) - 1);
    } else if (strcasecmp(header_name, "Accept") == 0) {
      strncpy(http_req->accept, header_value, sizeof(http_req->accept) - 1);
    } else if (strcasecmp(header_name, "Accept-Encoding") == 0) {
      strncpy(http_req->accept_encoding, header_value, sizeof(http_req->accept_encoding) - 1);
    } else if (strcasecmp(header_name, "Accept-Language") == 0) {
      strncpy(http_req->accept_language, header_value, sizeof(http_req->accept_language) - 1);
    } else if (strcasecmp(header_name, "Content-Type") == 0) {
      strncpy(http_req->content_type, header_value, sizeof(http_req->content_type) - 1);
    } else if (strcasecmp(header_name, "Content-Length") == 0) {
      strncpy(http_req->content_length, header_value, sizeof(http_req->content_length) - 1);
    } else if (strcasecmp(header_name, "Connection") == 0) {
      strncpy(http_req->connection, header_value, sizeof(http_req->connection) - 1);
    } else if (strcasecmp(header_name, "Cache-Control") == 0) {
      strncpy(http_req->cache_control, header_value, sizeof(http_req->cache_control) - 1);
    } else if (strcasecmp(header_name, "Authorization") == 0) {
      strncpy(http_req->authorization, header_value, sizeof(http_req->authorization) - 1);
    } else if (strcasecmp(header_name, "Cookie") == 0) {
      strncpy(http_req->cookie, header_value, sizeof(http_req->cookie) - 1);
    } else if (strcasecmp(header_name, "Sec-WebSocket-Key") == 0) {
      strncpy(http_req->sec_websocket_key, header_value, sizeof(http_req->sec_websocket_key) - 1);
    } else if (strcasecmp(header_name, "Sec-WebSocket-Version") == 0) {
      strncpy(http_req->sec_websocket_version, header_value, sizeof(http_req->sec_websocket_version) - 1);
    } else if (strcasecmp(header_name, "Sec-WebSocket-Protocol") == 0) {
      strncpy(http_req->sec_websocket_protocol, header_value, sizeof(http_req->sec_websocket_protocol) - 1);
    } else if (strcasecmp(header_name, "Referer") == 0) {
      strncpy(http_req->referer, header_value, sizeof(http_req->referer) - 1);
    } else if (strcasecmp(header_name, "Origin") == 0) {
      strncpy(http_req->origin, header_value, sizeof(http_req->origin) - 1);
    }

  }
}
