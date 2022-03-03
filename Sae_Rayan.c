// Codé par Rayan CHOUCHANE 

#include <stdio.h>

#define TAILLE_GRILLE 6

int hauteur_colonne ( int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne );
void init_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
void affiche_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
int poser_jeton (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int joueur);
int scan_colonne (int grille [TAILLE_GRILLE][TAILLE_GRILLE]);
int verifie_gagne (int grille [TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);

// Execution du jeu
int main () {
	
	int grille[TAILLE_GRILLE][TAILLE_GRILLE];
	init_grille (grille);
	
	int ligne;
	int colonne;
	int joueur=2;
	int victoire=0;
	int tour=1;
	
	do {					// Pour alterner les joueurs
		if (joueur==1) { 
			joueur=2;
		} else {
			joueur=1;
		}
		
		affiche_grille (grille);
		printf("Joueur %d à ton tour!\n", joueur);
		do {
			colonne = scan_colonne(grille);
			ligne = poser_jeton(grille, colonne , joueur);
		}
        while (ligne==-3); 			 // Si aucun jeton posé bloquer le tour
		printf("\n");
		
		victoire = verifie_gagne (grille, ligne, colonne ,joueur);
		tour++;
		
	}
     while (victoire==0 && tour<=36); // Plateau remplie en 36 tours
	
	
	affiche_grille (grille);
	if (victoire == 1 && joueur == 1) {
		printf("Joueur 1 a gagné\n");
	} else if (victoire == 1 && joueur == 2) {
		printf("Joueur 2 a gagné\n");
	} else {
		printf("Match nul");
	}
	
	
}

// Initialisation de chacune des cases du tableau à 0
void init_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]) {

	for (int x = 0; x<TAILLE_GRILLE; x++) {
		for (int y = 0; y<TAILLE_GRILLE; y++) {
			grille[x][y]=0;
		}
	}
}

// Affichage de la grille, J1 correspond à O, J2 correspond à X
void affiche_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
    for (int i=TAILLE_GRILLE-1 ;i>=0;i--){
        printf("|");
        for(int y=0;y<TAILLE_GRILLE;y++){


            switch (grille[i][y]){

            case 0:
                printf(" ");
                break;

            case 1:
                printf("X");
                break;

            case 2:
                printf("O");
                break;
            }

            printf("|");
      }

    printf("\n");
    }   
}

// Renvoie le nombre de jetons présent dans une colonne;
int hauteur_colonne ( int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne ) {
	int x=0;
	while (grille[x][colonne]!=0 && x<TAILLE_GRILLE) {
		x++;
	}
	return x;
}

// Si colonne pleine retourne -3; Colonne non valide retourne -2. Si jouer invalide retourne -1, si jeton posé retourne hauteur (première ligne =0)
int poser_jeton (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int joueur) {

	int hauteur = hauteur_colonne(grille,colonne);

	if(hauteur == 6){ // Colonne pleine
		return-3;
	}
	else if (colonne<0 || colonne >5){ // Colonne non valide
		return -2;
	}
	else if (joueur!=1 && joueur!=2){ // Joueur invalide
		return-1;
	}
	else{
		grille[hauteur][colonne]=joueur;
	}
	return hauteur;
}

// Saisir la colonne désirer et empecher la saisie des valeurs incorrects
int scan_colonne(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
	printf("Choississez ou vous shouhaiter jouer : ");
	int saisie;
	int nombreArguments;

	do{
			printf("Choississez ou vous shouhaiter jouer : ");
			nombreArguments=scanf("%d",&saisie);
	}
	while ((saisie<0 || saisie>=TAILLE_GRILLE) || nombreArguments!=1);
	return saisie;
}

// Verifie si un joueur à gagné renvoie 1 si oui et 0 si non:(
int verifie_gagne (int grille [TAILLE_GRILLE][TAILLE_GRILLE], int ligne, int colonne, int joueur) {
	int x;
	int y;
	int compteurJetons=0;
	
	//Vérification verticale va regarde la colonne ou se situe le pion si un des joueurs à gagner
	for (x=0; x<TAILLE_GRILLE; x++) {
		if (grille[x][colonne]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			compteurJetons=0;
		}
	}
	
	//Horizontalement verticale va regarde la ligne ou se situe le pion si un des joueurs à gagner
	compteurJetons=0;
	for (y=0; y<TAILLE_GRILLE; y++) {
		if (grille[ligne][y]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			compteurJetons=0;
		}
	}
	
	//Diagonale Gauche verticale va regarde en bas à gauche puis en haut à droite si il ya les meme jetons si 4 jetons alors le joueurs à gagné
	compteurJetons=1;
	x=ligne;
	y=colonne;
	int sortie=0;
	int i=1;
	while (x<6 && x>=0 && y<6 && y>=0 && sortie==0) {
		if (grille[x-i][y-i]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			sortie=1;
		}
		i++;
	}
	x=ligne;
	y=colonne;
	i=1;
	while (x<6 && x>=0 && y<6 && y>=0 && compteurJetons!=-1) {
		if (grille[x+i][y+i]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			compteurJetons=-1;
		}
		i++;
	}
	
	//Diagonale Droite  va regarde en bas à droite puis en haut à gauche si il ya les meme jetons si 4 jetons alors le joueurs à gagné
	compteurJetons=1;
	x=ligne;
	y=colonne;
	sortie=0;
	i=1;
	
	while (x<6 && x>=0 && y<6 && y>=0 && sortie==0) {
		if (grille[x+i][y-i]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			sortie=1;;
		}
		i++;
	}
	x=ligne;
	y=colonne;
	i=1;
	while (x<6 && x>=0 && y<6 && y>=0 && compteurJetons!=-1) {
		if (grille[x-i][y+i]==joueur) {
			compteurJetons++;
			if (compteurJetons==4) {
				return 1;
			}
		}
		else {
			compteurJetons=-1;
		}
		i++;
	}
	
	//Si aucun des autres cas vrai on renvoie 0
	return 0;
}