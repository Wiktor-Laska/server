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

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

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
        results = true;
        game = false;
        lobby = false;
}
void setscene_game(){
        results = false;
        game = true;
        lobby = false;
}
void setscene_lobby(){
        results = false;
        game = false;
        lobby = true;
}
void setscene_mainmenu(){
        results = false;
        game = false;
        lobby = false;
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
                    if(results == true) {

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

                    } else if(game == true){
                        // --- Rząd 1 ---
                        int btn1Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn1Height = (int)(GLWin.height * (86.0 / WINDOW_HEIGHT));
                        int btn1X = (int)(GLWin.width * (120.0 / WINDOW_WIDTH));
                        int btn1Y = (int)(GLWin.height * (204.0 / WINDOW_HEIGHT));

                        int btn2Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn2Height = (int)(GLWin.height * (86.0 / WINDOW_HEIGHT));
                        int btn2X = (int)(GLWin.width * (410.0 / WINDOW_WIDTH));
                        int btn2Y = (int)(GLWin.height * (204.0 / WINDOW_HEIGHT));

                        int btn3Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn3Height = (int)(GLWin.height * (86.0 / WINDOW_HEIGHT));
                        int btn3X = (int)(GLWin.width * (695.0 / WINDOW_WIDTH));
                        int btn3Y = (int)(GLWin.height * (204.0 / WINDOW_HEIGHT));

                        // --- Rząd 2 ---
                        int btn4Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn4Height = (int)(GLWin.height * (85.0 / WINDOW_HEIGHT));
                        int btn4X = (int)(GLWin.width * (120.0 / WINDOW_WIDTH));
                        int btn4Y = (int)(GLWin.height * (310.0 / WINDOW_HEIGHT));

                        int btn5Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn5Height = (int)(GLWin.height * (85.0 / WINDOW_HEIGHT));
                        int btn5X = (int)(GLWin.width * (410.0 / WINDOW_WIDTH));
                        int btn5Y = (int)(GLWin.height * (310.0 / WINDOW_HEIGHT));

                        int btn6Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn6Height = (int)(GLWin.height * (85.0 / WINDOW_HEIGHT));
                        int btn6X = (int)(GLWin.width * (695.0 / WINDOW_WIDTH));
                        int btn6Y = (int)(GLWin.height * (310.0 / WINDOW_HEIGHT));

                        // --- Rząd 3 ---
                        int btn7Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn7Height = (int)(GLWin.height * (90.0 / WINDOW_HEIGHT));
                        int btn7X = (int)(GLWin.width * (120.0 / WINDOW_WIDTH));
                        int btn7Y = (int)(GLWin.height * (410.0 / WINDOW_HEIGHT));

                        int btn8Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn8Height = (int)(GLWin.height * (90.0 / WINDOW_HEIGHT));
                        int btn8X = (int)(GLWin.width * (410.0 / WINDOW_WIDTH));
                        int btn8Y = (int)(GLWin.height * (410.0 / WINDOW_HEIGHT));

                        int btn9Width = (int)(GLWin.width * (260.0 / WINDOW_WIDTH));
                        int btn9Height = (int)(GLWin.height * (90.0 / WINDOW_HEIGHT));
                        int btn9X = (int)(GLWin.width * (695.0 / WINDOW_WIDTH));
                        int btn9Y = (int)(GLWin.height * (410.0 / WINDOW_HEIGHT));

                        // --- Obsługa kliknięć ---
                        if (mouseX >= btn1X && mouseX <= btn1X + btn1Width && mouseY >= btn1Y && mouseY <= btn1Y + btn1Height) {
                            printf("Button 1 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 1
                        } else if (mouseX >= btn2X && mouseX <= btn2X + btn2Width && mouseY >= btn2Y && mouseY <= btn2Y + btn2Height) {
                            printf("Button 2 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 2
                        } else if (mouseX >= btn3X && mouseX <= btn3X + btn3Width && mouseY >= btn3Y && mouseY <= btn3Y + btn3Height) {
                            printf("Button 3 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 3
                        } else if (mouseX >= btn4X && mouseX <= btn4X + btn4Width && mouseY >= btn4Y && mouseY <= btn4Y + btn4Height) {
                            printf("Button 4 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 4
                        } else if (mouseX >= btn5X && mouseX <= btn5X + btn5Width && mouseY >= btn5Y && mouseY <= btn5Y + btn5Height) {
                            printf("Button 5 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 5
                        } else if (mouseX >= btn6X && mouseX <= btn6X + btn6Width && mouseY >= btn6Y && mouseY <= btn6Y + btn6Height) {
                            printf("Button 6 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 6
                        } else if (mouseX >= btn7X && mouseX <= btn7X + btn7Width && mouseY >= btn7Y && mouseY <= btn7Y + btn7Height) {
                            printf("Button 7 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 7
                        } else if (mouseX >= btn8X && mouseX <= btn8X + btn8Width && mouseY >= btn8Y && mouseY <= btn8Y + btn8Height) {
                            printf("Button 8 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 8
                        } else if (mouseX >= btn9X && mouseX <= btn9X + btn9Width && mouseY >= btn9Y && mouseY <= btn9Y + btn9Height) {
                            printf("Button 9 clicked %d \n", mouseX);
                            // TODO: Akcja dla przycisku 9
                        }

                    } else if(lobby == true){


                        int btnWidth = (int)GLWin.width*(520.0/WINDOW_WIDTH);
                        int btnHeight = (int)GLWin.height*(80.0/WINDOW_HEIGHT);
                        int btnX = (GLWin.width-btnWidth)/2;
                        int btnY = (int)GLWin.height*(400.0/WINDOW_HEIGHT);

                        if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
                            mouseY >= btnY && mouseY <= btnY + btnHeight) {
                          
                            printf("Ready button clicked %d \n", mouseX);
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
                            setscene_lobby();
                            //TODO and sceen change and connect function
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
