// Copyright re-up.ph

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "/opt/homebrew/Cellar/cjson/1.7.18/include/cjson/cJSON.h"
#include <stdio.h>

void parse_json_stream(const char *json_line);

#endif
