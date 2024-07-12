// Copyright re-up.ph

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "/opt/homebrew/Cellar/jansson/2.14/include/jansson.h"
#include <curl/curl.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

size_t WriteMem(void *contents, size_t size, size_t nmemb, void *userp);

#endif
