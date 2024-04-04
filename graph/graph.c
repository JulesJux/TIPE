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

graph* construit(int S){
    graph* circuit = malloc (sizeof (graph));
    int* som = malloc (sizeof (int)*S);
    for (int i= 0 ; i < S;i++)som[i]=i+1;
    circuit->sommet = som;
    circuit->aretes = NULL ;
    circuit->nbs = S;
    return circuit;

}
void libere_m(maillon* M ){
    if (M != NULL){
        libere_m(M-> next);
        free(M);
    }

}
void libere_graph(graph* G){
    free(G -> sommet);
    libere_m(G->aretes);
}

graph* ajoute_S(graph* G){
    int* S1 = G->sommet;
    int* S2 = malloc(sizeof(int)*((G->nbs)+1));
    for (int i = 0 ; i < G->nbs ; i++){
        S2[i] = S1[i];
    }
    S2[G->nbs] = G->nbs +1;
    G->nbs ++;
    G->sommet = S2;
    return G;
}

void ajoute_A(graph* G,int a,int b){
    maillon* ar = malloc(sizeof(maillon));
    ar->a = a;
    ar->b =b;
    ar->next = NULL;
    maillon* act = G->aretes;
    if(act == NULL)G->aretes = ar;
    else{
        while(act->next != ar){
            if (act->next == NULL){
                act->next = ar;
            }
            act = act->next;
        }
    }

}

bool estdansgraph(graph* G,int n){return ((n <= G->nbs)&&(n>= 1));}

/*maillon* voisins(graph* G,int s){
    assert(estdansgraph(G,s));
    maillon* vois = NULL ;
    maillon* act = G->aretes ;
    while (act != NULL) {if 
    
    }
}*/

int main(){
    graph* circuit = construit(1);
    printf("%d \n",circuit-> sommet [0] );
    libere_graph(circuit);
    return 0;
}