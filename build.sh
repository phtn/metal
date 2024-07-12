# For Arm64 arch 
clang -o metal \
  main.c json_parser.c callbacks.c \
  -I/opt/homebrew/opt/curl/include \
  -L/opt/homebrew/opt/curl/lib -lcurl \
  -I/opt/homebrew/Cellar/cjson/1.7.18/include \
  -L/opt/homebrew/Cellar/cjson/1.7.18/lib -lcjson \
  -I/opt/homebrew/Cellar/jansson/2.14/include \
  -L/opt/homebrew/Cellar/jansson/2.14/lib -ljansson
