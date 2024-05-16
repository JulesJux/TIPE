#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct maillon_s {
int val;
struct maillon_s* next;
};
typedef struct maillon_s maillon;

typedef maillon* liste;

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

liste enumm_chordless_path(liste* G, int s, int t, liste Q, int taille){
	if(liste_mem(t, G[s])){
		return ajoute_sommet(Q, t); 
	}
	maillon* ptr = G[s];
	while (ptr != NULL){
		liste* G' = 
	}
}
