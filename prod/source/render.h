void resizeGLScene(unsigned int width, unsigned int height);
int initGL(void);
int drawGLScene(int countervoid);
void deleteAll();
extern std::string ip;
extern std::string ip_text;
extern bool lobby;
extern bool game;
extern bool results;
extern int stan_gry;         // 1-Lobby, 2-Gra, 3-Koniec
extern int num_players;
extern int runda_trwa;
extern char runda_lvl;
extern char punkty[];
extern char kolory_tekst[9]; // Pierwsze 9 bajtów (np. jakie słowo)
extern char kolory_tusz[9];  // Drugie 9 bajtów (np. jakim kolorem pomalowane)
extern char cel_tekst;         // Pierwszy pojedynczy bajt (cel do znalezienia)
extern char cel_tusz;          // Drugi pojedynczy bajt (wskazówka)
extern char zdarzenia[4];
extern std::string nazwa_text(char c);
extern char winner;
extern char win_val;