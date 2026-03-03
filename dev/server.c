#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <poll.h> 

#define MAX_PLAYERS 4
#define COLOR_NUMBER 9
void tasuj_tablice(char *tablica, int rozmiar) {
    for (int i = rozmiar - 1; i > 0; i--) {
        char j = rand() % (i + 1);
        char temp = tablica[i];
        tablica[i] = tablica[j];
        tablica[j] = temp;
    }
}
// struktura całego servera
typedef struct {
    int seed;
    int listenfd, connfd;
    struct sockaddr_in serv_addr; 
    struct pollfd fds[MAX_PLAYERS + 1];
    char points[MAX_PLAYERS]; 
    int ready[MAX_PLAYERS];
    int num_players;
    char colors[COLOR_NUMBER];
} Server;
void send_all(Server *serv,char *msg,int l){
    for (int j = 1; j <= serv->num_players; j++) send(serv->fds[j].fd, msg, l, 0);
}
// inicjalizacja serwera
void init(Server* ms) {
    memset(ms, 0, sizeof(Server));
    ms->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ms->serv_addr.sin_family = AF_INET;
    ms->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ms->serv_addr.sin_port = htons(5000); 
    for(int i=0;i<COLOR_NUMBER;i++){
        ms->colors[i]=i+'0';
    }
    ms->seed=time(NULL);
    srand(ms->seed);
    bind(ms->listenfd, (struct sockaddr*)&ms->serv_addr, sizeof(ms->serv_addr)); 
    listen(ms->listenfd, 10); 
    ms->fds[0].fd = ms->listenfd;
    ms->fds[0].events = POLLIN;
}
// działanie lobby
void lobby(Server* serv) {
    for(;;) {
        poll(serv->fds, serv->num_players + 1, -1);
        
        // przyjmowanie zgłoszeni(fds[0] nasza poczekalnia dla nowych graczy którzy są później przypisywani od 1 do maks 4)
        if((serv->fds[0].revents & POLLIN) && serv->num_players < MAX_PLAYERS) {
            int new_sock = accept(serv->listenfd, NULL, NULL);
            
            serv->num_players++;
            serv->fds[serv->num_players].fd = new_sock;
            serv->fds[serv->num_players].events = POLLIN;
            serv->points[serv->num_players - 1] = 0;
            serv->ready[serv->num_players - 1] = 0;
            
            char msg[256];
            sprintf(msg, "=== LOBBY ===\nDolaczyles jako Gracz %d.\nWpisz '1', gdy bedziesz gotowy do gry!\n", serv->num_players);
            send(new_sock, msg, strlen(msg), 0);
            
            printf("Gracz %d dolaczyl do Lobby.\n", serv->num_players);
        }

        //sprawdzanie gotowości graczy
        for(int i=1;i<=serv->num_players;i++){
            if (serv->fds[i].revents & POLLIN) {
                char buf[256] = {0};
                int r = recv(serv->fds[i].fd, buf, 255, 0);
                if (r > 0) {
                    if (strncmp(buf, "1",1) == 0 &&serv->ready[i - 1] == 0) {//sprawdzenie wysłanej wiadomości czy jest równa "1"
                        serv->ready[i - 1] = 1; 
                        char msg[100];
                        sprintf(msg, "-> Gracz %d kliknal READY!\n", i);
                        printf("%s", msg);
                        send_all(serv,msg,strlen(msg));
                    }
                }
            }
        }
        //uruchomienie gry
        if (serv->num_players>=2){
            int all_ready=1;
            for(int i=0;i<serv->num_players;i++){
                if(!serv->ready[i])
                    all_ready=0;
            }
            if(all_ready){
                printf("Wszyscy gotowi\n");
                return ;
            }
        }

    }
}
void game(Server* serv){
    char msg[255];
    sprintf(msg, "START\n");
    send_all(serv,msg,strlen(msg));//każdy gracz dostake wiadomość START
    char lvl='1';
    for(int i=0;i<10;i++){//rundy
        send_all(serv,&lvl,1);//wysyłanie lvl
        send_all(serv,serv->points,serv->num_players);//wysyłanie punktów

        //[0,1,2,3,4,5,6,7,8]
        tasuj_tablice(serv->colors,COLOR_NUMBER);
        send_all(serv,serv->colors,COLOR_NUMBER);//prześlij numer kolor napisów
        //[5,3,1,2,4,7,6,8,0]
        
        tasuj_tablice(serv->colors,COLOR_NUMBER);
        send_all(serv,serv->colors,COLOR_NUMBER);//prześlij numer nazwy tekstu kolorów
        //[8,2,4,7,1,3,5,6,0] musimy potasować tylko te
        tasuj_tablice(serv->colors,3);//TODO ogarnięcie ile COLOR_NUMBER różne poziomy różna ilość kolorów do wypisania na przyciski
        send_all(serv,serv->colors,1);//prześlij numer koloru napisu

        tasuj_tablice(serv->colors,COLOR_NUMBER);
        send_all(serv,serv->colors,1);//prześlij numer tekstu koloru
        //oczekiwanie poll 
        //sprawdzanie odpowiedzi 
        //1. gracz przysłał poprawną odpowiedź +2
        //2. gracz przysłał błędną odpowiedź -2
        //3. żaden gracz nie przysłał odpowiedzi -1 dla wszystkich
    }
}
int main() {
    Server main_server;
    init(&main_server);
    printf("Serwer uruchomiony. Czekam na graczy na porcie 5000...\n");
    lobby(&main_server);
    printf("zaczynanie gry..\n");
    game(&main_server);
    return 0;
}