#include <stdio.h>     
#include <stdlib.h>   
#include "year_data.h" 

int main(int argc, char **argv){
    if(argc != 3){
        printf("erreur dans le nombre d'arguments !\n");
        exit(1); 
    }

    
    FILE *f = fopen(argv[2], "r");
    if(f == NULL){ 
        printf("erreur à l'ouverture du fichier !\n");
        exit(1);
    }

    // Tableau de 2005 à 2024 à 0
    Annee tab[20] = {0};

    int annee, id_acc, loc, type, gravite, genre, naissance, trajet;
    char id_veh[50]; // Chaine de caractères pour la colonne vehicle_id 

    // Mémoire du dernier accident lu pour ne pas compter plusieurs fois le même
    int dernier_id = 0;
    int derniere_annee = 0;

    char temp[1000];
    fgets(temp, 999, f);
    while(fscanf(f, "%d;%d;%s;%d;%d;%d;%d;%d;%d", &annee, &id_acc, id_veh, &loc, &type, &gravite, &genre, &naissance, &trajet) == 9){

        if(annee >= 2005 && annee <= 2024){
            int i = annee - 2005; // Convertit l'année en indice (2005 -> 0)

            // Si l'id ou l'année change c'est un nouvel accident
            if(id_acc != dernier_id || annee != derniere_annee){
                tab[i].nb_accidents++;
                dernier_id = id_acc;      // Met a jour le dernier ID vu
                derniere_annee = annee;   // Met a jour la dernière année vu
            }
            if(gravite == 1){
                tab[i].indemnes++;
            } 
            else if(gravite == 2){
                tab[i].tues++;
            } 
            else if(gravite == 3){
                tab[i].blesses_graves++;
            }
            else if(gravite == 4){
                tab[i].blesses_legers++;
            } 
        }
    }

    fclose(f);

    afficher_menu_annee(tab); // Lance le menu en lui envoyant le tableau rempli

    return 0;
}

// Affiche le menu pour consulter une année
void afficher_menu_annee(Annee tab[20]){
    int choix = -1;
    while(choix != 0){ // Boucle tant que l'utilisateur ne tape pas 0
        printf("\nEntrez une annee (2005-2024) ou 0 pour quitter : ");
        scanf("%d", &choix);

        if(choix >= 2005 && choix <= 2024){ 
            int i = choix - 2005;           
            printf("Annee %d :\n", choix);
            printf("  Accidents      : %d\n", tab[i].nb_accidents);
            printf("  Indemnes       : %d\n", tab[i].indemnes);
            printf("  Tues           : %d\n", tab[i].tues);
            printf("  Blesses graves : %d\n", tab[i].blesses_graves);
            printf("  Blesses legers : %d\n", tab[i].blesses_legers);
        } else if(choix != 0){ // Si l'année n'existe pas et différente de 0
            printf("Annee invalide !\n");
        }
    }
}
