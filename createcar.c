#include <stdio.h>

void createcar(int x,int y,int horizontal,int tab[6][6]) {
    tab[x][y]=1;
    if(horizontal)
        tab[x+1][y]=1;
    else
        tab[x][y+1]=1;    
}
