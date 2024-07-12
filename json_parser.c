// Copyright re-up.ph

#include "./json_parser.h"
#include <stdlib.h>
#include <string.h>

void parse_json_stream(const char *json_line) {
  printf("\n");
  cJSON *json = cJSON_Parse(json_line);
  if (json == NULL) {
    fprintf(stderr, "JSON parsing error for line: %s\n", json_line);
    return;
  }

  cJSON *response = cJSON_GetObjectItemCaseSensitive(json, "response");
  cJSON *done = cJSON_GetObjectItemCaseSensitive(json, "done");

  if (cJSON_IsString(response) && (response->valuestring != NULL)) {
    printf("%s", response->valuestring);
    fflush(stdout);
  }

  if (cJSON_IsBool(done) && done->valueint) {
    printf("\n\nDone.\n");
    fflush(stdout);
  }

  cJSON_Delete(json);
}
