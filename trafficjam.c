#include <stdio.h>
#include "console.h"
#include "trafficjam.h"
#include <time.h> 


void plateau(int tab[6][6]) {
    hidecursor();
    int nl=0;
    int nc=0;
    setbgrcolor(BLACK);
    clrscr();
    printf("\n| -  -  -  -  -  - |\n");
    for(nl=0; nl<6;nl++){
        printf("|");
        for(nc=0; nc<6;nc++){
            if(tab[nc][nl]!=0){
                setbgrcolor(tab[nc][nl]);
                setfontcolor(tab[nc][nl]);
            }
            else{
                setfontcolor(WHITE);
                setbgrcolor(BLACK);
            }
            printf(" □ ");
            setbgrcolor(BLACK);
            setfontcolor(WHITE);
        }
        if(nl==2)
            printf(">\n");
        else
            printf("|\n");
    }
    printf("| -  -  -  -  -  - |");
    printf("\n\n");
    setfontbold(TRUE);
    setfontcolor(RED);
    printf("appuyez sur q pour quitter.\n");
    resetcolors();
    setfontbold(FALSE);
    setbgrcolor(BLACK);
}

int inittab(int tab[6][6],carr cars[24]){
    for(int c=0; c<6;c++){
        for(int j=0; j<6;j++){
            tab[c][j]=0;
        }
    }
    int i=0;
    while(cars[i].color!=BLACK){
        tab[cars[i].x][cars[i].y]=cars[i].color;
        if(cars[i].horizontal){
            tab[cars[i].x+1][cars[i].y]=cars[i].color;
            if(cars[i].big)
                tab[cars[i].x+2][cars[i].y]=cars[i].color;
        }
        else{
            tab[cars[i].x][cars[i].y+1]=cars[i].color;
            if(cars[i].big)
                tab[cars[i].x][cars[i].y+2]=cars[i].color;
        }
        i++;
   }
return i;
}


void createcar(int x,int y,int horizontal,int big,int index,carr carss[24],int* countshots, int carcolor) {

    carr voiture[24];
    for(int a=0; a<24;a++){
        voiture[a].color=BLACK;
        voiture[a].x=0;
        voiture[a].y=0;
        voiture[a].idx=a;
        voiture[a].horizontal=0;
        voiture[a].big=0;
    }
    int tabcaraftermove[6][6]={0};
    int tabwocar[6][6]={0};
    int el=0;
    int count=0;
    while (carss[el].color!=BLACK)
    {
        if(el!=index){
            voiture[count]=carss[el];
            count++;
        }
        el++;
    }
    carr caraftermove[2];
    caraftermove[0].color=carcolor;
    caraftermove[0].x=x;
    caraftermove[0].y=y;
    caraftermove[0].idx=0;
    caraftermove[0].horizontal=horizontal;
    caraftermove[0].big=big;
    caraftermove[1].color=BLACK;
    caraftermove[1].x=0;
    caraftermove[1].y=0;
    caraftermove[1].idx=1;
    caraftermove[1].horizontal=0;
    caraftermove[1].big=0;
    int exist=0;
    int idx=0;
    //wo = without
    int a=inittab(tabwocar,voiture);
    a=inittab(tabcaraftermove,caraftermove);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if(tabwocar[i][j]!=0 && tabcaraftermove[i][j]!=0)
                exist=1;
        }
        
    }
    
    int i=index;
    if (exist==0)
    {   
        *countshots+=1;
        carss[i].color=carcolor;
        carss[i].x=x;
        carss[i].y=y;
        carss[i].horizontal=horizontal;    
        carss[i].big=big;
    }
    
    
    
}


int analyse(carr cars[24]){
    int gagne;
    if(cars[0].x==5-cars[0].big && cars[0].y==2)
        gagne=1;
    else
        gagne=0;
    return gagne;
}

void hkey(carr cars[24], int caridx,int* ncoups){
    if(cars[caridx].x!=0 && cars[caridx].horizontal)
        createcar(cars[caridx].x-cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}

void lkey(carr cars[24], int caridx,int* ncoups){
    if(caridx==0)
        createcar(cars[caridx].x+cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
    else if(cars[caridx].x!=4-cars[caridx].big && cars[caridx].horizontal)
        createcar(cars[caridx].x+cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}

void kkey(carr cars[24], int caridx,int* ncoups){
    if(cars[caridx].y!=0 && cars[caridx].horizontal==0)
        createcar(cars[caridx].x,cars[caridx].y-1,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}

void jkey(carr cars[24], int caridx,int* ncoups){
    if(cars[caridx].y!=4-cars[caridx].big && cars[caridx].horizontal==0)
        createcar(cars[caridx].x,cars[caridx].y+1,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}

// void niveau1(carr cars[24]){
//     int a;
//     for(int i=0; i<24;i++){
//         cars[i].color=BLACK;
//         cars[i].x=0;
//         cars[i].y=0;
//         cars[i].idx=i;
//         cars[i].horizontal=0;
//         cars[i].big=0;
//     }
//     createcar(0,2,1,0,0,cars,&a,RED);
//     createcar(4,2,0,0,1,cars,&a,BRIGHTMAGENTA);
//     createcar(0,5,1,1,2,cars,&a,GREEN);
// }

// void niveau2(carr cars[24]){
//     int a;
//     for(int i=0; i<24;i++){
//         cars[i].color=BLACK;
//         cars[i].x=0;
//         cars[i].y=0;
//         cars[i].idx=i;
//         cars[i].horizontal=0;
//         cars[i].big=0;
//     }
//     createcar(0,2,1,0,0,cars,&a,RED);
//     createcar(4,2,0,0,1,cars,&a,BRIGHTMAGENTA);
//     createcar(0,5,1,1,2,cars,&a,GREEN);
//     createcar(2,0,1,0,3,cars,&a,BRIGHTYELLOW);
// }
void load_level(int level, carr cars[24]){
    int success;
    char niveauX[12]="niveauX.txt";
    niveauX[6]=level+48;
    niveauX[11]='\0';
    FILE *fp;
    fp=fopen(niveauX,"r");
    int i=0;
    if(fp==NULL){
        setfontbold(TRUE);
        setfontcolor(RED);
        printf("\n AUCUNE SAUVEGARDE !!!\n");
        printf("Appuyez sur n'importe quelle touche ...");
        resetcolors();
        while(getch()=='\0');
        success=0;
    }
    else{
        while(i<18){
            fscanf(fp,"%d %d %d %d %d %d",&cars[i].idx,&cars[i].color,&cars[i].x,&cars[i].y,&cars[i].horizontal,&cars[i].big);
            i++;
        }
        success=1;
    }
    fclose(fp);
}
void nextlevel(carr cars[24],int* level){
    *level+=1;
    if(*level<LEVELMAX+1)
        load_level(*level,cars);

}
void affhelp(void){
    gotoxy(30,2);
    printf("\t==AIDE==");
    gotoxy(30,3);
    printf("a: fermer/ouvrir l'aide");
    gotoxy(30,4);
    printf("h: bouger sa voiture à gauche");
    gotoxy(30,5);
    printf("j: bouger sa voiture en bas");
    gotoxy(30,6);
    printf("k: bouger sa voiture en haut");
    gotoxy(30,7);
    printf("l: bouger sa voiture à droite");
    gotoxy(30,8);
    printf("w: changer de voiture");
    gotoxy(30,9);
    printf("p: afficher les meilleurs scores");
    gotoxy(0,12);
}


void save(carr cars[24],int level){
    FILE *fpsrc;
    int i=0;
    fpsrc= fopen("save.txt","w");
    fprintf(fpsrc,"%d\n",level);
    while(cars[i].color!=BLACK){
        fprintf(fpsrc,"%d %d %d %d %d %d\n",cars[i].idx,cars[i].color,cars[i].x,cars[i].y,cars[i].horizontal,cars[i].big);
        i++;
    }
    fclose(fpsrc);
}

int load(carr cars[24],int *level){
    int success;
    FILE *fp;
    fp=fopen("save.txt","r");
    int i=0;
    if(fp==NULL){
        setfontbold(TRUE);
        setfontcolor(RED);
        printf("\n AUCUNE SAUVEGARDE !!!\n");
        printf("Appuyez sur n'importe quelle touche ...");
        resetcolors();
        while(getch()=='\0');
        success=0;
    }
    else{
        fscanf(fp,"%d",level);
        while(i<18){
            fscanf(fp,"%d %d %d %d %d %d",&cars[i].idx,&cars[i].color,&cars[i].x,&cars[i].y,&cars[i].horizontal,&cars[i].big);
            i++;
        }
        success=1;
    }
    fclose(fp);
    return success;
}
void username(char *username){
    clrscr();
    setbgrcolor(BLACK);
    setfontcolor(BRIGHTMAGENTA);
    gotoxy(10,15);
    printf("\nUsername: ");
    scanf("%s",username);
}

void get_best_scores(score bestscores[LEVELMAX]){
    FILE *fp;
    fp=fopen("scores.txt","r");
    char default_user[24]="00";
    int i=0;
    int j=0;
    if(fp==NULL){
        while(i<LEVELMAX){
            while(j<25){
                bestscores[i].user[j]=default_user[j];
                j++;
            }
            bestscores[i].shots=0;
            i++;
        }
    }else{
        i=0;
        while(i<LEVELMAX){
            fscanf(fp,"%s %d",bestscores[i].user,&bestscores[i].shots);
            i++;
        }
        fclose(fp);
    }
}
void save_best_scores(score bestscores[LEVELMAX]){
    FILE *fpsrc;
    int i=0;
    fpsrc= fopen("scores.txt","w");
    while(i<LEVELMAX){
        fprintf(fpsrc,"%s %d\n",bestscores[i].user,bestscores[i].shots);
        i++;
    }
    ///fprintf(fpsrc,"%d",level);
    fclose(fpsrc);
}

void check_best_score(score bestscores[LEVELMAX],char user[24],int shots,int level){
    score bestscore=bestscores[level-1];
    int i=0;
    if(bestscore.shots<shots){
        while(i<25){
            bestscores[level-1].user[i]=user[i];
            i++;
        }
        bestscores[level-1].shots=shots;
    }

}

void aff_bestscores(score bestscores[LEVELMAX]){
    gotoxy(30,2);
    printf("\t==BESTSCORES==");
    int i=0;
    while(i<LEVELMAX){
        gotoxy(30,3+i);
        printf("level %d:  ",i+1);
        printf("%s\t",bestscores[i].user);
        printf("%d",bestscores[i].shots);
        i++;
    }
    gotoxy(0,12);
}

void delai(int nbsecondes) { 
  /* Calcul: chaque système définit le nombre de périodes
   * d'horloge par seconde
   * La fonction clock() renvoie le temps en nombre de périodes
   * d'horloge (ou clock ticks)
   */
  int pause = nbsecondes*CLOCKS_PER_SEC;

  /* Mémorisation de l'heure de départ */
  clock_t start_time = clock(); 

  /* On boucle tant que la temporisation n'est pas atteinte */
  while (clock() < start_time + pause); 
}

void replay(int tab[255][6][6],int ncoups){
    int shot=0;
    for ( shot = 0; shot <= ncoups; shot++)
    {
        clrscr();
        plateau(tab[shot]);
        delai(1);
    }
    printf("\n GG");
    while(getch()!='q');

}

void screenshot(int tab[6][6]){
    FILE *fpsrc;
    int i;
    int j;
    fpsrc= fopen("screen.ppm","w");
    fprintf(fpsrc,"P3\n");
    fprintf(fpsrc,"6 6\n");
    fprintf(fpsrc,"255\n");
    for(i=0; i<6;i++){
        for(j=0; j<6;j++){
            if(tab[i][j]==0)
                fprintf(fpsrc,"0 0 0\n");
            else
                fprintf(fpsrc,"255 0 0\n");
        }
    }
        
    ///fprintf(fpsrc,"%d",level);
    fclose(fpsrc);
}