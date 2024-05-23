#include<stdio.h>
#include<time.h>
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


Entrainement* creationTabE(FILE* f, int nbLignes){
    Entrainement* tab = NULL;
    Entrainement e;

    tab = malloc(sizeof(Entrainement)*nbLignes);
    if(tab == NULL){
        exit(2);
    }

    rewind(f);
    for(int i=0; i<nbLignes; i++){
        fscanf(f, "%d %d %d %d", &e.date.jour, &e.date.mois, &e.ep, &e.temps);
        tab[i] = e;
    }
    return tab;
}


Joueur* creationTab(){
    Joueur* tab = NULL;
    FILE* f=fopen("athlete.txt","r+");
    char* nom = malloc(sizeof(char) *5);
    char* nom2 = malloc(sizeof(char) *50);
    nom = ".txt";
    
    if(f == NULL){
        exit(1);
    }
    int taille = nbAthlete(f), taille2;
    tab = malloc(sizeof(Joueur)*taille);
    if(tab==NULL){
        exit(2);
    }
    FILE* fi = NULL;

    rewind(f);
    

    for(int i=0; i<taille; i++){
        tab[i].nom = malloc(sizeof(char)* 50);
        fscanf(f, "%s",tab[i].nom);
        strcpy(nom2, tab[i].nom);
        strcat(nom2, nom);
        FILE* fi = fopen(nom2, "r");
        if(fi == NULL){
            printf("erreur");
            exit(3);
        }
        taille2 = nbLigne(fi);
        tab[i].e = creationTabE(fi, taille2);

        /*for(int j=0; j<taille2; j++){
            printf("%d %d %d %d\n",tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep,tab[i].e[j].temps);
        }
        fclose(fi);*/
    }


    
    fclose(f);
    return tab;
}

int verifDate(int max, char* nom, int val){
    while((val<1)|| (val>max)){
        printf("Quelle est %s de l'entraînement ?\n", nom);
        if(nom == "l'epreuve"){
            printf("1: 100m\n 2: 400m\n 3: 5000m\n 4: Marathon\n 5: Relais\n");
        }
        printf("\n\nReponse : ");
        scanf("%d", &val);
        printf("\033[H\033[2J");
        if((val<1)|| (val>max)){
            printf("Saisissez une valeur correcte.\n");
            printf("\033[H\033[2J");
        }
    }
    return val;
}

int verifNom(int taille, char nom[50], Joueur* tab){
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


void ajoutEntrainement(FILE* f, Entrainement* tab, int taille){
    Entrainement nouv;

    nouv.date.jour = verifDate(31, "jour", 0);

    nouv.date.mois = verifDate(12, "mois", 0);

    nouv.ep = verifDate(5, "l'epreuve", 0);;

    nouv.temps = -1;
    while(nouv.temps<0){
        printf("Quel temps (en seconde) ?\n\nReponse : ");
        scanf("%d", &nouv.temps);
        printf("\033[H\033[2J");
        if(nouv.temps<0){
            printf("Saisissez une valeur correcte.\n");
            printf("\033[H\033[2J");
        }
    }

    taille+=1;

    tab = realloc(tab, sizeof(Entrainement)*taille);
    if(tab == NULL){
        exit(4);
    }

    tab[taille-1] = nouv;

    fprintf(f, "\n%d %d %d %d", nouv.date.jour, nouv.date.mois, nouv.ep, nouv.temps);
}

int verif1(char* nom){
    char r2;
    printf("Souhaitez vous activer le filtre <<%s>> ? (o/n)\n\nRéponse :", nom);
    scanf(" %c", &r2);
    printf("\033[H\033[2J");
    if((r2=='o') || (r2=='O')){
       return 1;
    }
}


int verif2(char* nom, int val){
    if(val==0){
        printf("Saisissez une valeur correcte !\n");
    }
    else{
        printf("Le filtre %s a bien été enlevé\n", nom);

    }
    return 0;
}

void historique(Joueur * tab, int taille1, int val1, int val2, int val3){
    int taille, i, ver = 0, ver2 = 0;
    char nom[50];
    Entrainement e;
    FILE* f = NULL;
    FILE* f2 = NULL;
    f = fopen("athlete.txt", "r");
    if(f == NULL){
        exit(1);
    }
    e.ep = 0;
    if(val1 == 1){
        fclose(f);
        while(ver == 0){
            printf("quel athlete ?\n\nReponse : ");
            scanf("%s", nom);
            printf("\033[H\033[2J");
            i = verifNom(taille1, nom, tab);
            if(i!= -1){
                sprintf(nom,"%s.txt",nom);
                f = fopen(nom, "r");
                if(f == NULL){
                    exit(1);
                }
                taille = nbLigne(f);
                if(val2 == 1){
                    e.date.jour = verifDate(31, "le jour", 0);
                    printf("%d", e.date.jour);
                    e.date.mois = verifDate(12, "le mois", 0);
                    if(val3 == 1){
                        e.ep = verifDate(5, "l'epreuve", 0);
                    }
                    for(int a=0; a<taille; a++){
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
                    for(int a=0; a<taille; a++){
                        if(e.ep == tab[i].e[a].ep){
                            printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                        }
                    }
                }
                else{
                    for(int j=0; j<taille; j++){
                        printf("%d/%d %d %ds\n", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                    }
                }
                ver = 1;
            }else{
                ver = 0;
            }
        }
    }else if(val2 == 1){
        e.date.jour = verifDate(31, "le jour", 0);
        e.date.mois = verifDate(12, "le mois", 0);
        if(val3 == 1){
            e.ep = verifDate(5, "l'epreuve", 0);
        }
        for(int i=0; i<taille1; i++){
            sprintf(nom,"%s.txt",tab[i].nom);
            f2 = fopen(nom, "r");
            if(f2 == NULL){
                exit(1);
            }
            taille = nbLigne(f2);
            fclose(f2);
            for(int j=0; j<taille; j++){
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
        }
    }else if(val3 == 1){
        e.ep = verifDate(5, "l'epreuve", 0);
        for(int i=0; i<taille1; i++){
            sprintf(nom,"%s.txt",tab[i].nom);
            f2 = fopen(nom, "r");
            if(f2 == NULL){
                exit(1);
            }
            taille = nbLigne(f2);
            fclose(f2);
            for(int a=0; a<taille; a++){
                if(e.ep == tab[i].e[a].ep){
                    printf("%s\n", tab[i].nom);
                    printf("%d/%d %d %ds\n", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                }
            }
        }
    }
}


void menu(Joueur* tab){
    printf("\033[H\033[2J");
    int n, taille1, taille2, val = 0, x, xathlete, xepreuve, xdate;
    FILE* f = fopen("athlete.txt", "r");
    if(f==NULL){
        exit(1);
    }
    taille1 = nbAthlete(f);
    fclose(f);
    n=0;
    char nom[20], r='O', r2, r3;
    printf("Que souhaitez vous faire ?\n 1: Ajouter un entrainement\n 2: Afficher l'historique des entrainements\n 3: Consulter des statistiques de performances d'un athlète\n\n Reponse :  ");
    scanf("%d", &n);
    printf("\033[H\033[2J");

    switch(n){
        case 1:
            while(val == 0){
                printf("Pour quel athlete ?\n\nReponse : ");
                scanf("%s", nom);
                printf("\033[H\033[2J");

                for(int i=0; i<taille1; i++){
                    if(strcmp(tab[i].nom, nom)==0){
                        sprintf(nom,"%s.txt",nom);

                        f = fopen(nom, "a+");
                        if(f == NULL){
                            exit(1);
                        }

                        taille2 = nbLigne(f);
                        ajoutEntrainement(f, tab[i].e, taille2);
                        i = taille1;
                        val = 1;
                    }else if(i==taille1-1){
                        printf("verifier l'orthographe\n");
                        val = 0;
                    }
                }
            }

            break;

        case 2:
            while((r=='O') || (r=='o')){
                x=0;
                while((x<1) || (x>3)){
                    printf("Quel filtre voulez-vous mettre ?\n1: Athlète\n2: Date\n3: Epreuve\n\nRéponse : ");
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
                        break;
                }

                printf("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :");
                scanf(" %c", &r);
                printf("\033[H\033[2J");
                }

                if((xathlete!=1) && (xdate!=1) && (xepreuve!=1)){
                    printf("Vous n'avez activé aucun filtre\n");
                    break;
                }
                printf("Voici les filtres activés : \n");
                if(xathlete==1){
                    printf("Athlete\n");
                }
                if(xdate==1){
                    printf("Date\n");
                }
                if (xepreuve==1){
                    printf("Epreuve\n");
                }
                printf("Souhaitez-vous desactiver un filtre ? (o/n)\n\nRéponse : ");
                scanf(" %c", &r3);
                printf("\033[H\033[2J");
                while((r3=='o') || (r3=='O')){
                    x=0;
                    printf("Quel filtre souhaitez-vous désactiver ?\n");
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
                            printf("Aucun filtre n'a été enlevé\n");
                            r3 = n;
                            break;

                        default :
                            printf("Saisissez une valeur correcte\n");
                            break;
                    }
                    printf("Souhaitez-vous enlever un autre filtre ? (o/n)\n\nReponse :");
                    scanf(" %c", &r3);
                    printf("\033[H\033[2J");
                }
                historique(tab, taille1, xathlete, xdate, xepreuve);
            break;


        case 3:




        default:
            printf("Veuillez saisir une valeur comprise entre 1 et 3");
    }
}

int main(){
    Joueur* tab = creationTab();
    menu(tab);
    return 0;
}