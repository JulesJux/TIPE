#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct maillon_s {
    int a; 
    int b;
    struct maillon_s* next; 
};
typedef struct maillon_s maillon;

struct s_graph{
int* sommet ;
int nbs;
maillon* aretes ; 
};
typedef struct s_graph graph;



int** mult(int** m1,int** m2,int t);
graph* construit(int S);
void libere_m(maillon* M );
void libere_graph(graph* G);
void libere_mat(int** mat, int taille);
graph* ajoute_S(graph* G);
void ajoute_A(graph* G,int a,int b);
bool estdansgraph(graph* G,int s);
bool estvoisin(graph* G,int u ,int v);
bool estchemin(graph* G,maillon* chemin);
bool existechemin(graph* G,int u,int v,int etape);
bool estconexe(graph* G);
int* voisins(graph* G,int s);
int** adjacence (graph* G);
int ** mat_adj(graph* G);
void print_graph(graph* G);
