#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include "render.h"
#include <pthread.h>

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

int decode_button(int c){
  switch(c)
{
  case 1:
    return 6;
  break;
  case 2:
    return 4;
  break;
  case 3:
    return 7;
  break;
  case 4:
    return 1;
  break;
  case 5:
    return 2;
  break;
  case 6:
    return 3;
  break;
  case 7:
    return 8;
  break;
  case 8:
    return 5;
  break;
  case 9:
    return 9;
  break;
  default:
  return -1;
}

}

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
            stan_gry = 3;
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
            recv(sock, &t_cel_tusz, 1, 0);
            recv(sock, &t_cel_tekst, 1, 0);
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
            stan_gry = 4; 
            runda_trwa = 0;
            for(int i = 0; i < obecni_gracze; i++) {
                punkty[i] = finalne_punkty[i];
            }
            pthread_mutex_unlock(&muteks_gry);

            printf("\n=== [Sieć] KONIEC GRY! ===\nWyniki koncowe:\n");
            int biggest = 0;
            char c = -127;
            for(int i = 0; i < obecni_gracze; i++) {
                printf("Gracz %d: %d pkt\n", i + 1, finalne_punkty[i]);
                if(c < finalne_punkty[i]){
                    c = finalne_punkty[i];
                    biggest = i;
                }
            }
            winner = biggest+1;
            win_val = c;
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

// struktura parametrow okna
typedef struct {
    Display *dpy;
    int screen;
    Window win;
    GLXContext ctx;
    XSetWindowAttributes attr;
    Bool fs;
    XF86VidModeModeInfo deskMode;
    int x, y;
    unsigned int width, height;
    unsigned int depth;    
} GLWindow;

// atrybuty dla trybu jednobuforowego w formacie RGBA
// co najmniej 4 bity na kolor oraz 16 bitow bufor glebokosci
static int attrListSgl[] = {GLX_RGBA, 
    GLX_RED_SIZE, 4, 
    GLX_GREEN_SIZE, 4, 
    GLX_BLUE_SIZE, 4, 
    GLX_DEPTH_SIZE, 16,
    None};

// atrybuty dla tryby podwojnego buforowego w formacie RGBA
// co najmniej 4 bity na kolor oraz 16 bitow bufor glebokosci
static int attrListDbl[] = { GLX_RGBA, GLX_DOUBLEBUFFER, 
    GLX_RED_SIZE, 4, 
    GLX_GREEN_SIZE, 4, 
    GLX_BLUE_SIZE, 4, 
    GLX_DEPTH_SIZE, 16,
    None };

GLWindow GLWin;
int counter=0;
//int iMx,iMy;
Bool done;
char tytul[] = "X Window + OpenGL";

void setscene_results(){
        stan_gry = 4;
}
void setscene_game(){
        stan_gry = 3;
}
void setscene_lobby(){
        stan_gry = 2;
}
void setscene_mainmenu(){
        stan_gry = 1;
}

static void sendSceneChangeToServer(const char *msg)
{
    if (ip.empty()) {
        printf("No server IP set, skipping scene change notify.\n");
        return;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Failed to create socket for scene change notify.\n");
        return;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        printf("Invalid server IP: %s\n", ip.c_str());
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Scene change connect failed.\n");
        close(sock);
        return;
    }

    send(sock, msg, strlen(msg), 0);
    close(sock);
}


// funkcja do zwalniania uzywanych zasobow oraz przywracania starego pulpitu
void killGLWindow(void)
{   if (GLWin.ctx)
    {   if (!glXMakeCurrent(GLWin.dpy, None, NULL))
            printf("Could not release drawing context.\n");
        glXDestroyContext(GLWin.dpy, GLWin.ctx);
        GLWin.ctx = NULL;
    }
    // przywrocenie oryginalnej rozdzielczosci w przypadku trybu fullscreen
    if (GLWin.fs)
    {   XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, &GLWin.deskMode);
        XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
    }
    XCloseDisplay(GLWin.dpy);
}

// tworzenie okna o zadanych parametrach
Bool createGLWindow(char* title, int width, int height, int bits,
                    Bool fullscreenflag)
{   XVisualInfo *vi;
    Colormap cmap;
    int dpyWidth, dpyHeight;
    int i;
    int glxMajorVersion, glxMinorVersion;
    int vidModeMajorVersion, vidModeMinorVersion;
    XF86VidModeModeInfo **modes;
    int modeNum;
    int bestMode;
    Atom wmDelete;
    Window winDummy;
    unsigned int borderDummy;
    
    GLWin.fs = fullscreenflag;
    bestMode = 0;    // zaznaczenie obecnego trybu jako najlepszego
    GLWin.dpy = XOpenDisplay(0);    // pobranie wyswietlacza
    GLWin.screen = DefaultScreen(GLWin.dpy);
    
    // okreslenie wersji XF86VidModeExtension
    XF86VidModeQueryVersion(GLWin.dpy, &vidModeMajorVersion,
        &vidModeMinorVersion);
    printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion,
        vidModeMinorVersion);
    XF86VidModeGetAllModeLines(GLWin.dpy, GLWin.screen, &modeNum, &modes);
    GLWin.deskMode = *modes[0];    // zapamietanie rozdzielczosci pulpitu

    // przeszukiwanie trybow w celu odnalezienia zadanej rozdzielczosci okna
    for (i = 0; i < modeNum; i++)
        if ((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
            bestMode = i;

    // okreslenie trybu wizualizacji (jedno- czy dwubuforowy)
    vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListDbl);
    if (vi == NULL)
    {   vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListSgl);
        printf("Only Singlebuffered Visual!\n");
    }
    else printf("Got Doublebuffered Visual!\n");

    // okreslenie wersji glX
    glXQueryVersion(GLWin.dpy, &glxMajorVersion, &glxMinorVersion);
    printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);

    // tworzenie kontekstu renderowania GLX i mapy kolorow
    GLWin.ctx = glXCreateContext(GLWin.dpy, vi, 0, GL_TRUE);
    cmap = XCreateColormap(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
        vi->visual, AllocNone);
    GLWin.attr.colormap = cmap;
    GLWin.attr.border_pixel = 0;

    if (GLWin.fs)
    {   XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, modes[bestMode]);
        XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
        dpyWidth = modes[bestMode]->hdisplay;
        dpyHeight = modes[bestMode]->vdisplay;
        printf("Resolution %dx%d\n", dpyWidth, dpyHeight);
        XFree(modes);
    
        // tworzenie okna w trybie pelnoekranowym
        GLWin.attr.override_redirect = True;
        GLWin.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
            StructureNotifyMask | PointerMotionMask;
        GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
            0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual,
            CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
            &GLWin.attr);
        XWarpPointer(GLWin.dpy, None, GLWin.win, 0, 0, 0, 0, 0, 0);
		XMapRaised(GLWin.dpy, GLWin.win);
        XGrabKeyboard(GLWin.dpy, GLWin.win, True, GrabModeAsync,
            GrabModeAsync, CurrentTime);
        XGrabPointer(GLWin.dpy, GLWin.win, True, ButtonPressMask,
            GrabModeAsync, GrabModeAsync, GLWin.win, None, CurrentTime);
    }
    else
    {   // tworzenie okna w trybie okienkowym
        GLWin.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
            StructureNotifyMask | PointerMotionMask;
        GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
            0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
            CWBorderPixel | CWColormap | CWEventMask, &GLWin.attr);
        wmDelete = XInternAtom(GLWin.dpy, "WM_DELETE_WINDOW", True);
        XSetWMProtocols(GLWin.dpy, GLWin.win, &wmDelete, 1);
        XSetStandardProperties(GLWin.dpy, GLWin.win, title,
            title, None, NULL, 0, NULL);
        XMapRaised(GLWin.dpy, GLWin.win);
    }       

    // zaznaczenie kontekstu renderowania jako aktywnego
    glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
    XGetGeometry(GLWin.dpy, GLWin.win, &winDummy, &GLWin.x, &GLWin.y,
        &GLWin.width, &GLWin.height, &borderDummy, &GLWin.depth);
    printf("Depth %d\n", GLWin.depth);
    if (glXIsDirect(GLWin.dpy, GLWin.ctx)) 
        printf("Congrats, you have Direct Rendering!\n");
    else
        printf("Sorry, no Direct Rendering possible!\n");
    if (!initGL()) // inicjacja OpenGL (render.cpp)
    {   printf("Could not initialize OpenGL.\nAborting...\n");
        return False;
    }
    else resizeGLScene(GLWin.width, GLWin.height); 

    return True;    
}

// funkcja okreslajaca reakcje na wcisniecie klawisza
void keyPressed(KeySym key) 
{
    switch (key)
    { case XK_Escape:
          done = True;
          break;
    case XK_F1:
       
         break;
    case XK_1:
        ip = ip + "1";
        ip_text = ip_text + "1";
        break;
    case XK_2:
        ip = ip + "2";
        ip_text = ip_text + "2";
        break;
    case XK_3:
        ip = ip + "3";
        ip_text = ip_text + "3";
        break;
    case XK_4:
        ip = ip + "4";
        ip_text = ip_text + "4";
        break;
    case XK_5:
        ip = ip + "5";
        ip_text = ip_text + "5";
        break;
    case XK_6:
        ip = ip + "6";
        ip_text = ip_text + "6";
        break;
    case XK_7:
        ip = ip + "7";
        ip_text = ip_text + "7";
        break;
    case XK_8:
        ip = ip + "8";
        ip_text = ip_text + "8";
        break;
    case XK_9:
        ip = ip + "9";
        ip_text = ip_text + "9";
        break;
    case XK_0:
        ip = ip + "0";
        ip_text = ip_text + "0";
        break;
    case XK_period:
        ip = ip + ".";
        ip_text = ip_text + ".";
        break;
    case XK_BackSpace:
        if (!ip.empty()) {
            ip.pop_back();
            ip_text.pop_back();
        }
        break;
    case XK_u: 
        setscene_results();
        break;
    case XK_i: 
        setscene_game();
        break;
    case XK_o: 
        setscene_lobby();
        break;
    case XK_p: 
        setscene_mainmenu();
        break;
    }
}

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in serv_addr;

    pthread_t thread_id;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    XEvent event;
    KeySym key;
        
    done = False;

    GLWin.fs = False; // domyslne odpalenie trybu okienkowego
    if (!createGLWindow(tytul, WINDOW_WIDTH, WINDOW_HEIGHT, 24, GLWin.fs))
        done = True;
  

    // petla obslugi zdarzen
    while (!done)
    {   // uchwyt do kolejki zdarzen
        while (XPending(GLWin.dpy) > 0)
        {   XNextEvent(GLWin.dpy, &event);
            switch (event.type)
            { case Expose: // odswiezenia okna
                  if (event.xexpose.count != 0) break;
                   //drawGLScene(counter); // rysowanie przeniesione poza switch
                  break;
              case ConfigureNotify: // zmiana rozmiaru okna
                  if ((event.xconfigure.width !=int(GLWin.width)) || 
                      (event.xconfigure.height !=int(GLWin.height)))
                  {   GLWin.width = event.xconfigure.width;
                      GLWin.height = event.xconfigure.height;
                      // printf("Resize event\n");
                      resizeGLScene(event.xconfigure.width,
                          event.xconfigure.height); // zmiana rozmiaru (render.cpp)
                  }
                  break;
              case MotionNotify: // wykrycie ruchu myszy
                  // iMx=event.xmotion.x;
                  // iMy=event.xmotion.y;
                  break;		
              case ButtonPress: // wcisniecie przycisku myszy
              {
                    int mouseX = event.xbutton.x;
                    int mouseY = event.xbutton.y;
                    printf("X: %d, Y: %d \n", mouseX, mouseY);
                    if(stan_gry == 4) {

                        int btn1Width = (int)GLWin.width*(520.0/WINDOW_WIDTH);
                        int btn1Height = (int)GLWin.height*(80.0/WINDOW_HEIGHT);
                        int btn1X = (GLWin.width-btn1Width)/2;
                        int btn1Y = (int)GLWin.height*(400.0/WINDOW_HEIGHT);

                        int btn2Width = (int)GLWin.width*(520.0/WINDOW_WIDTH);
                        int btn2Height = (int)GLWin.height*(80.0/WINDOW_HEIGHT);
                        int btn2X = (GLWin.width-btn2Width)/2;
                        int btn2Y = (int)GLWin.height*(535.0/WINDOW_HEIGHT);

                        if (mouseX >= btn1X && mouseX <= btn1X + btn1Width &&
                            mouseY >= btn1Y && mouseY <= btn1Y + btn1Height) {
                          
                            printf("Join again button clicked %d \n", mouseX);
                            setscene_lobby();
                        } else if(mouseX >= btn2X && mouseX <= btn2X + btn2Width &&
                                  mouseY >= btn2Y && mouseY <= btn2Y + btn2Height){ 
                            printf("Main menu button clicked %d \n", mouseX);
                            setscene_mainmenu();
                            //TODO add main menu functionality and server comunication change scene
                        }

                    } else if(stan_gry == 3){
                        // --- Definicje siatki przycisków 3x3 ---
                        const float baseX[3] = {120.0, 410.0, 695.0}; // Kolumny
                        const float baseY[3] = {204.0, 310.0, 410.0}; // Rzędy
                        const float baseH[3] = {86.0, 85.0, 90.0};    // Wysokości rzędów
                        const float baseW = 260.0;                    // Wspólna szerokość

                        int btnW = (int)(GLWin.width * (baseW / WINDOW_WIDTH));

                        // Sprawdzamy wszystkie 9 przycisków w pętli
                        for (int i = 0; i < 9; i++) {
                            int row = i / 3; // Wynik to 0, 1 lub 2
                            int col = i % 3; // Wynik to 0, 1 lub 2

                            int btnX = (int)(GLWin.width * (baseX[col] / WINDOW_WIDTH));
                            int btnY = (int)(GLWin.height * (baseY[row] / WINDOW_HEIGHT));
                            int btnH = (int)(GLWin.height * (baseH[row] / WINDOW_HEIGHT));

                            // --- Obsługa kliknięć ---
                            if (mouseX >= btnX && mouseX <= btnX + btnW && 
                                mouseY >= btnY && mouseY <= btnY + btnH) {
                                
                                printf("Button %d clicked %d \n", decode_button(i + 1), mouseX);
                                send(sock,&kolory_tekst[decode_button(i+1)-1],1, 0);
                                //printf("%s \n",nazwa_text(kolory_tusz[decode_button(i+1)-1]).c_str());
                                
                                // TODO: Dodaj switch(i) lub wywołaj funkcję na podstawie indeksu przycisku
                                
                                break; // Przerywamy pętlę - kliknięto już w przycisk
                            }
                        }

                    } else if(stan_gry == 2){


                        int btnWidth = (int)GLWin.width*(520.0/WINDOW_WIDTH);
                        int btnHeight = (int)GLWin.height*(80.0/WINDOW_HEIGHT);
                        int btnX = (GLWin.width-btnWidth)/2;
                        int btnY = (int)GLWin.height*(400.0/WINDOW_HEIGHT);

                        if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
                            mouseY >= btnY && mouseY <= btnY + btnHeight) {
                          
                            printf("Ready button clicked %d \n", mouseX);
                            send(sock,"READY",5, 0);
                            //TODO add ready functionality and server comunication of readiness
                        }


                    } else {

                        int btnWidth = (int)GLWin.width*(520.0/WINDOW_WIDTH);
                        int btnHeight = (int)GLWin.height*(80.0/WINDOW_HEIGHT);
                        int btnX = (GLWin.width-btnWidth)/2;
                        int btnY = (int)GLWin.height*(400.0/WINDOW_HEIGHT);

                        if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
                            mouseY >= btnY && mouseY <= btnY + btnHeight) {
                          
                            printf("connect button clicked,  add connect function %d \n", mouseX);
                            stan_gry = 2;
                            setscene_lobby();
                             inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);

                        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                            printf("Błąd połączenia. Czy serwer jest włączony?\n");
                            return 1;
                        }

                        // Uruchamiamy wątek w tle, który nasłuchuje serwera
                        pthread_create(&thread_id, NULL, watek_sieciowy, (void *)&sock);
                        }

                    }


                  break;
              }
              case KeyPress: // wcisniecie klawisza
                  key = XLookupKeysym(&event.xkey, 0);
                  keyPressed(key);
                  break;
              case ClientMessage:    
                  if (*XGetAtomName(GLWin.dpy, event.xclient.message_type)
                      == *"WM_PROTOCOLS")
                      {   printf("Exiting sanely...\n");
                          done = True;
                      }
                  break;
              default:
                  break;
            }
        }

	if (++counter >= 360) counter = 0;

        drawGLScene(counter); // rysowanie sceny (render.cpp)
	glXSwapBuffers(GLWin.dpy,GLWin.win);
    }
    deleteAll();
    killGLWindow();
    return 0;
}
