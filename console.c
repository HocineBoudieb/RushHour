/*
 * console.c
 * PoPS ESR v1.1
 *
 */

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "console.h"

/* Attente d'un appui sur Entrée */
void wait() {
    while (fgetc(stdin) != '\n');
}


/* Efface l'affichage */
void clrscr() {
  printf("\033[2J\033[?6h");
}


/* Déplacement en x,y du curseur */
void gotoxy(int x, int y) {
  printf("\033[%d;%dH", y, x);
}


void setfontcolor(int color) {
  printf("\033[%dm", color);
}

void setbgrcolor(int color) {
  printf("\033[%dm", color+10);
}

/* Police en mode bold (gras ou en évidence) */
void setfontbold(int status) {
  printf("\033[%dm", status);
}

void setunderline(int status) {
  if (status) status = 4;
  printf("\033[%dm", status);
}

void setblink(int status) {
  if (status) status = 5;
  printf("\033[%dm", status);
}

/* Définit le titre du terminal */
void settitle(char const* title) {
  printf("\033]0;%s\x7", title);
}

/* Désactive l'affichage du curseur */
void hidecursor() {
  printf("\033[?25l");
}

/* Réactive l'affichage du curseur */
void unhidecursor() {
  printf("\033[?25h");
}

void setcurshape(int shape) {
  // vt520/xterm-style; linux terminal uses ESC[?1;2;3c, not implemented
  printf("\033[%d q", shape);
}

/* Récupération de la taille du terminal */
struct termsize gettermsize() {
  struct termsize size;
  struct winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  size.cols = win.ws_col;
  size.rows = win.ws_row;
  return size;
}

/* Récupération d'un caractère au clavier
 * sans écho du caractère ni besoin d'appuyer
 * sur Entrée
 */
int getch() {
  struct termios oldattr, newattr;
  tcgetattr(STDIN_FILENO, &oldattr);

  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  int ch = getc(stdin);

  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  return ch;
}

/* Récupération d'un caractère au clavier
 * avec écho du caractère sans besoin d'appuyer
 * sur Entrée
 */
int getche() {
  struct termios oldattr, newattr;
  tcgetattr(STDIN_FILENO, &oldattr);

  newattr = oldattr;
  newattr.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  int ch = getc(stdin);

  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  return ch;
}

void clrline() {
  printf("\033[2K\033E");
}

void resetcolors() {
  printf("\033[0m");
}

void resetterminal() {
  printf("\033c");
}

/* sous Unix/Linux la sortie standard
 * stdout est bufférisée, i.e., un printf
 * ne s'affiche que si un \n est dans le buffer
 * Cette fonction désactive le buffer
 */
void nostdoutbuff() {
  setvbuf(stdout, NULL, _IONBF, 0);
}

/* Réactive le buffer de la sortie standard */
void setstdoutbuff() {
  setvbuf(stdout, NULL, _IOLBF, 0);
}
