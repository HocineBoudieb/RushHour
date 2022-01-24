#ifndef __TRAFFICJAM_H
#define __TRAFFICJAM_H
#define LEVELMAX 4

typedef struct scores{
    char user[24];
    int shots;
}score;

typedef struct toy{
    int idx;
    int color;
    int x;
    int y;
    int horizontal;
    int big;
}carr;

void createcar(int x,int y,int horizontal,int big,int index,carr carss[24],int* countshots,int carcolor);
void plateau(int tab[6][6]);
int inittab(int tab[6][6],carr cars[24]);
int analyse(carr cars[24]);
void hkey(carr cars[24], int caridx,int* ncoups);
void lkey(carr cars[24], int caridx,int* ncoups);
void jkey(carr cars[24], int caridx,int* ncoups);
void kkey(carr cars[24], int caridx,int* ncoups);
void niveau1(carr cars[24]);
void niveau2(carr cars[24]);
void nextlevel(carr cars[24], int* level);
void affhelp(void);
void save(carr cars[24], int level);
int load(carr cars[24], int* level);
void username(char *username);
void get_best_scores(score bestscores[2]);
void save_best_scores(score bestscores[2]);
void check_best_score(score bestscores[2],char user[24],int shots,int level);
void aff_bestscores(score bestscores[2]);
void load_level(int level, carr cars[24]);
void replay(int tab[255][6][6],int ncoups);
void delai(int nbsecondes);
void screenshot(int tab[6][6]);
#endif
