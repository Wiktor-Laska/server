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
    for (int j = 1; j <= serv->num_players; j++)
        if (serv->fds[j].fd != -1)
            send(serv->fds[j].fd, msg, l, MSG_NOSIGNAL);
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
void game(Server *serv)
{
    char msg[255];

    sprintf(msg, "START\n");
    send_all(serv, msg, strlen(msg)); // każdy gracz dostake wiadomość START

    for (char lvl = '1'; lvl <= '4'; lvl++)
    { // rundy
        for (int i = 0; i < 5; i++)
        {
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

            send_all(serv, &lvl, 1);                         // wysyłanie lvl
            send_all(serv, serv->points, serv->num_players); // wysyłanie punktów

            //[0,1,2,3,4,5,6,7,8]
            tasuj_tablice(serv->colors, COLOR_NUMBER);
            send_all(serv, serv->colors, COLOR_NUMBER); // prześlij numer kolor napisów
            //[5,3,1,2,4,7,6,8,0]

            tasuj_tablice(serv->colors, COLOR_NUMBER);
            send_all(serv, serv->colors, COLOR_NUMBER); // prześlij numer nazwy tekstu kolorów
            //[8,2,4,7,1,3,5,6,0] musimy potasować tylko te
            char odp;
            if (lvl == '1')
                tasuj_tablice(serv->colors, 3); 
            if (lvl == '2')
                tasuj_tablice(serv->colors, 5); 
            if (lvl >= '3')
                tasuj_tablice(serv->colors, 9);
            send_all(serv, serv->colors, 1); // prześlij numer koloru napisu
            odp = serv->colors[0];
            tasuj_tablice(serv->colors, COLOR_NUMBER);
            send_all(serv, serv->colors, 1); // prześlij numer tekstu koloru

            // TODO wysłanie zdarzeń losowych wysłanie zdarzeń np 4 chary 0-nie ma zdarzenia 1<= zdarzenie o mocy podanej
            for(int x=0;x<RANDOM_EVENTS;x++){
                if(rand()%(20/(lvl-'0')))
                    serv->random_event[x]=0;
                else
                    serv->random_event[x]=(lvl-'0');
            }
            send_all(serv,serv->random_event,RANDOM_EVENTS);
            //==========================================================================================================

            // sprawdzanie odpowiedzi
            // oczekiwanie poll
            int poll_result = poll(serv->fds, serv->num_players + 1, 10000-(lvl-'1')*1500); // 5 sekund na odpowiedź - 1,5 na każdy następny lvl

            // 1. gracz przysłał poprawną odpowiedź +1-4
            // 2. gracz przysłał błędną odpowiedź -2
            // 3. żaden gracz nie przysłał odpowiedzi -1 dla wszystkich
            if (poll_result == 0)
            {
                // Czas minął, nikt nie odpowiedział
                for (int x = 0; x < serv->num_players; x++)
                {
                    serv->points[x] -= 1;
                }
                sprintf(msg, "WYNIK\nnikt nie odpowiedział, wszyscy -1\n");
                send_all(serv, msg, strlen(msg));
                continue; // Przejdź do następnej rundy
            }

            for (int j = 1; j <= serv->num_players; j++)
            {
                if (serv->fds[j].revents & POLLIN)
                {
                    char odp_c[256];
                    int r = recv(serv->fds[j].fd, odp_c, 255, 0);
                    if (r > 0)
                    {
                        sprintf(msg, "WYNIK\n");
                        send_all(serv, msg, strlen(msg));
                        if (odp_c[0] == odp)
                        {
                            serv->points[j - 1] += (lvl-'0');

                            sprintf(msg, "Gracz %d odpowiedział dobrze +%d\n", j, lvl - '0');
                            send_all(serv, msg, strlen(msg));
                        }
                        else
                        {
                            serv->points[j - 1] -= 2;

                            sprintf(msg, "Gracz %d odpowiedział źle -2\n", j);
                            send_all(serv, msg, strlen(msg));
                        }

                        break;
                    }
                    else
                    {
                        printf("Gracz %d sie rozlaczyl.\n", j);
                        close(serv->fds[j].fd); // Zamknięcie gniazda w systemie
                        serv->fds[j].fd = -1;
                    }
                }
            }
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
            strcpy(msg, "Serwer zostal zamkniety. Do zobaczenia!\n");
            send(serv->fds[i].fd, msg, strlen(msg), MSG_NOSIGNAL);
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