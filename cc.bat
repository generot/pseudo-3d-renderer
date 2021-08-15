@echo off
gcc -g -o bin/pdr.exe src/*.c -I "%SDL2%\\include\\SDL2" -L "%SDL2%\\lib" -lmingw32 -lSDL2main -lSDL2