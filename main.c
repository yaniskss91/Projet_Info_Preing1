#include "passerellejo.h"

int main(){
    printf("\033[H\033[2J");
    printf("cacca\n ");
    Joueur* tab = creationTab();
    printf("pipi");
    menu(tab);
    return 0;
}