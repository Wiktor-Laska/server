#define _GNU_SOURCE
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
#define SLEEP_TIME 0
#define RANDOM_EVENTS 4
void tasuj_tablice(char *tablica, int rozmiar)
{
    for (int i = rozmiar - 1; i > 0; i--)
    {
        char j = rand() % (i + 1);
        char temp = tablica[i];
        tablica[i] = tablica[j];
        tablica[j] = temp;
    }
}
// struktura całego servera
typedef struct
{
    int seed;
    int listenfd, connfd;
    struct sockaddr_in serv_addr;
    struct pollfd fds[MAX_PLAYERS + 1];
    char points[MAX_PLAYERS];
    int ready[MAX_PLAYERS];
    int num_players;
    char colors[COLOR_NUMBER];
    char random_event[RANDOM_EVENTS];
} Server;
void send_all(Server *serv, char *msg, int l)
{
    msg[l]='\0';
    for (int j = 1; j <= serv->num_players; j++)
        if (serv->fds[j].fd != -1){
            send(serv->fds[j].fd, msg, l, MSG_NOSIGNAL);
        }
}
// inicjalizacja serwera
void init(Server *ms)
{
    memset(ms, 0, sizeof(Server));
    ms->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(ms->listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    ms->serv_addr.sin_family = AF_INET;
    ms->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ms->serv_addr.sin_port = htons(5000);
    for (int i = 0; i < COLOR_NUMBER; i++)
    {
        ms->colors[i] = i + '0';
    }
    ms->seed = time(NULL);
    srand(ms->seed);
    bind(ms->listenfd, (struct sockaddr *)&ms->serv_addr, sizeof(ms->serv_addr));
    listen(ms->listenfd, 10);
    ms->fds[0].fd = ms->listenfd;
    ms->fds[0].events = POLLIN;
}
// działanie lobby
void lobby(Server *serv)
{
    for (;;)
    {
        poll(serv->fds, serv->num_players + 1, -1);

        // przyjmowanie zgłoszeni(fds[0] nasza poczekalnia dla nowych graczy którzy są później przypisywani od 1 do maks 4)
        if ((serv->fds[0].revents & POLLIN) && serv->num_players < MAX_PLAYERS)
        {
            int new_sock = accept(serv->listenfd, NULL, NULL);

            serv->num_players++;
            serv->fds[serv->num_players].fd = new_sock;
            serv->fds[serv->num_players].events = POLLIN;
            serv->points[serv->num_players - 1] = 0;
            serv->ready[serv->num_players - 1] = 0;

            char msg[256];
            sprintf(msg, "=== LOBBY ===\nDolaczyles jako Gracz %d.\nWpisz 'READY', gdy bedziesz gotowy do gry!\n", serv->num_players);
            send(new_sock, msg, strlen(msg), 0);

            printf("Gracz %d dolaczyl do Lobby.\n", serv->num_players);
        }

        // sprawdzanie gotowości graczy
        for (int i = 1; i <= serv->num_players; i++)
        {
            if (serv->fds[i].revents & POLLIN)
            {
                char buf[256] = {0};
                int r = recv(serv->fds[i].fd, buf, 255, 0);
                if (r > 0)
                {
                    if (strncmp(buf, "READY", 5) == 0 && serv->ready[i - 1] == 0)
                    { // sprawdzenie wysłanej wiadomości czy jest równa "1"
                        serv->ready[i - 1] = 1;
                        char msg[100];
                        sprintf(msg, "-> Gracz %d kliknal READY!\n", i);
                        printf("%s", msg);
                        send_all(serv, msg, strlen(msg));
                    }
                }
                else
                {
                    printf("Gracz %d sie rozlaczyl.\n", i);
                    close(serv->fds[i].fd); // Zamknięcie gniazda w systemie
                    serv->fds[i].fd = -1;
                    for (int k = i; k < serv->num_players; k++)
                    {
                        serv->fds[k] = serv->fds[k + 1];
                        serv->points[k - 1] = serv->points[k];
                        serv->ready[k - 1] = serv->ready[k];
                    }
                    serv->fds[serv->num_players].fd = -1;
                    serv->fds[serv->num_players].events = 0;
                    serv->points[serv->num_players - 1] = 0;
                    serv->ready[serv->num_players - 1] = 0;
                    serv->num_players--;
                    i--;
                    char msg[100];
                    sprintf(msg, "Ktos wyszedl. Obecna liczba graczy: %d\n", serv->num_players);
                    send_all(serv, msg, strlen(msg));
                }
            }
        }
        // uruchomienie gry
        if (serv->num_players >= 2)
        {
            int all_ready = 1;
            for (int i = 0; i < serv->num_players; i++)
            {
                if (!serv->ready[i])
                    all_ready = 0;
            }
            if (all_ready)
            {
                printf("Wszyscy gotowi\n");
                serv->fds[0].events = 0;
                return;
            }
        }
    }
}
// NAPRAWIONY BŁĄD: zmienione <= na <, żeby nie kopiować śmieci z pamięci!
void charcopy(char *buff,char *tc,int p,int l){
    for(int i=p; i < p+l; i++){
        buff[i]=tc[i-p];
    }
}

void game(Server *serv)
{
    printf("START\n");
    char msg[255];
    sprintf(msg, "START\n");
    send_all(serv, msg, strlen(msg)); // każdy gracz dostake wiadomość START
    char np = serv->num_players+'0';  // Zapisujemy liczbę jako 1 bajt
    send_all(serv, &np, 1);
    
    printf("Czekam 3 sekundy przed pierwsza runda...\n");
    sleep(3); // <--- DODANO: 3 sekundy przerwy przed startem zabawy

    for (char lvl = '1'; lvl <= '4'; lvl++)
    { // rundy
        for (int i = 0; i < 5; i++)
        {
            int z=0;
            sprintf(msg, "RUNDA\n");
            sleep(SLEEP_TIME);
            send_all(serv, msg, strlen(msg));
            
            // czyszczenie bufforów
            for (int k = 1; k <= serv->num_players; k++)
            {
                if (serv->fds[k].fd != -1) 
                {
                    char trash[256];
                    while (recv(serv->fds[k].fd, trash, 255, MSG_DONTWAIT) > 0)
                    {
                        // Nic tu nie robimy, po prostu "wyciągamy" stare dane w kosz
                    }
                }
            }
            
            // pakowanie danych (poziom, punkty)
            charcopy(msg, &lvl, z, 1);
            z+=1; 
            charcopy(msg, serv->points, z, serv->num_players);
            z+=serv->num_players; 
            
            // Pierwsze tasowanie (Tekst)
            tasuj_tablice(serv->colors, COLOR_NUMBER);
            charcopy(msg, serv->colors, z, COLOR_NUMBER);
            z+=COLOR_NUMBER; 

            // Drugie tasowanie (Kolor tuszu)
            tasuj_tablice(serv->colors, COLOR_NUMBER);
            charcopy(msg, serv->colors, z, COLOR_NUMBER);
            z+=COLOR_NUMBER; 
            
            char odp;
            if (lvl == '1') tasuj_tablice(serv->colors, 3); 
            if (lvl == '2') tasuj_tablice(serv->colors, 5); 
            if (lvl >= '3') tasuj_tablice(serv->colors, 9);
            charcopy(msg, serv->colors, z, 1);
            z+=1; 

            odp = serv->colors[0]; // To jest nasza poprawna odpowiedź
            
            tasuj_tablice(serv->colors, COLOR_NUMBER);
            charcopy(msg, serv->colors, z, 1);
            z+=1; 

            // Zdarzenia losowe
            for(int x=0; x<RANDOM_EVENTS; x++){
                if(rand()%(20/(lvl-'0'))) serv->random_event[x]=0;
                else serv->random_event[x]=(lvl-'0');
            }
            charcopy(msg, serv->random_event, z, RANDOM_EVENTS);
            z+=RANDOM_EVENTS; 
            
            send_all(serv, msg, z);
            
            // Upewniamy się, że wszystko wysłane
            poll(serv->fds, serv->num_players+1, 0);

            //===================================================================
            // NOWY SYSTEM ODCZYTU (Zegar + Odporność na rozłączenie)
            //===================================================================
            printf("ODP (lvl %c):\n", lvl);
            
            int total_time = 10000 - (lvl-'1')*1500;
            int time_left = total_time;
            int round_resolved = 0; // Flaga: 1 jeśli ktoś już zgadł

            // Mierzymy czas z dokładnością do milisekund
            struct timespec start_time, current_time;
            clock_gettime(CLOCK_MONOTONIC, &start_time);

            // Pętla kręci się dopóki mamy czas i nikt nie udzielił odpowiedzi
            while (time_left > 0 && !round_resolved) 
            {
                int poll_result = poll(serv->fds, serv->num_players + 1, time_left);
                
                if (poll_result == 0)
                {
                    // Czas minął, nikt nie odpowiedział
                    for (int x = 0; x < serv->num_players; x++) {
                        if (serv->fds[x+1].fd != -1) { // Minusy tylko dla tych, co grają
                            serv->points[x] -= 1;
                        }
                    }
                    break; // Koniec pętli while, przechodzimy do sygnału KRUNDA
                }

                for (int j = 1; j <= serv->num_players; j++)
                {
                    if (serv->fds[j].fd != -1 && (serv->fds[j].revents & POLLIN))
                    {
                        char odp_c[256];
                        int r = recv(serv->fds[j].fd, odp_c, 255, 0);
                        if (r > 0)
                        {
                            if (odp_c[0] == odp) {
                                serv->points[j - 1] += (lvl-'0');
                            } else {
                                serv->points[j - 1] -= 2;
                            }
                            round_resolved = 1; // Ktoś odpowiedział!
                            break; // Przerywamy sprawdzanie innych graczy
                        }
                        else
                        {
                            printf("Gracz %d sie rozlaczyl.\n", j);
                            close(serv->fds[j].fd);
                            serv->fds[j].fd = -1;
                            // NAPRAWIONE: Gracz się rozłączył, ale nie przerywamy rundy!
                        }
                    }
                }

                // Odliczamy czas, który upłynął
                clock_gettime(CLOCK_MONOTONIC, &current_time);
                long elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
                                  (current_time.tv_nsec - start_time.tv_nsec) / 1000000;
                time_left = total_time - elapsed_ms;
            }

            // --- KONIEC RUNDY ---
            sprintf(msg, "KRUNDA"); // Równo 6 znaków dla klienta (Koniec Rundy)
            send_all(serv, msg, 6); // Wysyłamy sygnał końca
            
            sleep(1); // <--- DODANO: 1 sekunda przerwy przed kolejną rundą
        }
    }
}
void end_game(Server *serv)
{
    char msg[255];
    sprintf(msg, "KONIEC\n");
    send_all(serv, msg, strlen(msg));
    send_all(serv, serv->points, serv->num_players);
    for(int i=1;i<=serv->num_players;i++){
        if(serv->fds[i].fd!=-1){
            close(serv->fds[i].fd);
            serv->fds[i].fd = -1;
        }
    }
    if (serv->listenfd != -1) {
        close(serv->listenfd);
        serv->listenfd = -1;
    }
    serv->num_players = 0;
    printf("Serwer został pomyślnie zamknięty.\n");
}
int main()
{
    Server main_server;
    while(1){
        init(&main_server);
        printf("Serwer uruchomiony. Czekam na graczy na porcie 5000...\n");
        lobby(&main_server);
        printf("zaczynanie gry..\n");
        game(&main_server);
        printf("koniec gry..\n");
        end_game(&main_server);
    }

    return 0;
}