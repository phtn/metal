// Copyright re-up.ph

#include "./callbacks.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  CURL *curl;
  CURLcode response;

  struct MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;

  // Parse args
  char prompt[4096] = {0};
  for (int i = 1; i < argc; i++) {
    if (i > 1)
      strcat(prompt, " ");
    strcat(prompt, argv[i]);
  }

  json_t *json =
      json_pack("{s:s, s:s}", "model", "codellama", "prompt", prompt);

  if (!json) {
    fprintf(stderr, "Failed to parse.\n");
    return 1;
  }

  char *post_fields = json_dumps(json, JSON_COMPACT);
  if (!post_fields) {
    fprintf(stderr, "Hi there!\n");
    json_decref(json);
    return 1;
  }

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");

  const char *url = "http://localhost:11434/api/generate";
  // const char *data = "{\"model\":\"codellama\",\"prompt\":\"Who are you?\"}";

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMem);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

    response = curl_easy_perform(curl);

    if (response != CURLE_OK) {
      fprintf(stderr, "perform() err: %s\n", curl_easy_strerror(response));
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    free(chunk.memory);
    json_decref(json);
    free(post_fields);
  }

  curl_global_cleanup();

  return 0;
}
