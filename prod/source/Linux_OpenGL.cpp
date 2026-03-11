#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include "render.h"

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

    }
}

int main(int argc, char **argv)
{
    XEvent event;
    KeySym key;
        
    done = False;

    GLWin.fs = False; // domyslne odpalenie trybu okienkowego
    if (!createGLWindow(tytul, 1080, 720, 24, GLWin.fs))
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
                    int btnX = 280;
                    int btnY = 400;
                    int btnWidth = 520;
                    int btnHeight = 80;

                    if (mouseX >= btnX && mouseX <= btnX + btnWidth &&
                          mouseY >= btnY && mouseY <= btnY + btnHeight) {
                          
                          printf("Button clicked at %d, %d!\n", mouseX, mouseY);
                          // Do your button action here
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
