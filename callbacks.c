// Copyright re-up.ph

#include "./callbacks.h"
#include "./json_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t WriteMem(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (ptr == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  char *line_start = mem->memory;
  char *line_end;
  while ((line_end = strchr(line_start, '\n')) != NULL) {
    *line_end = '\0';
    parse_json_stream(line_start);
    line_start = line_end + 1;
  }

  if (line_start < mem->memory + mem->size) {
    size_t remaining = mem->size - (line_start - mem->memory);
    memmove(mem->memory, line_start, remaining);
    mem->size = remaining;
  } else {
    mem->size = 0;
  }

  return realsize;
}
