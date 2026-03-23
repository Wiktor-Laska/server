#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

// --- WSPÓŁDZIELONY STAN GRY ---
int stan_gry = 1;         // 1-Lobby, 2-Gra, 3-Koniec
int num_players = 0;
int runda_trwa = 0;
char runda_lvl = '1';
char punkty[4] = {0};
char kolory_tekst[9] = {0}; // Pierwsze 9 bajtów (np. jakie słowo)
char kolory_tusz[9] = {0};  // Drugie 9 bajtów (np. jakim kolorem pomalowane)

char cel_tekst = 0;         // Pierwszy pojedynczy bajt (cel do znalezienia)
char cel_tusz = 0;          // Drugi pojedynczy bajt (wskazówka)

char zdarzenia[4] = {0};

pthread_mutex_t muteks_gry = PTHREAD_MUTEX_INITIALIZER;

void *watek_sieciowy(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char naglowek[7];

    while(1) {
        memset(naglowek, 0, sizeof(naglowek));
        
        int r = recv(sock, naglowek, 6, MSG_PEEK); 
        
        if (r <= 0) {
            printf("\n[Sieć] Rozłączono z serwerem.\n");
            break; 
        }

        if (strncmp(naglowek, "START\n", 6) == 0) {
            recv(sock, naglowek, 6, 0); 
            
            char np;
            recv(sock, &np, 1, 0); 

            pthread_mutex_lock(&muteks_gry);
            num_players = np - '0';
            stan_gry = 2;
            runda_trwa = 0; // Gra się zaczęła, ale czekamy te 3 sekundy na pierwszą rundę
            pthread_mutex_unlock(&muteks_gry);
            
            printf("[Sieć] Gra wystartowała! Liczba graczy: %d\n", num_players);
        } 
        // start rundy
        else if (strncmp(naglowek, "RUNDA\n", 6) == 0) {
            recv(sock, naglowek, 6, 0);
            
            char t_lvl, t_punkty[4] = {0};
            char t_kolory_tekst[9], t_kolory_tusz[9];
            char t_cel_tekst, t_cel_tusz;
            char t_zdarzenia[4];

            recv(sock, &t_lvl, 1, 0);
            
            int obecni_gracze = 0;
            pthread_mutex_lock(&muteks_gry);
            obecni_gracze = num_players;
            pthread_mutex_unlock(&muteks_gry);

            if (obecni_gracze > 0) {
                recv(sock, t_punkty, obecni_gracze, 0); 
            }
            
            recv(sock, t_kolory_tekst, 9, 0);
            recv(sock, t_kolory_tusz, 9, 0);
            recv(sock, &t_cel_tekst, 1, 0);
            recv(sock, &t_cel_tusz, 1, 0);
            recv(sock, t_zdarzenia, 4, 0);

            pthread_mutex_lock(&muteks_gry);
            runda_lvl = t_lvl;
            for(int i=0; i < obecni_gracze; i++) punkty[i] = t_punkty[i];
            
            for(int i=0; i < 9; i++) {
                kolory_tekst[i] = t_kolory_tekst[i];
                kolory_tusz[i] = t_kolory_tusz[i];
            }
            
            cel_tekst = t_cel_tekst;
            cel_tusz = t_cel_tusz;

            for(int i=0; i < 4; i++) zdarzenia[i] = t_zdarzenia[i];
            
            runda_trwa = 1; 
            pthread_mutex_unlock(&muteks_gry);

            printf("[Sieć] Odebrano nową rundę (Poziom: %c, Cel: %c/%c)\n", t_lvl, t_cel_tekst, t_cel_tusz);
            for(int i=0; i < obecni_gracze; i++) {
                printf("  Gracz %d: %d punktów\n", i+1, t_punkty[i]);
            }   
        }
        // ==========================================
        // ŁAPANIE KOŃCA RUNDY (KRUNDA)
        // ==========================================
        else if (strncmp(naglowek, "KRUNDA", 6) == 0) {
            recv(sock, naglowek, 6, 0); // Wciągamy 6 znaków KRUNDA z gniazda
            
            pthread_mutex_lock(&muteks_gry);
            runda_trwa = 0; // <--- DODANO: Koniec rundy. OpenGL ma wyczyścić planszę na 1 sekundę!
            pthread_mutex_unlock(&muteks_gry);
            
            printf("[Sieć] Koniec rundy! Przygotuj sie...\n");
        }
        // ==========================================
        // zakończenie gierki
        // ==========================================
        // zakończenie gierki
        else if (strncmp(naglowek, "KONIEC", 6) == 0) {
            recv(sock, naglowek, 6, 0); // Wciągamy "KONIEC"
            char znak_nowej_linii;
            recv(sock, &znak_nowej_linii, 1, 0);
            
            int obecni_gracze = 0;
            pthread_mutex_lock(&muteks_gry);
            obecni_gracze = num_players;
            pthread_mutex_unlock(&muteks_gry);

            char finalne_punkty[4] = {0};
            if (obecni_gracze > 0) {
                recv(sock, finalne_punkty, obecni_gracze, 0);
            }
            
            pthread_mutex_lock(&muteks_gry);
            stan_gry = 3; 
            runda_trwa = 0;
            for(int i = 0; i < obecni_gracze; i++) {
                punkty[i] = finalne_punkty[i];
            }
            pthread_mutex_unlock(&muteks_gry);
            printf("\n=== [Sieć] KONIEC GRY! ===\nWyniki koncowe:\n");
            for(int i = 0; i < obecni_gracze; i++) {
                printf("Gracz %d: %d pkt\n", i + 1, finalne_punkty[i]);
            }
        }
        else {
            //tutaj przeczytanie zwykłego tekstu, który może być np. wynikiem rundy, informacją o punktach itp.
            //TODO: CHAT np funkcja WYPISZ_NA_CZACIE
            char zwykly_tekst[256];
            memset(zwykly_tekst, 0, sizeof(zwykly_tekst));
            int przeczytane = recv(sock, zwykly_tekst, 255, 0);
            
            if (przeczytane > 0) {
                printf("%s", zwykly_tekst);
                fflush(stdout);
            }
        }
    }
    return NULL;
}

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[256];
    pthread_t thread_id;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Błąd połączenia. Czy serwer jest włączony?\n");
        return 1;
    }

    // Uruchamiamy wątek w tle, który nasłuchuje serwera
    pthread_create(&thread_id, NULL, watek_sieciowy, (void*)&sock);
    
    // Główna pętla programu PISZE do serwera
    while(1) {
        memset(buffer, 0, 256);
        fgets(buffer, 256, stdin); 
        if (strcmp(buffer, "-1\n") == 0) {
            break;
        }
        
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    return 0;
}