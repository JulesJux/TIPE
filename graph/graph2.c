#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct maillon_s {
int val;
struct maillon_s* next;
};
typedef struct maillon_s maillon;

typedef maillon* liste;


liste* construit_ss_graphe(liste* G, liste N, int taille);
liste ajoute_sommet(liste l, int u);
void affiche(liste* G, int taille);
void exemple(void);


int main(void){
	exemple();
}

void exemple(void){
	liste* ex = malloc(sizeof(liste)*4);
	for(int i = 0; i < 4; i++){
		ex[i] = NULL;
	}
	ex[0] = ajoute_sommet(ex[0], 1);
	ex[0] = ajoute_sommet(ex[0], 2);
	ex[1] = ajoute_sommet(ex[1], 0);
	ex[1] = ajoute_sommet(ex[1], 2);
	ex[1] = ajoute_sommet(ex[1], 3);
	ex[3] = ajoute_sommet(ex[3], 1);
	ex[2] = ajoute_sommet(ex[2], 0);
	ex[2] = ajoute_sommet(ex[2], 1);

	printf("graphe initial : \n");
	affiche(ex, 4);

	liste* G2 = construit_ss_graphe(ex, ex[0], 4);
	liste* G3 = construit_ss_graphe(ex, ex[1], 4);
	liste* G4 = construit_ss_graphe(ex, ex[3], 4);

	//affiche(G2, 4);
	//affiche(G3, 4);
	printf("Graphe privé des voisins de 3 : \n");
	affiche(G4, 4);

	return;
}

void affiche(liste* G, int taille){
	for(int i = 0; i < taille; i++){
		liste ptr = G[i];
		printf("voisins de %d \n", i);
		while(ptr != NULL){
			printf("%d, ", ptr->val);
			ptr = ptr->next;
		}
		printf("\n");
	}
	return;
}


bool liste_mem(int u, liste l){
	if(l == NULL){
		return false;
	}
	if (u == l->val){
		return true;
	}
	else{
		return liste_mem(u, l->next);
	}
}

liste ajoute_sommet(liste l, int u){
	if (liste_mem(u, l)){
		return l;
	}
	else{
		maillon* new = malloc(sizeof(maillon));
		new -> val = u;
		new -> next = l;
		return new;
	}
}

liste* construit_ss_graphe(liste* G, liste N, int taille){
	liste* G2 = malloc(sizeof(liste)*taille);
	for(int i = 0; i < taille; i++){
		G2[i] = NULL;
		if (!liste_mem(i, N)){
			liste ptr = G[i];
			while(ptr != NULL){
				if(!liste_mem(ptr->val, N)){
					G2[i] =	ajoute_sommet(G2[i], ptr->val);
					
				}
				ptr = ptr->next;
			}
		}
	} 	
	return G2;
}

liste enumm_chordless_path(liste* G, int s, int t, liste Q, int taille){
	if(liste_mem(t, G[s])){
		return ajoute_sommet(Q, t); 
	}
	maillon* ptr = G[s];
	while (ptr != NULL){
		liste* G2 = NULL; 
	}
}

