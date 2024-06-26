#include "passerellejo.h"
//Creation Allocation er Verication
char* creaAllocNom(int taille){
    char* nom = NULL;
    nom = malloc(sizeof(char) *taille);
    if(nom == NULL){
        exit(1);
    }
    return nom;
}
// Verification creation tableau
void verifTab(Entrainement* tab){
    if(tab == NULL){
        exit(3);
    }
}
// Verification creation tableau
void verifAllocFich(FILE* f){
    if(f == NULL){
        exit(2);
    }
}

// Calcul dans le fichier athelte le nombre d'athlete
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
// Calcul du nombre de ligne par fichier
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
// Creation et remplissage d'un tableau entrainement pour un athlete
Entrainement* creationTabE(FILE* f, int taille){
    Entrainement* tab = NULL;
    tab = malloc(sizeof(Entrainement)*taille);
    verifTab(tab);

    Entrainement e;

    rewind(f);
    for(int i=0; i<taille; i++){
        fscanf(f, "%d %d %d %d", &e.date.jour, &e.date.mois, &e.ep, &e.temps);
        if(e.ep == 5){
            fscanf(f, "%d", &e.position);
        }
        tab[i] = e;
    }

    return tab;
}
// creation du tableau principale entrainement
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
//Verification si str est composé de chiffres et non de lettres
int verifNb(const char *str){
     for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;

}
// Securistation du scanf pour eviter des boucles infini
int securscanf(char* test){
    int x;
    if (test !=NULL){
        test[strcspn(test, "\n")] = 0;

        if (verifNb(test)){
            x = atoi(test);
            return x;
        }
        else {
            printf("Erreur, veuillez réessayer\n\n\n");
            return 0;
        }                        
    }
    else {
        printf("Erreur dans la lecture de la valeur\n");
        return 0;
    }
}
// Verification des dates de l'utilisateur
int verifDate(int max, char* nom, int val){
    char* test = creaAllocNom(100);
    while((val<1)|| (val>max)){
        printf("Quelle est %s de l'entrainement ?\n", nom);

        if(nom == "l'epreuve"){
            printf("1: 100m\n 2: 400m\n 3: 5000m\n 4: Marathon\n 5: Relais\n");
        }

        printf("\n\nReponse : ");
        scanf("%s", test);
        printf("\033[H\033[2J");
        val = securscanf(test);

        if((val<1)|| (val>max)){
            printf("Saisissez une valeur correcte.\n");
        }
    }
    return val;
}
// Ajout d'entrainement 
void ajoutEntrainement(FILE* f, Entrainement* tab, int taille){
    Entrainement nouv;
    char* test = creaAllocNom(100);

    nouv.date.jour = verifDate(31, "jour", 0);
    nouv.date.mois = verifDate(12, "mois", 0);
    nouv.ep = verifDate(5, "l'epreuve", 0);

    nouv.temps = -1;
    while(nouv.temps<0){
        printf("Quel temps (en seconde) ?\n\nReponse : ");
        scanf("%d", &nouv.temps);
        printf("\033[H\033[2J");

        if(nouv.temps<0){
            printf("Saisissez une valeur correcte.\n");
        }
    }

    taille+=1;

    tab = realloc(tab, sizeof(Entrainement)*taille);
    verifTab(tab);

    if (nouv.ep==5){
        nouv.position=0;
        while((nouv.position < 1) || (nouv.position>4)){
            printf("Quelle position dans le relais ?\n\nReponse: ");
            scanf("%s", test);
            printf("\033[H\033[2J");
            nouv.position = securscanf(test);
        }
    }
    tab[taille-1] = nouv;

    fprintf(f, "\n%d %d %d %d", nouv.date.jour, nouv.date.mois, nouv.ep, nouv.temps);
    if(nouv.ep == 5){
        fprintf(f, " %d", nouv.position);
    }
}
//verification si le nom est composé de lettres
char verif_r(char nom[50], char r){
    while((r!='o') &&(r!='n')){
        printf("%s", nom);
        scanf(" %c", &r);
        printf("\033[H\033[2J");
    }
    return r;
}
//Fonction pour les filtres.Verification la validation du choix de filtres
int verif1(char* nom){
    char* r = creaAllocNom(20);
    printf("Souhaitez vous activer le filtre <<%s>> ? (o/n)\n\nRéponse :", nom);
    scanf(" %s", r);
    printf("\033[H\033[2J");

    while(((r[0]!='o') && (r[1]!='\0'))||(r[0]!='n') && (r[1]!='\0')){
        printf("Souhaitez vous activer le filtre <<%s>> ? (o/n)\n\nRéponse :", nom);
        scanf(" %s", r);
        printf("\033[H\033[2J");
    }
    if(r[0]=='o'){
        return 1;
    }else{
        return 0;
    }
}
// Verification si le filtre a bien été enlever ou pas
int verif2(char* nom, int val){
    if(val==0){
        printf("Saisissez une valeur correcte !\n");
    }
    else{
        printf("Le filtre %s a bien été enlever\n", nom);

    }
    return 0;
}
// Verification de l'orthographe du nom
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
// Consultation de l'historique d'un athelte 
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
                                printf("%d/%d %d %ds ", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep,tab[i].e[a].ep, tab[i].e[a].temps);
                                if(e.ep == 5){
                                    printf("%d", tab[i].e[a].position);
                                }
                                printf("\n");
                            }
                            else{
                                printf("%d/%d %d %ds ", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                                if(tab[i].e[a].ep == 5){
                                    printf("%d", tab[i].e[a].position);
                                }
                                printf("\n");
                            }
                        }
                    }
                }
                else if(val3 == 1){
                    e.ep = verifDate(5, "l'epreuve", 0);
                    for(int a=0; a<taille2; a++){
                        if(e.ep == tab[i].e[a].ep){
                            printf("%d/%d %d %ds ", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                            if(e.ep == 5){
                                printf("%d", tab[i].e[a].position);
                            }
                            printf("\n");
                        }
                    }
                }
                else{
                    for(int j=0; j<taille2; j++){
                        printf("%d/%d %d %ds ", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                        if(tab[i].e[j].ep == 5){
                            printf("%d", tab[i].e[j].position);
                        }
                        printf("\n");
                    }
                }
                v = 1;
            }else{
                printf("Vérifier l'arthographe\n\n");
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
                        printf("%d/%d %d %ds ", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                        if(e.ep == 5){
                            printf("%d", tab[i].e[j].position);
                        }
                        printf("\n");
                    }
                    else{
                        printf("%s\n", tab[i].nom);
                        printf("%d/%d %d %ds\n", tab[i].e[j].date.jour, tab[i].e[j].date.mois, tab[i].e[j].ep, tab[i].e[j].temps);
                        if(tab[i].e[j].ep == 5){
                            printf("%d", tab[i].e[j].position);
                        }
                        printf("\n");
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
                    printf("%d/%d %d %ds ", tab[i].e[a].date.jour, tab[i].e[a].date.mois, tab[i].e[a].ep, tab[i].e[a].temps);
                    if(tab[i].e[a].ep == 5){
                        printf("%d", tab[i].e[a].position);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        }
    }else{
        printf("vous revenez en arriere\n\n");
    }
}


int* tabTemps(Entrainement* tab, int taille, int taille2, int ep){
    int k = 0;
    int* tabTmps = malloc(taille2 * sizeof(int));
    if (tabTmps == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    for(int i=0; i<taille; i++){
        if(tab[i].ep == ep){
            tabTmps[k] = tab[i].temps;
            k++;
        }
    }
    return tabTmps;
}

//Calcul de moyenne entre deux temps
float moyenne(int* tab, int taille){
    float som = 0;
    for(int i=0;i<taille; i++){
        som = som+tab[i];
    }
    float moy = som/taille;
    return moy;
}

// CALCULER LE PIVOT
int partition(int* A, int debut, int fin) {
    int inf, sup, tmp;
    inf = debut + 1;
    sup = fin;
    while (inf <= sup) {
        while (inf <= sup && A[sup] > A[debut]) {
            sup--;
        }
        while (inf <= sup && A[inf] <= A[debut]) {
            inf++;
        }
        if (inf < sup) {
            tmp = A[sup];
            A[sup] = A[inf];
            A[inf] = tmp;
            inf++;
            sup--;
        }
    }
    tmp = A[debut];
    A[debut] = A[sup];
    A[sup] = tmp;
    return sup;
}

//TRIER LE TABLEAU A DANS L'ORDRE CROISSANT
void triRapideRec(int* A, int debut, int fin){
    int pivot;
    if(debut < fin){
        pivot = partition(A, debut, fin);
        triRapideRec(A, debut, pivot-1);
        triRapideRec(A, pivot+1, fin);
    }
}

// INITIALISER LES PARAMETRES DE LA FONCTION QUI TRIE LE TABLEAU DANS L'ORDRE CROISSANT
void triRapide(int* A, int n){
    triRapideRec(A, 0, n-1);
}
//Comparateur de performance entre deux dates
void Compare_Perf(Joueur *tab,int i, int taille){
    Date d1,d2;
    int epreuve,tps1=0,tps2=0,diff_tmps;
    epreuve=verifDate(5, "l'epreuve", 0);
    d1.jour=verifDate(31, "jour", 0);
    d1.mois=verifDate(12, "mois", 0);
    d2.jour=verifDate(31, "jour", 0);
    d2.mois=verifDate(12, "mois", 0);
    for(int j=0;j<taille;j++){
        if( (tab[i].e[j].ep==epreuve )&&(tab[i].e[j].date.jour==d1.jour) && (tab[i].e[j].date.mois==d1.mois)){ // SI L'EPREUVE ET LES DATES SAISIES CORRESPONDENTS AU FICHIERS
            tps1=tab[i].e[j].temps;
            j=taille;
        }

    }
    for(int j=0;j<taille;j++){
        if((tab[i].e[j].ep==epreuve )&& (tab[i].e[j].date.jour==d2.jour) && (tab[i].e[j].date.mois==d2.mois )){
            tps2=tab[i].e[j].temps;
            j=taille;
        }

    }
    if(tps1!=0 && tps2!=0){

    
        diff_tmps=tps1-tps2;
        if(diff_tmps<0){
            diff_tmps=-diff_tmps;
            printf("L athlete a regresse de %d s\n",diff_tmps);
        }
        else{
            printf("L athlete a progresser de %d s\n",diff_tmps);
        }
        
    }
    else{
        printf("Une des deux dates est incorrecte\n\n");
    }

}



// Le menu principale, utilisation de switch pour naviguer dans le menu
void menu(Joueur* tab){
    printf("\033[H\033[2J");
    int n=0, taille, taille2, v = 0, x, xathlete = 0, xepreuve=0, xdate=0;
    int xresume = 0, xenvoie = 0, xprogre = 0;
    float moy;
    char *test = creaAllocNom(100);

    FILE* f = fopen("athlete.txt", "r"); // Ouverture fichiers athlete qui contient le nom des athletes
    verifAllocFich(f);
    FILE* f2 = NULL;
    taille = nbAthlete(f);
    fclose(f);

    char* nom = creaAllocNom(50);//Allcation dynamique pour les noms
    char r='O', r2='o';

    while(n!=4){
        n=0;
        printf("Que souhaitez vous faire ?\n 1: Ajouter un entrainement\n 2: Afficher l'historique des entrainements\n 3: Consulter des statistiques\n 4: Quitter le programme\n\n Reponse :  ");
        scanf("%s", test);
        printf("\033[H\033[2J");
        n = securscanf(test);

        switch(n){  // switch pour les différents choix possibles proposer
            case 1:
                v=0;
                while(v == 0){          // boucle de validation pour si il y a des erreures relancer cette boucle
                    printf("Pour quel athlete ?\n\nReponse : ");
                    scanf("%s", nom);
                    printf("\033[H\033[2J");

                    for(int i=0; i<taille; i++){        // Parcourir le fichier athlete
                        if(strcmp(tab[i].nom, nom)==0){
                            sprintf(nom,"%s.txt",nom);

                            f = fopen(nom, "a+");
                            verifAllocFich(f);

                            taille2 = nbLigne(f);

                            ajoutEntrainement(f, tab[i].e, taille2);

                            i = taille;
                            v = 1;
                        }else if(i==taille-1){              // message d'erreure
                            printf("verifier l'orthographe(n'oublier pas la majuscule)\n");
                            v = 0;
                        }
                    }
                }

                break;

            case 2:
                r='O';
                r2='o';
                while((r=='O') || (r=='o')){                // boucle de validation pour si il y a des erreures relancer cette boucle
                    x=0;
                    while((x<1) || (x>4 )){                 // boucle de validation pour x
                        printf("Quel filtre voulez-vous mettre ?\n1: Athlète\n2: Date\n3: Epreuve\n4: retour\n\nRéponse : ");
                        scanf("%s", test);
                        printf("\033[H\033[2J");
                        x = securscanf(test);
                    }

                    switch (x){                             // switch pour les différents choix possible proposer
                        case 1:
                            xathlete = verif1("athlete");
                            break;
                        case 2:
                            xdate = verif1("date");
                            break;
                        case 3:
                            xepreuve = verif1("epreuve");
                            break;
                        case 4:                         // condition pour passer le case sans passer par les étape intermédiaire du case
                            xathlete = 0;
                            xepreuve  = 0;
                            xdate = 0;
                            r = 'n';
                            r2 = 'n';
                            break;
                    }
                    if(x != 4){             // condition pour rester dans le case 
                        printf("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :");
                        scanf(" %c", &r);
                        r = verif_r("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :", r);
                        printf("\033[H\033[2J");
                    }

                }
                if(x != 4){                 // condition pour rester dans le case 
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
                    scanf(" %c", &r2);
                    r2 = verif_r("Souhaitez-vous mettre un autre filtre ? (o/n)\n\nReponse :", r2);
                    printf("\033[H\033[2J");
                }
                while((r2=='o') || (r2=='O')){                  // validation 2
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
                    scanf("%s", test);
                    printf("\033[H\033[2J");
                    x = securscanf(test);
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
                            printf("Aucun filtre n'a été enlever\n");
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

            case 4:

                break;

            case 3:
                r='O';
                while((r=='O') || (r=='o')){                // boucle de validation pour si il y a des erreures relancer cette boucle
                     x=0;
                    while((x<1) || (x>3)){                  // boucle de validation pour x
                        printf("Que voulez savoir ?\n1: Résumer d'un athlète\n2: Qui envoier au JO\n3: La progression d'un athlète\n\nRéponse : ");
                        scanf("%s", test);
                        printf("\033[H\033[2J");
                        x = securscanf(test);
                    }

                    switch (x){
                        case 1:
                             while(r2=='o'){                    // boucle de validation pour si il y a des erreures relancer cette boucle
                                printf("Quel athléte ?\n\nReponse: ");
                                scanf(" %s", nom);
                                printf("\033[H\033[2J");
                                int i = verifNom(taille, nom, tab);
                                xepreuve = 0;
                                if(i != -1){
                                    sprintf(nom,"%s.txt",nom);
                                    f2 = fopen(nom, "r");
                                    verifAllocFich(f2);

                                    taille2 = nbLigne(f2);
                                    xepreuve = verifDate(5, "l'epreuve", 0);
                                    int taille3 = 0;
                                    for(int j=0; j<taille2; j++){               // calculer le nombre d'entrainement qu'a l'athlete
                                        if(tab[i].e[j].ep == xepreuve){
                                            taille3++;
                                        }
                                    }
                                    if(taille3 != 0){
                                        int* tabTmps = malloc(taille3 * sizeof(int));               // initialisation d un tableau int
                                        if(tabTmps == NULL){
                                            exit(1);
                                        }

                                        tabTmps = tabTemps(tab[i].e, taille2, taille3, xepreuve);
                                        moy = moyenne(tabTmps, taille3);
                                        triRapide(tabTmps, taille3);
                                        printf("\033[H\033[2J");
                                        printf("%s\n", tab[i].nom);
                                        printf("meilleur temps : %d\n", tabTmps[0]);
                                        printf("pire temps : %d\n", tabTmps[taille3-1]);
                                        printf("temps moyen : %fs\n", moy);

                                    }else{
                                        printf("l'athlète n'a pas fait d'entrainement pour cette épreuve.\n");
                                    }
                                    r2 = 'n';
                                }else{
                                    printf("verifier l'orthographe\n");
                                }
                            }r = 'n';
                            break;
                        case 2:
                            xepreuve = verifDate(5, "l'epreuve", 0);

                            int taille3 = 0;
                            for(int i=0; i<taille; i++){
                                sprintf(nom, "%s.txt", tab[i].nom);
                                f2 = fopen(nom, "r");
                                verifAllocFich(f2);
                                taille2 = nbLigne(f2);
                                for(int j=0; j<taille2; j++){
                                    if(tab[i].e[j].ep == xepreuve){
                                        taille3++;
                                        j = taille2;
                                    }
                                }
                                fclose(f2);
                            }

                            if(taille3 != 0){
                                int k, l=0;
                                int* tabTmps;
                                int* tabMoy = malloc(taille3 * sizeof(int));
                                if(tabMoy == NULL){
                                    exit(1);
                                }
                                for(int i=0; i<taille; i++){
                                    taille3 = 0;
                                    sprintf(nom, "%s.txt", tab[i].nom);
                                    f2 = fopen(nom, "r");
                                    verifAllocFich(f2);
                                    taille2 = nbLigne(f2);
                                    for(int j=0; j<taille2; j++){
                                        if(tab[i].e[j].ep == xepreuve){
                                            taille3++;
                                        }
                                    }
                                    rewind(f2);
                                    tabTmps = malloc(taille3 * sizeof(int));
                                    if(tabTmps == NULL){
                                        exit(12);
                                    }
                                    k = 0;
                                    for(int j=0; j<taille2; j++){
                                        if(tab[i].e[j].ep == xepreuve){
                                            tabTmps[k] = tab[i].e[j].temps;                                            
                                            k++;
                                        }
                                    }
                                
                                    if(taille3 >0){
                                        moy = moyenne(tabTmps, taille3);                            
                                        tabMoy[l] = moy;                                        
                                        l++;
                                    }

                                    fclose(f2);
                                }

                                triRapide(tabMoy, taille3);

                                for(int i=0; i<taille; i++){
                                    taille3 = 0;
                                    sprintf(nom, "%s.txt", tab[i].nom);
                                    f2 = fopen(nom, "r");
                                    verifAllocFich(f2);
                                    taille2 = nbLigne(f2);
                                    for(int j=0; j<taille2; j++){
                                        if(tab[i].e[j].ep == xepreuve){
                                            taille3++;
                                        }
                                    }
                                    rewind(f2);
                                    tabTmps = malloc(taille3 * sizeof(int));
                                    if(tabTmps == NULL){
                                        exit(12);
                                    }
                                    k = 0;
                                    for(int j=0; j<taille2; j++){
                                        if(tab[i].e[j].ep == xepreuve){
                                            tabTmps[k] = tab[i].e[j].temps;
                                            //printf("%d\n", tabTmps[k]);
                                            k++;
                                        }
                                    }
                                    if(taille3 >0){
                                        moy = moyenne(tabTmps, taille3);
                                        if(moy == tabMoy[0]){
                                            printf("meilleur temps moy : %ds fait par %s\n", tabMoy[0], tab[i].nom);
                                        }else if(moy == tabMoy[1]){
                                            printf("2e meilleur temps moy : %ds fait par %s\n", tabMoy[1], tab[i].nom);
                                        }else if(moy == tabMoy[2]){
                                            printf("3e meilleur temps moy : %ds fait par %s\n", tabMoy[2], tab[i].nom);
                                        }
                                    }

                                    fclose(f2);
                                }
                                free(tabTmps);

                            }
                            else{
                                printf("aucun athlète n'a fait d'entrainement pour cette épreuve.\n");
                            }
                            r = 'n';

                            break;
                        case 3:
                            v=0;
                            while(v == 0){
                                printf("Pour quel athlete ?\n\nReponse : ");
                                scanf("%s", nom);
                                int i = verifNom(taille, nom, tab);
                                printf("\033[H\033[2J");

                                sprintf(nom,"%s.txt",nom);
                                f = fopen(nom, "r");
                                verifAllocFich(f);
                                taille2 = nbLigne(f);
                                Compare_Perf(tab, i, taille2);
                                v=1;
                            }
                            r = 'n';
                        break;
                    }
                }
                break;
            default:
                printf("Valeur non comprise entre 1 et 4\n\n");
                break;
        }
    }
}