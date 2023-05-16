/******************************************************************************/
/*                                                                            */
/*                              Simulateur de frappe                          */
/*                             Auteur: CyberCookieKing                        */
/*                                                                            */
/* But:                                                                       */
/*  Simule la frappe de touches à l'aide de la bibliothèque X11               */
/*                                                                            */
/* Instalation:                                                               */
/*  sudo apt install libx11-dev libxtst-dev                                   */
/*                                                                            */
/* Compilation:                                                               */
/*  gcc -o simulateur simulateur.c -lX11 -lXtst                               */
/*                                                                            */
/* Utilisation:                                                               */
/*  - Exécuter l'exécutable 'simulateur'                                      */
/*  - Simule l'appui de la touche Super, la frappe de "Mouspad",              */
/*    l'appui de la touche Return et la frappe de "Hello World !!"            */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

void simulateKeyPress(Display *display, KeySym key)
{
    KeyCode keycode = XKeysymToKeycode(display, key);
    XTestFakeKeyEvent(display, keycode, True, 0);
    XFlush(display);
}

void simulateKeyRelease(Display *display, KeySym key)
{
    KeyCode keycode = XKeysymToKeycode(display, key);
    XTestFakeKeyEvent(display, keycode, False, 0);
    XFlush(display);
}

void simulateKey(Display *display, KeySym key)
{
    simulateKeyPress(display, key);
    simulateKeyRelease(display, key);
}

void simulateKeyCombination(Display *display, KeySym key[], size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        simulateKey(display, key[i]);
        usleep(1000);
    }
}

unsigned int* convertToAsciiValues(const char* str)
{
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    unsigned int* asciiValues = (unsigned int*)malloc(length * sizeof(unsigned int));

    for (int i = 0; i < length; i++) {
        asciiValues[i] = (unsigned int)str[i];
    }

    return asciiValues;
}

KeySym* convertToKeySym(Display* display, unsigned int* asciiValues, int length) 
{
    KeySym* keySyms = (KeySym*)malloc(length * sizeof(KeySym));

    for (int i = 0; i < length; i++) {
        keySyms[i] = XStringToKeysym(XKeysymToString(asciiValues[i]));
    }

    return keySyms;
}

KeySym* asciiToKeySym(Display* display, const char* str)
{
    unsigned int* asciiValues = convertToAsciiValues(str);
    int length = strlen(str);
    KeySym* keySyms = convertToKeySym(display, asciiValues, length);
    return keySyms;
}

void simulateKeyWrite(Display* display, const char* str)
{
    int length = strlen(str);
    KeySym* keySyms = asciiToKeySym(display, str);

    if (keySyms != NULL) {
        simulateKeyCombination(display, keySyms, length);
        free(keySyms); // Libérer la mémoire allouée
    }
}

int main()
{
    Display* display = XOpenDisplay(":0");
    if (display == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le display X11.\n");
        return 1;
    }

    // Simuler l'appui de la touche Super
    simulateKey(display, XK_Super_L);
    usleep(100000);

    // Simuler la frappe de Mouspad
    simulateKeyWrite(display, "Mouspad");
    usleep(100000);

    // Simuler l'appui de la touche Return
    simulateKey(display, XK_Return);
    usleep(1000000);

    // Simuler la frappe de Hello World
    simulateKeyWrite(display, "Hello World !!");
    usleep(100000);

    XCloseDisplay(display);
    return 0;
}
