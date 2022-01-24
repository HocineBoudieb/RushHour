#include <stdio.h>
#include "console.h"


int main(void) {
  int x=10, y=20;
  int i=0;
  struct termsize taille;

  clrscr();
  settitle("--==== Test de console.h ====--");
  printf("Appuyer 5 fois sur Espace!");
  gotoxy(x,y); /* on déplace le curseur */
  setfontcolor(GREEN);
  printf("Hello World!!!");
  hidecursor();
  while(x<15) {
    while(getch()!=' ');
    x++;
    clrscr();
    gotoxy(x,y);
    printf("Hello World!!!");
   }
  clrscr();
  setfontbold(TRUE);
  setfontcolor(YELLOW);
  printf("Hello World!!!\nAppuyez sur Entrée\n");
  while(getch()!='\n');
  for(i=30;i<38;i++) {
    setbgrcolor(i);
    printf("Une couleur de fond différente\n");
  }
  setbgrcolor(BLACK);
  for(i=30;i<38;i++) {
    setfontcolor(i);
    printf("Une couleur de police différente\n");
  }
  printf("\nAppuyez sur Entrée à nouveau\n");
  setfontbold(FALSE);

  while(getch()!='\n');
  resetcolors();
  clrscr();
  
  taille = gettermsize();
  printf("Taille du terminal: %d colonnes et %d lignes\n",taille.cols,taille.rows);
  for (i=0;i<taille.cols;i++) {
	  printf("=");
  }

  printf("Appuyez sur q pour quitter\n");
  while (getch() != 'q');

  resetcolors();
  resetterminal();

  return 0;
}
