#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct maillon_s {
	int val;
	struct maillon_s* next;
};
typedef struct maillon_s maillon;

typedef maillon* liste;

typedef liste chemin;

struct maillon_chemin_s {
	chemin path;
	struct maillon_chemin_s* next;
};
typedef struct maillon_chemin_s maillon_chemin;
typedef maillon_chemin* liste_chemin;


liste* construit_ss_graphe(liste* G, liste N, int taille);
liste ajoute_sommet(liste l, int u);
void affiche(liste* G, int taille);
void exemple(void);
liste pop(liste l, int u);
liste_chemin enumm_chordless_path(liste* G, int s, int t, liste Q, int taille, liste_chemin res);
void affiche_chemin(chemin weg);
void libere_graphe(liste* G, int taille);
void libere_liste(liste l);


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
	//ex[0] = ajoute_sommet(ex[0], 3);
	ex[1] = ajoute_sommet(ex[1], 0);
	ex[1] = ajoute_sommet(ex[1], 2);
	ex[1] = ajoute_sommet(ex[1], 3);
	ex[2] = ajoute_sommet(ex[2], 0);
	ex[2] = ajoute_sommet(ex[2], 1);
	ex[2] = ajoute_sommet(ex[2], 3);
	//ex[3] = ajoute_sommet(ex[3], 0);
	ex[3] = ajoute_sommet(ex[3], 1);
	ex[3] = ajoute_sommet(ex[3], 2);
	
	liste_chemin lc = enumm_chordless_path(ex, 0, 3, NULL, 4, NULL);

	while(lc != NULL){
		affiche_chemin(lc->path);
		liste tmp = lc->path;
		lc = lc->next;
		libere_liste(tmp);
	}

	libere_graphe(ex, 4);

	return;
}

void libere_liste(liste l){
	while(l != NULL){
		liste tmp = l;
		l = l -> next;
		free(tmp);
	}
}

void libere_graphe(liste* G, int taille){
	for(int i = 0; i < taille; i++){
		libere_liste(G[i]);
	}
	free(G);
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

void affiche_chemin(chemin weg){
	while(weg != NULL){
		printf("%d", weg->val);
		weg = weg -> next;
	}
	printf("\n");
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

bool liste_chemin_mem(chemin weg, liste_chemin l){
	if(l == NULL){
		return false;
	}
	if (weg == l->path){
		return true;
	}
	else{
		return liste_chemin_mem(weg, l->next);
	}
}

liste pop(liste l, int u){
	liste new = NULL;
	while(l != NULL){
		if(l->val!=u){
			ajoute_sommet(new, l->val);
		}
		l = l->next;
	}
	return new;
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

liste_chemin ajoute_chemin(liste_chemin l, chemin weg){
	if (liste_chemin_mem(weg, l)){
		return l;
	}
	else{
		liste_chemin new = malloc(sizeof(liste_chemin));
		new -> path = pop(weg, -1);
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

liste_chemin enumm_chordless_path(liste* G, int s, int t, liste Q, int taille, liste_chemin res){
	if(liste_mem(t, G[s])){
		chemin Q2 = ajoute_sommet(Q, t);
		free(Q2);
		return ajoute_chemin(res, Q2);
	}
	maillon* ptr = G[s];
	while (ptr != NULL){
		liste N2 = pop(G[s], ptr->val);
		liste* G2 = construit_ss_graphe(G, pop(N2, s), taille);
		liste Q2 = ajoute_sommet(Q, ptr->val);
		res = enumm_chordless_path(G2, ptr->val, t, Q2, taille, res);
		free(Q2);
		libere_graphe(G2, taille);
		ptr = ptr->next;
	}
	return res;
}
