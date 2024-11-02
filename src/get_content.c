#include "../include/get_content.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* get_content(char* path) {
  char* ending = "";
  if (path[strlen(path)-1] == '/') {
    ending = strdup("index.html");
  }

  char* default_path = malloc(strlen(path)+strlen(ending)+9);
  snprintf(default_path, strlen(path)+strlen(ending)+9, "%s%s%s", "./public", path, ending);

  char* content = 0;
  long length;

  FILE *fp = fopen(default_path, "r");

  if (fp == NULL) {
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  length = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  content = malloc(length);
  if (content) {
    fread(content, 1, length, fp);
  }
  fclose(fp);

  return content;
}
