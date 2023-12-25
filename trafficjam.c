#include <stdio.h>
#include "console.h"
#include "trafficjam.h"
#include <time.h> 


/**
 * @brief affiche le menu et renvoi le choix voulu
 * 
 * @return char 
 */
char menu(void){
    clrscr();
    gotoxy(0,10);
    settitle("=====MENU=====");
    printf("1. JOUER\n2. LANCER LE DERNIER REPLAY\n3. EDITEUR DE NIVEAU");
    char choix;
    do{
        choix= getch();
    }
    while(choix!='1' && choix!='2' && choix!='3');
    return choix;
}
/**
 * @brief affiche le plateau avec la couleur correspondante à chaque case du plateau
 * 
 * @param tab 
 */
void plateau(int tab[6][6]) {
    hidecursor();
    int nl=0;
    int nc=0;
    setbgrcolor(BLACK);
    clrscr();
    setbgrcolor(90);
    setfontcolor(90);
    printf("\n | -  -  -  -  -  - | \n");
    setbgrcolor(BLACK);
    for(nl=0; nl<6;nl++){
        setbgrcolor(90);
        setfontcolor(90);
            printf(" |");
            setbgrcolor(BLACK);
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
            printf(" > \n");
        else{
            setfontcolor(90);
            setbgrcolor(90);
            printf("| \n");
            setbgrcolor(90);
        }
            
    }
    setfontcolor(90);
    setbgrcolor(90);
    printf(" | -  -  -  -  -  - | ");
    setbgrcolor(BLACK);
    printf("\n\n");
    setfontbold(TRUE);
    setfontcolor(RED);
    printf("appuyez sur q pour quitter.\n");
    resetcolors();
    setfontbold(FALSE);
    setbgrcolor(BLACK);
}
/**
 * @brief initialise le plateau en y assignant chaque couleur correspondante à la voiture présente sur cette case
 * 
 * @param tab 
 * @param cars 
 * @return int 
 */
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

/**
 * @brief crée une voiture de coordonée x,y d'orientation horizontal si 1 sinon vertical
 * 
 * @param x 
 * @param y 
 * @param horizontal 
 * @param big 
 * @param index 
 * @param carss 
 * @param countshots 
 * @param carcolor 
 */

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
/**
 * @brief  renvoie 1 si l'utilisateur a gagné la partie
 * 
 * @param cars 
 * @return int 
 */
int analyse(carr cars[24]){
    int gagne;
    if(cars[0].x==5-cars[0].big && cars[0].y==2)
        gagne=1;
    else
        gagne=0;
    return gagne;
}
/**
 * @brief déplace la voiture à gauche
 * 
 * @param cars 
 * @param caridx 
 * @param ncoups 
 */
void hkey(carr cars[24], int caridx,int* ncoups){
    if(cars[caridx].x!=0 && cars[caridx].horizontal)
        createcar(cars[caridx].x-cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}
/**
 * @brief déplace la voiture à droite
 * 
 * @param cars 
 * @param caridx 
 * @param ncoups 
 */
void lkey(carr cars[24], int caridx,int* ncoups){
    if(caridx==0)
        createcar(cars[caridx].x+cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
    else if(cars[caridx].x!=4-cars[caridx].big && cars[caridx].horizontal)
        createcar(cars[caridx].x+cars[caridx].horizontal,cars[caridx].y,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}
/**
 * @brief déplace la voiture en haut
 * 
 * @param cars 
 * @param caridx 
 * @param ncoups 
 */
void kkey(carr cars[24], int caridx,int* ncoups){
    if(cars[caridx].y!=0 && cars[caridx].horizontal==0)
        createcar(cars[caridx].x,cars[caridx].y-1,cars[caridx].horizontal,cars[caridx].big,caridx,cars,ncoups,cars[caridx].color);
}
/**
 * @brief déplace la voiture en bas
 * 
 * @param cars 
 * @param caridx 
 * @param ncoups 
 */
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

/**
 * @brief ouvre le fichier correspondant au niveau voulu et le charge dans le tableau de voiture cars
 * 
 * @param level 
 * @param cars 
 */
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

/**
 * @brief passe au niveau suivant et charge le prochain niveau
 * 
 * @param cars 
 * @param level 
 */
void nextlevel(carr cars[24],int* level){
    *level+=1;
    if(*level<LEVELMAX+1)
        load_level(*level,cars);

}
/**
 * @brief affiche l'aide 
 * 
 */
void affhelp(void){
    setbgrcolor(BLACK);
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
    printf("w/W: changer de voiture");
    gotoxy(30,9);
    printf("p: afficher les meilleurs scores");
    gotoxy(30,10);
    printf("r: reset le niveau en cours");
    gotoxy(30,11);
    printf("s: prendre un screenshot");
    gotoxy(0,12);
}

/**
 * @brief sauvegarde la partie en cours dans un fichier save.txt
 * 
 * @param cars 
 * @param level 
 */
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
/**
 * @brief charge la sauvegarde du fichier save.txt dans le tableau de voiture
 * 
 * @param cars 
 * @param level 
 * @return int 
 */
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

/**
 * @brief demande de saisir le psoeudo et le stock dans username
 * 
 * @param username 
 */
void username(char *username){
    clrscr();
    setbgrcolor(BLACK);
    setfontcolor(BRIGHTMAGENTA);
    gotoxy(10,15);
    printf("\nUsername: ");
    scanf("%s",username);
}

/**
 * @brief obtient les meilleurs scores écris dans le fichier scores.txt et les stock dans le tableau des scores
 * 
 * @param bestscores 
 */
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

/**
 * @brief sauvegarde les meilleurs scores dans le fichier scores.txt
 * 
 * @param bestscores 
 */
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

/**
 * @brief vérifie si l'utilisateur "user" a effectué un meilleur score que celui présent dans le tableau des meilleurs scores et si oui le remplace
 * 
 * @param bestscores 
 * @param user 
 * @param shots 
 * @param level 
 */
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
/**
 * @brief affiche les meilleurs scores
 * 
 * @param bestscores 
 */
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
/**
 * @brief crée un temps délai de nbsecondes
 * 
 * @param nbsecondes 
 */
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
/**
 * @brief affiche le replay du niveau gagné stocké dans tab
 * 
 * @param tab 
 * @param ncoups 
 */
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

/**
 * @brief sauvegarde le replay tab dans un fichier replay.txt
 * 
 * @param tab 
 * @param ncoups 
 */
void save_replay(int tab[255][6][6],int ncoups){
    FILE *fpsrc;
    int shot=0;
    fpsrc= fopen("replay.txt","w");
    fprintf(fpsrc,"%d\n",ncoups);
    while(shot<ncoups){
        for(int i=0; i<6;i++){
            for(int j=0; j<6;j++){
                fprintf(fpsrc,"%d ",tab[shot][i][j]);
            }
            fprintf(fpsrc,"\n");
        }
        fprintf(fpsrc,"\n\n");
        shot++;
    }
    ///fprintf(fpsrc,"%d",level);
    fclose(fpsrc);
}
/**
 * @brief charger le replay sauvegarder dans replay.txt dans le tableau tab
 * 
 * @param tab 
 * @param ncoups 
 */
void load_replay(int tab[255][6][6],int *ncoups){
    FILE *fp;
    int shot=0;
    fp= fopen("replay.txt","r");
    if(fp==NULL){
        setfontbold(TRUE);
        setfontcolor(RED);
        printf("\n AUCUNE SAUVEGARDE !!!\n");
        printf("Appuyez sur n'importe quelle touche ...");
        resetcolors();
        while(getch()=='\0');
    }
    else{
        fscanf(fp,"%d",ncoups);
        while(shot<*ncoups){
            for(int i=0; i<6;i++){
                for(int j=0; j<6;j++){
                    fscanf(fp,"%d",&tab[shot][i][j]);
                }
            }
            shot++;
    }
    }
    ///fprintf(fpsrc,"%d",level);
    fclose(fp);
}
/**
 * @brief prend un screenshot du tableau actuel et le sauvegarde dans le fichier screen.ppm
 * 
 * @param tab 
 */
void screenshot(int tab[6][6]){
    FILE *fpsrc;
    int i;
    int j;
    int color;
    fpsrc= fopen("screen.ppm","w");
    fprintf(fpsrc,"P3\n");
    fprintf(fpsrc,"6 6\n");
    fprintf(fpsrc,"255\n");
    for(i=0; i<6;i++){
        for(j=0; j<6;j++){
            color=tab[j][i];
            if(color==0)
                fprintf(fpsrc,"0 0 0");
            else{
                switch (color)
                {
                case RED:
                    fprintf(fpsrc,REDRGB);
                    break;
                case BLUE:
                    fprintf(fpsrc,BLUERGB);
                    break;
                case GREEN:
                    fprintf(fpsrc,GREENRGB);
                    break;
                case YELLOW:
                    fprintf(fpsrc,YELLOWRGB);
                    break;
                case MAGENTA:
                    fprintf(fpsrc,MAGENTARGB);
                    break;
                case CYAN:
                    fprintf(fpsrc,CYANRGB);
                    break;
                case WHITE:
                    fprintf(fpsrc,WHITERGB);
                    break;
                case BRIGHTWHITE:
                    fprintf(fpsrc,BWHITERGB);
                    break;
                case BRIGHTRED:
                    fprintf(fpsrc,BREDRGB);
                    break;
                case BRIGHTMAGENTA:
                    fprintf(fpsrc,BMAGENTARGB);
                    break;
                case BRIGHTBLUE:
                    fprintf(fpsrc,BBLUERGB);
                    break;
                case BRIGHTYELLOW:
                    fprintf(fpsrc,BYELLOWRGB);
                    break;
                case BRIGHTGREEN:
                    fprintf(fpsrc,BGREENRGB);
                    break;
                default:
                    fprintf(fpsrc,"128 128 0");
                    break;
                }
                
            }
            fprintf(fpsrc,"\n");
        }
    }
    fclose(fpsrc);
}
/**
 * @brief remet toutes les valeures du tableau replay à 0
 * 
 * @param tab 
 */
void reset(int tab[255][6][6]){
    for (int i = 0; i < 255; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                tab[i][j][k]=0;
            }
            
        }
        
    }
    
}

/**
 * @brief crée une voiture aux coordonnés x,y d'orientation définie par horizontal de taille par big et de couleur par carcolor et ce sans collisions
 * 
 * @param x 
 * @param y 
 * @param horizontal 
 * @param big 
 * @param index 
 * @param carss 
 * @param carcolor 
 */
void createcar_edit(int x,int y,int horizontal,int big,int index,carr carss[24], int carcolor) {

    int i= index;
    carss[i].color=carcolor;
    carss[i].x=x;
    carss[i].y=y;
    carss[i].horizontal=horizontal;    
    carss[i].big=big;
    
}
/**
 * @brief crée une voiture  aux coordonnées x,y d'orientation définie par horizontal de taille par big et de couleur par carcolor et ce seulement si il n'y a pas de voiture déjà présente à ces coordonnés
 * 
 * @param x 
 * @param y 
 * @param horizontal 
 * @param big 
 * @param index 
 * @param carss 
 * @param carcolor 
 * @return int 
 */
int createcar_final(int x,int y,int horizontal,int big,int index,carr carss[24],int carcolor) {
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
    int i= index;
    if(exist==0){
        carss[i].color=carcolor;
        carss[i].x=x;
        carss[i].y=y;
        carss[i].horizontal=horizontal;    
        carss[i].big=big;
    }
    return exist;
    
}
/**
 * @brief déplace la voiture dans l'éditeur d'indice caridx selon la touche key appuyé et ce sans prendre en compte l'orientation de celle-ci
 * 
 * @param cars 
 * @param caridx 
 * @param key 
 * @param cars2 
 */
void move_edit(carr cars[24],int* caridx,char key, carr cars2[24]){
    int color= (*caridx%7)+31;
    switch (key)
    {
    case 'h':
        if(cars[*caridx].x!=0)
            createcar_edit(cars[*caridx].x-1,cars[*caridx].y,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars,cars[*caridx].color);
        break;
    case 'l':
        if((cars[*caridx].x!=4-cars[*caridx].big && cars[*caridx].horizontal) || (cars[*caridx].x!=5 && cars[*caridx].horizontal==0))
            createcar_edit(cars[*caridx].x+1,cars[*caridx].y,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars,cars[*caridx].color);
            break;
    case 'k':
        if(cars[*caridx].y!=0 )
            createcar_edit(cars[*caridx].x,cars[*caridx].y-1,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars,cars[*caridx].color);
        break;
    case 'j':
        if(cars[*caridx].y!=4-cars[*caridx].big)
            createcar_edit(cars[*caridx].x,cars[*caridx].y+1,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars,cars[*caridx].color);
        break;
    case 'b':
        cars[*caridx].big=!cars[*caridx].big;
        break;
    case 'v':
        cars[*caridx].horizontal=!cars[*caridx].horizontal;
        break;
    case 'w':
        if(!createcar_final(cars[*caridx].x,cars[*caridx].y,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars,cars[*caridx].color)){
            createcar_edit(cars[*caridx].x,cars[*caridx].y,cars[*caridx].horizontal,cars[*caridx].big,*caridx,cars2,cars[*caridx].color);
            *caridx+=1;
            createcar_edit(0,0,0,0,*caridx,cars,color);
        }
    default:
        break;
    }
}
/**
 * @brief affiche l'interface de l'éditeur 
 * 
 */
void editeur(void){
    int select=1;
    int ncoups=0;
    int tab[6][6]={0};
    carr cars_edit[24];
    carr cars_final[24];
    for(int i=0; i<24;i++){
        cars_edit[i].color=BLACK;
        cars_final[i].color=BLACK;
        cars_edit[i].x=0;
        cars_final[i].x=0;
        cars_edit[i].y=0;
        cars_final[i].y=0;
        cars_edit[i].idx=i;
        cars_final[i].idx=i;
        cars_edit[i].horizontal=0;
        cars_final[i].horizontal=0;
        cars_edit[i].big=0;
        cars_final[i].big=0;
    }
    createcar_edit(0,2,1,0,0,cars_edit,RED);
    inittab(tab,cars_edit);
    clrscr();
    plateau(tab);
    printf("Appuyez sur Entrée pour valider le point de départ.");
    char key;
    do
    {
        key=getch();
        switch (key)
        {
            case 'h':
                hkey(cars_edit,0,&ncoups);
                break;
            case 'l':
                if(!analyse(cars_edit))
                    lkey(cars_edit,0,&ncoups);
                break;
        }
        inittab(tab,cars_edit);
        plateau(tab);
        printf("Appuyez sur Entrée pour valider le point de départ.");
    } while (key!='\n');
    createcar_edit(cars_edit[0].x,cars_edit[0].y,cars_edit[0].horizontal,cars_edit[0].big,cars_edit[0].idx,cars_final,cars_edit[0].color);
    createcar_edit(0,0,0,0,select,cars_edit,32);
    do
    {
        inittab(tab,cars_edit);
        plateau(tab);
        printf("Appuyez sur Entrée pour valider le niveau.\n");
        printf("Appuyez sur b pour changer la taille de la voiture\n");
        printf("Appuyez sur v pour changer l'orientation de la voiture\n");
        printf("Touches habituelles pour se déplacer :)\n");
        key=getch();
        move_edit(cars_edit,&select,key,cars_final);
    } while (key!='\n');
    FILE *fpsrc;
    int i=0;
    fpsrc= fopen("niveauE.txt","w");
    while(cars_final[i].color!=BLACK){
        fprintf(fpsrc,"%d %d %d %d %d %d\n",cars_final[i].idx,cars_final[i].color,cars_final[i].x,cars_final[i].y,cars_final[i].horizontal,cars_final[i].big);
        i++;
    }
    fclose(fpsrc);

}