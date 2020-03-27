//
//  main.c
//  SCIF1b
//
//  Created by Fabien SANCHEZ on 17/03/2020.
//  Copyright © 2020 Fabien SANCHEZ. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define taille 5

int m[taille][taille]={0}; // Création matrice
char liste_couleur[] ="ABCDEFG"; // Création nombre de couleur
char joueur[] = "OX"; //Couleur des joueurs
int piece_joueur1[2][taille*taille]={0}; //Préparation des pièces à tester
int piece_joueur2[2][taille*taille]={0};
int compteur1 = 1;
int compteur2 = 1;

void def_coordonnees(){
    int i =0;
    for (i=0; i<taille*taille;i++){
        piece_joueur1[1][i]=taille-1;
        piece_joueur2[0][i]=taille-1;
    }
}
void aire_de_jeu(){
    // char a = 'A';
    int i=0;
    int j=0;
    srand(time(NULL)); // démarrage du timer pour le rand
    
    // création des valeurs dans la matrices
        for(i=0; i < taille; i++){
            for(j=0; j < taille; j++){
                int lettre =  (rand() % (7));
                m[i][j]=liste_couleur[lettre];
                // printf("%c",m[i][j]); C'était pour vérifier
                if(j==taille-1 && i==0){
                    m[i][j]=joueur[0];
                }
                if(j==0 && i==taille-1){
                    m[i][j]=joueur[1];
                }
            }
        }
    }

int test_changement_couleur(int i, int j, int c, int k){
    if(m[i][j] == c){
        m[i][j] = joueur[k];
        return 1;
    }
    return 0;
}

void implementation_piece_joueur( int i, int j, int k){
    if (k==0){
        printf("%d",i);
        compteur1+=1;
        piece_joueur1[0][compteur1]=i;  // Implémentation des pièces du joueur 1
        piece_joueur1[1][compteur1]=j;
        
    }
    if (k==1){
        compteur2+=1;
        piece_joueur2[0][compteur2]=i;  // Implémentation des pièces du joueur 2
        piece_joueur2[1][compteur2]=j;
        
    }
    
}

void environnement(int i, int j, int c, int k){
    // à terme pour trouver l'environnement de la case du joueur
    int a=i-1;
    int b=j-1;
    
   
    a=i-1;
    b=j;
    if (a<taille && b<taille && a>=0 && b >=0){
        if ( 1 == test_changement_couleur(a, b, c, k)){
            implementation_piece_joueur(a,b,k);
            environnement(a, b, c, k);
        }
    }
    
    a=i;
    b=j-1;
    if (a<taille && b<taille && a>=0 && b >=0){
        if ( 1 == test_changement_couleur(a, b, c, k)){
            implementation_piece_joueur(a,b,k);
            environnement(a, b, c, k);
        }
    }
    a=i;
    b=j+1;
    if (a<taille && b<taille && a>=0 && b >=0){
        if ( 1 == test_changement_couleur(a, b, c, k)){
            implementation_piece_joueur(a,b,k);
            environnement(a, b, c, k);
        }
    }
    
    a=i+1;
    b=j;
    if (a<taille && b<taille && a>=0 && b >=0){
        if ( 1 == test_changement_couleur(a, b, c, k)){
            implementation_piece_joueur(a,b,k);
            environnement(a, b, c, k);
        }
    }
}
    
void print_aire_de_jeu(){
    int i=0;
    int j=0;
    // reconstruction et affichage de la matrice
    printf("Voici l'air de jeu :\n\n");
    for(i=0; i < taille; i++){
        for(j=0; j < taille; j++){
            printf("%c ",m[i][j]);
        }
        printf("\n");
    }
}


int Jouer(int a, int b,int k){
    char c = 0;
    int i = 0;
    scanf(" %c",&c);
    if ( k == 0 ){
        for (i=0; i<taille*taille; i++){
            environnement(piece_joueur1[0][i], piece_joueur1[1][i], c, k);
            printf("%d",piece_joueur1[0][i]);
        }
        print_aire_de_jeu();

    }
    if ( k == 1 ){
        for (i=0; i<taille*taille; i++){
            environnement(piece_joueur2[0][i], piece_joueur2[1][i], c, k);
            // printf("%d",piece_joueur2[1][i]);
        }
        print_aire_de_jeu();
    }
    return 0;
}

void determiner_joueur(int k){
    printf("\n C'est au joueur %d de commencer, quelle couleur choisis-tu ? \n",k+1);
    int a =0;
    if ( k == 0 ){
        a = Jouer(0,taille-1,k);
    }
    if ( k == 1 ){
        a = Jouer(taille-1,0,k);
    }
    }


void tour(){
    int k = 0;
    determiner_joueur(k);
    k+=1;
    determiner_joueur(k);
}
void nombre_de_tour(){
    int nombre_de_tour_limite = 0;
    int nombre_de_tour = 0;
    printf("Entres le nombre de tour que tu veux jouer :\n");
    scanf("%d", &nombre_de_tour_limite);
    
    if (nombre_de_tour_limite >= taille*taille/2){
        printf("Votre nombre de tour sera limité à %d \n", taille*taille/2); // Délimitation du nombre de tour, en effet taille^2/2 suffise pour finir en partant du principe que chaque joueur sélectionne toujours une bonne couleur
    }
    
    while (nombre_de_tour < nombre_de_tour_limite){
        tour();
        nombre_de_tour +=1;
    }
    
    
}
void mode_de_jeu(){
    
    printf("Dans quel mode de jeu veux - tu jouer ? \n1 : Contre un autre joueur\n2 : Contre une IA random\n");
    int a = scanf("%d",&a);
    
    if (a==1){
        printf("Tu as choisi de combattre un humain, tu seras le O. \n");
        nombre_de_tour();
    }
    
    if (a==2){
        printf("Tu as choisi de combattre une IA random, tu seras le O. \n");
        nombre_de_tour();
    }
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
   
    def_coordonnees(); // Préparation des origines
    aire_de_jeu(); // Création de l'aire de jeu
    print_aire_de_jeu();
    mode_de_jeu();
    
    
    printf("Tu t'es bien amusé j'espère! A une prochaine ! \n");
    return 0;
}
