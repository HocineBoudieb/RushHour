#include <stdio.h>
#include <assert.h>
#include "console.h"
#include "trafficjam.h"


int main(void) {
    setbgrcolor(BLACK);
    settitle("===TRAFFIC JAM===");
    char user[25];
    int change=0;
    int help=FALSE;
    int is_score=FALSE;
    int ncars;
    char appui2;
    int ncoups=0;
    carr cars[24];
    int tab[6][6]={0};
    int tab_replay[255][6][6]={0};
    char touche;
    int caridx=0;
    int gagnant=0;
    int niveau=1;
    score bestscores[2];
    get_best_scores(bestscores);
    username(user);
    printf("%s",user);
    resetcolors();
    for(int i=0; i<24;i++){
        cars[i].color=BLACK;
        cars[i].x=0;
        cars[i].y=0;
        cars[i].idx=i;
        cars[i].horizontal=0;
        cars[i].big=0;
    }
    clrscr();
    printf("Voulez vous charger une partie?(o/n)");
    do{
        touche=getch();
    }while (touche!='n' && touche!='o');
    if(touche=='o'){
        if(!load(cars,&niveau))
            load_level(1,cars);
    }
    else{
        load_level(1,cars);
    }
    clrscr();
    ncars=inittab(tab,cars);
    plateau(tab);
    printf("\n selection : \t");
    setbgrcolor(cars[caridx].color);
    printf("□");
    setbgrcolor(BLACK);
    printf("\n nombre de coups: %d",ncoups);
    char appui=getch();
    while (appui != 'q' && niveau<LEVELMAX+1){
        change=1;
        switch (appui){
            case 'w':
                caridx++;
                break;
            case 'h':
                hkey(cars,caridx,&ncoups);
                break;
            case 'j':
                jkey(cars,caridx,&ncoups);
                break;
            case 'k':
                kkey(cars,caridx,&ncoups);
                break;
            case 'l':
                lkey(cars,caridx,&ncoups);
                break;
            case 'r':
                load_level(niveau,cars);
                ncoups=0;
                break;
            case 's':
                screenshot(tab);
                change=0;
                break;
            case 'H':
                if(help){
                    clrscr();
                    plateau(tab);
                    setfontbold(TRUE);
                    printf("\n nombre de coups: %d",ncoups);
                    setfontbold(FALSE);
                    help=FALSE; 
                }          
                else if(is_score==FALSE){
                    affhelp();
                    help=TRUE;
                }
                change=0;
                break;
            case 'p':
                if(is_score){
                    clrscr();
                    plateau(tab);
                    setfontbold(TRUE);
                    printf("\n nombre de coups: %d",ncoups);
                    setfontbold(FALSE);
                    is_score=FALSE; 
                }else if(help==FALSE){
                    aff_bestscores(bestscores);
                    is_score=TRUE;
                }
                change=0;
                break;
            default:
                change=0;
        }
        if(caridx==ncars)
            caridx=0;
        if(change){
            for(int line=0;line<6;line++){
                for (int col = 0; col < 6; col++)
                {
                    tab_replay[ncoups][line][col]=tab[line][col];
                }
                
            }
            gagnant=analyse(cars);
            ncars=inittab(tab,cars);   
            plateau(tab);
            printf("\n selection : \t");
            setbgrcolor(cars[caridx].color);
            printf("□");
            setbgrcolor(BLACK);
            if(help)
                affhelp(); 
            setfontbold(TRUE);
            printf("\n nombre de coups: %d",ncoups);
            setfontbold(FALSE);
        }
        if(gagnant){
            check_best_score(bestscores,user,ncoups,niveau);
            save_best_scores(bestscores);
            if(niveau<LEVELMAX){
                clrscr();
                nextlevel(cars,&niveau);
                gotoxy(17,5);
                printf("\nBRAVO vous avez gagner en %d coups \nappuyez sur n pour passer au prochain level\nAppuyez sur r pour replay \nAppuyez sur q pour quitter\n", ncoups);
                appui2=getch();
                while(appui2!='q' && appui2!='n' && appui2!='r')
                    appui2=getch();
                if(appui2=='r'){
                    replay(tab_replay,ncoups);
                    printf("\nnappuyez sur n pour passer au prochain level\nAppuyez sur q pour quitter\n");
                    while(appui2!='q' && appui2!='n')
                        appui2=getch();
                }   
                if(appui2=='q')
                    appui=appui2;
                
                ncoups=0;
            }
            else
                niveau++;
        }else{
            appui=getch();
        }   
        
    }
    clrscr();
    if(niveau==LEVELMAX+1){
        gotoxy(17,5);
        printf("\nBRAVO vous avez gagner en %d coups \nappuyez sur q pour quitter\n", ncoups);
        while(getch()!='q');
    }
    else{
        gotoxy(10,10);
        do{
            printf("\n voulez vous sauvegarder la progression ?(o/n)\n");
            touche=getch();
        }while (touche!='n' && touche!='o');
        if(touche=='o')
            save(cars,niveau);
    }
    unhidecursor();
    clrscr();
    return 0;
}


