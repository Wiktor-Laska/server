#aktualizacja oprogramowania:
sudo apt update && sudo apt install gdb -y 

#kompilacja
gcc server.c -o server -pthread
gcc -g client.c -o client

#odpalanie
./server
następnie w innych terminalach
./client
