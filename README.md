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

ODPALENIE SERWERA:
CMD - ipconfig wybieramy ipv4 z której rzeczy chcemy się połączyć(WINDOWS ip)
terminal vs code - hostname -I(WSL ip)
                 - netsh interface portproxy add v4tov4 listenport=5000 listenaddress=0.0.0.0 connectport=5000 connectaddress= WSL ip
                                                                                                                               ======
powershell     New-NetFirewallRule -DisplayName "Gra C Port 5000" -Direction Inbound -LocalPort 5000 -Protocol TCP -Action Allow
                            
Klient z lokalnego wifi potrzebuje adres WINDOWS ip do portu 5000