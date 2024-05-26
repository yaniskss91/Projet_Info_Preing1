#ifndef PASSERELLEJO_H_INCLUDED
#define PASSERELLEJO_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>

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

char* creaAllocNom(int taille);
void verifTab(Entrainement* tab);
void verifAllocFich(FILE* f);
int nbAthlete(FILE* f);
int nbLigne(FILE* f);
Entrainement* creationTabE(FILE* f, int taille);
Joueur* creationTab();
int verifDate(int max, char* nom, int val);
void ajoutEntrainement(FILE* f, Entrainement* tab, int taille);
char verif_r(char nom[50], char r);
int verif1(char* nom);
int verif2(char* nom, int val);
int verifNom(int taille, char* nom, Joueur* tab);
void historique(Joueur * tab, int taille, int val1, int val2, int val3);
int* tabTemps(Entrainement* tab, int taille, int taille2, int ep);
float moyenne(int* tab, int taille);
int partition(int* A, int debut, int fin);
void triRapideRec(int* A, int debut, int fin);
void triRapide(int* A, int n);
void Compare_Perf(Joueur *tab,int i, int taille);
void menu(Joueur* tab);


#endif // PASSERELLEJO_H_INCLUDED
