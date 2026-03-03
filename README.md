#aktualizacja oprogramowania:
sudo apt update && sudo apt install gdb -y 

#kompilacja
gcc server.c -o server -pthread
gcc -g client.c -o client -pthread

#odpalanie
./server
następnie w innych terminalach
./client



instalacja opengl:

sudo apt install mesa-utils libgl1

sudo apt install libgl-dev

sudo apt install libglu1-mesa-dev

sudo apt install libglfw3-dev

sudo apt install libxxf86vm-dev

kompilacja gry:

g++ Linux_OpenGL.cpp -o program -lGL -lGLU -lX11 -lXxf86vm