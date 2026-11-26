#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int annee;
    int nb_accidents;
    int indemnes;
    int tues;
    int blesses_graves;
    int blesses_legers;
} Annee;

void afficher_menu_annee(Annee tab[]);

