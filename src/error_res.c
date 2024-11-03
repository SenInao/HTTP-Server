#include <string.h>
#include "../include/request_handler.h"

Response server_err() {
  Response res;
  res.status = strdup("500");
  res.version = strdup("HTTP/1.1");
  res.message = strdup("Internal Server Error");
  res.body = strdup("<html><head><title>Server error</title><meta charset='utf-8'/></head><body><h1>Internal Server Error</h1></body></html>");
  res.header_count = 0;
  res.stringified = stringify_res(&res);
  return res;
}

Response not_found() {
  Response res;
  res.status = strdup("404");
  res.version = strdup("HTTP/1.1");
  res.message = strdup("Not Found");
  res.body = strdup("<html><head><title>Server error</title><meta charset='utf-8'/></head><body><h1>Not Found</h1></body></html>");
  res.header_count = 0;
  res.stringified = stringify_res(&res);
  return res;
}
