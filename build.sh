rm -rf "builds/radar-punk" && cc src/*.c -g -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o "builds/radar-punk"
