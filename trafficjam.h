#ifndef __TRAFFICJAM_H
#define __TRAFFICJAM_H
#define LEVELMAX 7

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

char menu(void);
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
void get_best_scores(score bestscores[LEVELMAX]);
void save_best_scores(score bestscores[LEVELMAX]);
void check_best_score(score bestscores[LEVELMAX],char user[24],int shots,int level);
void aff_bestscores(score bestscores[LEVELMAX]);
void load_level(int level, carr cars[24]);
void replay(int tab[255][6][6],int ncoups);
void save_replay(int tab[255][6][6],int ncoups);
void load_replay(int tab[255][6][6],int *ncoups);
void delai(int nbsecondes);
void screenshot(int tab[6][6]);
void reset(int tab[255][6][6]);
void createcar_edit(int x,int y,int horizontal,int big,int index,carr carss[24], int carcolor);
int createcar_final(int x,int y,int horizontal,int big,int index,carr carss[24],int carcolor);
void move_edit(carr cars[24],int* caridx,char key, carr cars2[24]);
void editeur(void);
#endif
