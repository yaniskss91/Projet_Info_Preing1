#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct{
    int jour,mois;
}Date;

typedef struct{
    Date date;
    int ep;
    int temps;
    int position;
}Entrainement;

typedef struct{
    char* nom;
    Entrainement* e;
}Joueur;


char* creaAllocNom(int taille){
    char* nom = NULL;
    nom = malloc(sizeof(char) *taille);
    if(nom == NULL){
        exit(1);
    }
    return nom;
}
void verifTab(Entrainement* tab){
    if(tab == NULL){
        exit(3);
    }
}

void verifAllocFich(FILE* f){
    if(f == NULL){
        exit(2);
    }
}
int nbLigne(FILE* f){
    int nbr_ligne=1;
    char caractere;
    while((caractere=fgetc(f))!=EOF){
        if(caractere=='\n'){
            nbr_ligne++;
        }
    }
    return nbr_ligne;
}
int verifDate(int max, char* nom, int val){
    while((val<1)|| (val>max)){
        printf("Quelle est %s de l'entra�nement ?\n", nom);

        if(nom == "l'epreuve"){
            printf("1: 100m\n 2: 400m\n 3: 5000m\n 4: Marathon\n 5: Relais\n");
        }

        printf("\n\nReponse : ");
        scanf("%d", &val);
        printf("\033[H\033[2J");

        if((val<1)|| (val>max)){
            printf("Saisissez une valeur correcte.\n");
        }
    }
    return val;
}

int nbAthlete(FILE* f){
    int taille=1;
    char caractere;
    while((caractere=fgetc(f))!=EOF){
        if(caractere==' '){
            taille++;
        }
    }
    return taille;
}
Entrainement* creationTabE(FILE* f, int taille){
    Entrainement* tab = NULL;
    tab = malloc(sizeof(Entrainement)*taille);
    verifTab(tab);

    Entrainement e;

    rewind(f);
    for(int i=0; i<taille; i++){
        fscanf(f, "%d %d %d %d", &e.date.jour, &e.date.mois, &e.ep, &e.temps);
        tab[i] = e;
    }

    return tab;
}

Joueur* creationTab(){
    char* nom = creaAllocNom(50);
    char* nom2 = creaAllocNom(5);
    nom2 = ".txt";

    FILE* f = fopen("athlete.txt", "r");
    verifAllocFich(f);

    int taille = nbAthlete(f), taille2;

    Joueur* tab = NULL;
    tab = malloc(sizeof(Joueur)*taille);
    if(tab==NULL){
        exit(3);
    }

    rewind(f);

    FILE* f2 = NULL;
    for(int i=0; i<taille; i++){
        tab[i].nom = creaAllocNom(50);

        fscanf(f, "%s",tab[i].nom);
        strcpy(nom, tab[i].nom);
        strcat(nom, nom2);

        f2 = fopen(nom, "r");
        verifAllocFich(f2);

        taille2 = nbLigne(f2);

        tab[i].e = creationTabE(f2, taille2);

        fclose(f2);
    }

    fclose(f);
    return tab;
}




char verif_r(char nom[50], char r){
    while((r!='o') &&(r!='n')){
        printf("%s", nom);
        scanf(" %c", &r);
        printf("\033[H\033[2J");
    }
    return r;
}
int verif1(char* nom){
    char* r = creaAllocNom(20);
    printf("Souhaitez vous activer le filtre <<%s>> ? (o/n)\n\nR�ponse :", nom);
    scanf(" %s", r);
    printf("\033[H\033[2J");

    while(((r[0]!='o') && (r[1]!='\0'))||(r[0]!='n') && (r[1]!='\0')){
        printf("Souhaitez vous activer le filtre <<%s>> ? (o/n)\n\nR�ponse :", nom);
        scanf(" %s", r);
        printf("\033[H\033[2J");
    }
    if(r[0]=='o'){
        return 1;
    }else{
        return 0;
    }
}
int verif2(char* nom, int val){
    if(val==0){
        printf("Saisissez une valeur correcte !\n");
    }
    else{
        printf("Le filtre %s a bien �t� enlev�\n", nom);

    }
    return 0;
}

int verifNom(int taille, char* nom, Joueur* tab){
    for(int i=0; i<taille; i++){
        if(strcmp(tab[i].nom, nom)==0){
            return i;
        }else if(i==taille-1){
            printf("verifier l'orthographe.");
            printf("\033[H\033[2J");
            return -1;
        }
    }
}

void historique(Joueur * tab, int taille, int val1, int val2, int val3){
    int taille2, i, v = 0;
    char* nom = creaAllocNom(50);
    Entrainement e;

    FILE* f = NULL;
    f = fopen("athlete.txt", "r");
    verifAllocFich(f);

    FILE* f2 = NULL;
    e.ep = 0;

    if(val1 == 1){
        fclose(f);
        while(v == 0){
            printf("quel athlete ?\n\nReponse : ");
            scanf("%s", nom);
            printf("\033[H\033[2J");
            i = verifNom(taille, nom, tab);
            if(i != -1){
                sprintf(nom,"%s.txt",nom);

                f = fopen(nom, "r");
                verifAllocFich(f);

                taille2 = nbLigne(f);
                printf("%d", taille2);
                if(val2 == 1){
                    e.date.jour = verifDate(31, "le jour", 0);
                    e.date.mois = verifDate(12, "le mois", 0);
                    if(val3 == 1){
                        e.ep = verifDate(5, "l'epreuve", 0);
                    }
                    for(int a=0; a<taille2; a++){
                        if(e.date.jour==tab[i].e[a].date.jour && e.date.mois==tab[i].e[a].date.mois){
                            if(e.ep == tab[i].e[a].ep){
                                printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                            }
                            else{
                                printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                            }
                        }
                    }
                }
                else if(val3 == 1){
                    e.ep = verifDate(5, "l'epreuve", 0);
                    for(int a=0; a<taille2; a++){
                        if(e.ep == tab[i].e[a].ep){
                            printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                        }
                    }
                }
                else{
                    for(int j=0; j<taille2; j++){
                        printf("%d/%d %d %ds\n", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                    }
                }
                v = 1;
            }else{
                printf("V�rifier l'arthographe\n\n");
                v = 0;
            }
            printf("\n");
        }
    }else if(val2 == 1){
        e.date.jour = verifDate(31, "le jour", 0);
        e.date.mois = verifDate(12, "le mois", 0);
        if(val3 == 1){
            e.ep = verifDate(5, "l'epreuve", 0);
        }
        for(int i=0; i<taille; i++){
            sprintf(nom,"%s.txt",tab[i].nom);
            f2 = fopen(nom, "r");
            verifAllocFich(f2);

            taille2 = nbLigne(f2);
            fclose(f2);

            for(int j=0; j<taille2; j++){
                if(e.date.jour==tab[i].e[j].date.jour && e.date.mois==tab[i].e[j].date.mois){
                    if(e.ep == tab[i].e[j].ep){
                        printf("%s\n", tab[i].nom);
                        printf("%d/%d %d %ds\n", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                    }
                    else{
                        printf("%s\n", tab[i].nom);
                        printf("%d/%d %d %ds\n", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                    }
                }
            }
            printf("\n");
        }
    }else if(val3 == 1){
        e.ep = verifDate(5, "l'epreuve", 0);
        for(int i=0; i<taille; i++){
            sprintf(nom,"%s.txt",tab[i].nom);

            f2 = fopen(nom, "r");
            verifAllocFich(f2);

            taille2 = nbLigne(f2);
            fclose(f2);
            for(int a=0; a<taille2; a++){
                if(e.ep == tab[i].e[a].ep){
                    printf("%s\n", tab[i].nom);
                    printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                }
            }
            printf("\n");
        }
    }else{
        printf("vous revenez en arri�re\n\n");
    }
}

void menu(Joueur* tab){
    printf("\033[H\033[2J");
    int n=0, taille, taille2, v = 0, x, xathlete = 0, xepreuve=0, xdate=0;
    int xresume = 0, xenvoie = 0, xprogre = 0;

    FILE* f = fopen("athlete.txt", "r");
    verifAllocFich(f);
    FILE* f2 = NULL;
    taille = nbAthlete(f);
    fclose(f);

    char* nom = creaAllocNom(50);// marche peut pas pour sprintf ligne 48
    char r='O', r2='o';

    while(n!=4){
        printf("Que souhaitez vous faire ?\n 1: Ajouter un entrainement\n 2: Afficher l'historique des entrainements\n 3: Consulter des statistiques\n 4: Quitter le programme\n\n Reponse :  ");
        scanf("%d", &n);
        printf("\033[H\033[2J");

        switch(n){
            /*case 1:
                while(v == 0){
                    printf("Pour quel athlete ?\n\nReponse : ");
                    scanf("%s", nom);
                    printf("\033[H\033[2J");

                    for(int i=0; i<taille; i++){
                        if(strcmp(tab[i].nom, nom)==0){
                            sprintf(nom,"%s.txt",nom);

                            f = fopen(nom, "a+");
                            verifAllocFich(f);

                            taille2 = nbLigne(f);

                            ajoutEntrainement(f, tab[i].e, taille2);

                            i = taille;
                            v = 1;
                        }else if(i==taille-1){
                            printf("verifier l'orthographe(n'oublier pas la majuscule)\n");
                            v = 0;
                        }
                    }
                }

                break;*/

            case 2:
                r='O';
                r2='o';
                while((r=='O') || (r=='o')){
                    x=0;
                    while((x<1) || (x>4)){
                        printf("Quel filtre voulez-vous mettre ?\n1: Athl�te\n2: Date\n3: Epreuve\n4: retour\n\nR�ponse : ");
                        scanf("%d", &x);
                        printf("\033[H\033[2J");
                    }

                    switch (x){
                        case 1:
                            xathlete = verif1("athlete");
                            break;
                        case 2:
                            xdate = verif1("date");
                            break;
                        case 3:
                            xepreuve = verif1("epreuve");
                            break;
                        case 4:
                            xathlete = 0;
                            xepreuve  = 0;
                            xdate = 0;
                            r = 'n';
                            r2 = 'n';
                            break;
                    }
                    if(x != 4){
                        printf("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :");
                        scanf(" %c", &r);
                        r = verif_r("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :", r);
                        printf("\033[H\033[2J");
                    }

                }
                if(x != 4){
                    printf("Voici les filtres activ�s : \n");
                    if(xathlete==1){
                        printf("Athlete\n");
                    }
                    if(xdate==1){
                        printf("Date\n");
                    }
                    if (xepreuve==1){
                        printf("Epreuve\n");
                    }

                    printf("Souhaitez-vous desactiver un filtre ? (o/n)\n\nR�ponse : ");
                    scanf(" %c", &r2);
                    r2 = verif_r("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :", r2);
                    printf("\033[H\033[2J");
                }
                while((r2=='o') || (r2=='O')){
                    x=0;
                    printf("Quel filtre souhaitez-vous d�sactiver ?\n");
                    if (xathlete==1){
                        printf("1: Athlete\n");
                    }
                    if (xdate==1){
                        printf("2: Date\n");
                    }
                    if (xepreuve==1){
                        printf("3: Epreuve\n");
                    }
                    printf("4: Aucun\n");
                    printf("\n\nReponse :");
                    scanf("%d", &x);
                    printf("\033[H\033[2J");
                    switch (x){
                        case 1:
                            xathlete = verif2("Athlete", xathlete);
                            break;

                        case 2:
                            xdate = verif2("Date", xdate);
                            break;

                        case 3:
                            xepreuve = verif2("Epreuve", xepreuve);
                            break;

                        case 4 :
                            printf("Aucun filtre n'a �t� enlev�\n");
                            r2 = n;
                            break;

                        default :
                            printf("Saisissez une valeur correcte\n");
                            break;
                    }
                    if(x!=1&&x!=2&&x!=3&&x!=4){
                        printf("Souhaitez-vous enlever un autre filtre ? (o/n)\n\nReponse :");
                        scanf(" %c", &r2);
                        r2 = verif_r("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :", r2);
                        printf("\033[H\033[2J");
                    }
                }
                historique(tab, taille, xathlete, xdate, xepreuve);

                break;

/*
            case 3:
                xresume = 0;
                xenvoie = 0;
                xprogre = 0;
                while((r=='O') || (r=='o')){
                    x=0;
                    while((x<1) || (x>3)){
                        printf("Que voulez savoir ?\n1: R�sumer d'un athl�te\n2: Qui envoier au JO\n3: La progression d'un atl�te\n\nR�ponse : ");
                        scanf("%d", &x);
                        printf("\033[H\033[2J");
                    }

                    switch (x){
                        case 1:
                            while(r2=='o'){
                                printf("Quel athl�te ?\n\nReponse: ");
                                scanf(" %s", nom);
                                int i = verifNom(taille1, nom, tab);
                                xepreuve = 0;

                                if(i != -1){
                                    sprintf(nom,"%s.txt",nom);
                                    f2 = fopen(nom, "r");
                                    if(f2 == NULL){
                                        exit(1);
                                    }

                                    taille2 = nbLigne(f2);
                                    while((xepreuve<1)||(xepreuve>5)){
                                        printf("\033[H\033[2J");
                                        printf("Quelle �preuve ?\n1: 100m\n 2: 400m\n 3: 5000m\n 4: Marathon\n 5: Relais\n\nReponse: ");
                                        scanf("%d", &xepreuve);
                                    }
                                    int taille3 = 0;
                                    for(int j=0; j<taille2; j++){
                                        if(tab[i].e[j].ep == xepreuve){
                                            taille3++;
                                        }
                                    }
                                    if(taille3 != 0){
                                        int* tabTmps = malloc(taille3 * sizeof(int));
                                        if (tabTmps == NULL) {
                                            printf("Erreur d'allocation de m�moire\n");
                                            exit(1);
                                        }
                                        tabTmps = tabTemps(tab[i].e, taille2, taille3, xepreuve);
                                        float moy = moyenne(tabTmps, taille3);
                                        triRapide(tabTmps, taille3);
                                        printf("\033[H\033[2J");
                                        printf("%s\n", tab[i].nom);
                                        printf("meilleur temps : %d\n", tabTmps[0]);
                                        printf("pire temps : %d\n", tabTmps[taille3-1]);
                                        printf("temps moyen : %fs\n", moy);

                                    }else{
                                        printf("l'athl�te n'a pas fait d'entrainement pour cette �preuve.\n");
                                    }
                                    r2 = 'n';
                                }else{
                                    printf("verifier l'orthographe\n");
                                }
                            }
                            r = 'n';

                            break;
                        case 2:

                            break;
                        case 3:

                            break;
                    }
                }

                break;*/

            default:
                printf("Veuillez saisir une valeur comprise entre 1 et 4\n\n");
                break;
        }
    }
}

int main(){
    printf("\033[H\033[2J");
    Joueur* tab = creationTab();
    menu(tab);
    return 0;
}
