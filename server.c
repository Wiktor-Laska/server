#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// Funkcja obsługująca pojedynczego klienta
void *connection_handler(void *socket_desc) {
    // Odczytujemy numer gniazda i OD RAZU zwalniamy zaalokowaną pamięć
    int sock = *(int*)socket_desc;
    int id=htonl(sock);
    free(socket_desc); 
    
    char buffer[256];
    int read_size;
    send(sock, (void*)&id, sizeof(id), 0);
    // Nieskończona pętla - odbieramy dane aż do przerwania
    while(1) {
        // Czyścimy bufor PRZED każdym nowym odczytem
        memset(buffer, 0, 256);
        
        // Blokujemy działanie wątku i czekamy na wiadomość od klienta
        read_size = recv(sock, buffer, 255, 0);
        
        // Sprawdzamy, czy odczyt się powiódł
        if(read_size <= 0) {
            printf("Serwer: Klient %d się rozłączył bez pożegnania lub wystąpił błąd.\n", sock);
            break; // Wychodzimy z pętli
        }
        
        // Sprawdzamy, czy klient przysłał komendę wyjścia "-1\n"
        if(strcmp(buffer, "-1\n") == 0) {
            printf("Serwer: Klient zakończył nadawanie (-1).\n");
            break; // Wychodzimy z pętli
        }
        
        // Jeśli to żadna z powyższych sytuacji, po prostu wypisujemy liczbę
        printf("Serwer: Otrzymałem od klienta %d liczbę: %s", sock,buffer);
    }
    
    // Kod po wyjściu z pętli while(1)
    printf("Serwer: CLOSE. Zamykam gniazdo dla tego klienta %d.\n", sock);
    
    close(sock);
    pthread_exit(NULL);
}
int main() {
    int listenfd, connfd;
    struct sockaddr_in serv_addr; 
    pthread_t thread_id;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
    
    printf("Serwer uruchomiony. Czekam na liczby na porcie 5000...\n");

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        
        // POPRAWKA: Tworzymy nową pamięć dla każdego połączenia (eliminuje race condition)
        int *new_sock = malloc(sizeof(int));
        *new_sock = connfd;
        
        pthread_create(&thread_id, NULL, connection_handler, (void*) new_sock);
        // Odłączamy wątek, żeby system sam posprzątał po nim zasoby
        pthread_detach(thread_id); 
    }
    return 0;
}