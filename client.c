#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, moje_id, siec_id;
    struct sockaddr_in serv_addr;
    char buffer[256];


    // Tworzenie gniazda
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    
    // Konwersja adresu IP z tekstu na format binarny
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Łączenie z serwerem
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Błąd połączenia. Czy serwer jest włączony?\n");
        return 1;
    }

    int read_size=recv(sock,(void*)&siec_id,sizeof(siec_id),0);
    moje_id=ntohl(siec_id);
    printf("Brawo połączyłeś się z klientem o numerze %d\n", moje_id);
    for(;;) {
        // Czyszczenie bufora przed odczytem (dobra praktyka w pętlach)
        memset(buffer, 0, 256);

        // Pobranie liczby od użytkownika
        printf("Podaj liczbę do wysłania (lub -1 aby wyjść): ");
        fgets(buffer, 256, stdin); 
        
        // Wysłanie danych
        send(sock, buffer, strlen(buffer), 0);
        printf("Wysłano!\n");

        // Sprawdzenie, czy użytkownik wpisał "-1" (uwzględniając znak Enter '\n')
        if (strcmp(buffer, "-1\n") == 0) {
            printf("Zamykanie połączenia...\n");
            break;
        }
    }

    // Zamknięcie połączenia
    close(sock);
    return 0;
}