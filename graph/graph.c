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
graph* ajoute_S(graph* G);
void ajoute_A(graph* G,int a,int b);
bool estdansgraph(graph* G,int n);
bool estvoisin(graph* G,int u ,int v);
bool estarete(graph* G,int a,int b);
bool estchemin(graph* G,maillon* chemin);
bool existechemin(graph* G,int u,int v,int etape);
bool estconexe(graph* G);
int* voisins(graph* G,int s);
int** adjacence (graph* G);
int ** mat_adj(graph* G);



//operation autres

int** mult(int** m1,int** m2,int t){
    int** mat = malloc (t* sizeof(int*));
    for (int i = 0;i < t ;i++){
        mat[i]= malloc(t* sizeof(int));
    }
    for (int i = 0;i < t;i++ ){
        for (int j = 0;j < t;j++ ){
            int s = 0;
            for (int k = 0;k<t;k++){
                if (m1[i][k]*m2[k][j]>0)s= 1;
            }
            mat[i][j] = s;
        }
    }
    return mat ;
}



//constructions graphe

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

//acquisition information

bool estdansgraph(graph* G,int n){return ((n <= G->nbs)&&(n>= 1));}

bool estvoisin(graph* G,int u,int v){
    int* vois_u = voisins(G,u);
    for (int i = 1 ;i<= vois_u[0];i++){
        if (vois_u[i]==v ){
            free (vois_u);
            return true;
        }
    }
    free(vois_u);
    return false ;
}

bool estarete(graph*G,int a,int b){  //meme chose que estvoisin mais defini avec G->arete
    maillon* act = G->aretes;
    while (act != NULL){
        if (act->a == a && act->b == b)return true;
    }
    return false;
}

bool estchemin(graph* G,maillon* chemin){
    return (chemin == NULL)||(estarete(G,chemin->a,chemin->b)&&(chemin->next==NULL||chemin->b == chemin->next->a)&&estchemin(G,chemin->next));
}

bool existechemin(graph* G,int u,int v,int etape){
    if (etape < G->nbs){
        int* vois = voisins(G,u);
        bool res = false;
        for (int i= 1 ; i <= vois[0];i++){
           if (vois[i] == v) return true;
           res += existechemin(G,vois[i],v,etape+1);
        }
        return res;
    }
    else{
        return u == v;
    }
}

bool estconexe(graph* G){
    int ** mat = mat_adj(G); 
    int **res = mat_adj(G);
    for(int i = 1;i<G->nbs ;i++){
        int** tmp = res;
        res = mult(res,mat,G->nbs);
        free(tmp);
    }
    for (int i = 0 ;i<G->nbs;i++){
        for (int j = 0 ; j<G->nbs;j++) {
            if (!res[i][j]){
                free(mat);
                free(res);
                return false;
            }
        }
    }
    free(mat);
    free(res);
    return true;
}


//constructions autres

int* voisins(graph* G,int s){
    assert(estdansgraph(G,s));
    int* vois = malloc(sizeof(int)*G->nbs) ;
    vois[0] = 0;
    maillon* act = G->aretes ;
    while (act != NULL) {if (act->a == s) {
        vois[0]++; 
        vois[vois[0]] = act-> b ;
        } 
        act = act->next;
    }
    return vois;
}

int** adjacence (graph* G){
    int** table = malloc(sizeof(int*)*G->nbs);
    for (int i = 0;i< G->nbs; i++){
        int * ptr = voisins(G,i);
        table[i] = ptr;
    }
    return table;
}

int ** mat_adj(graph* G){
    int** mat = malloc (G->nbs* sizeof(int*));
    for (int i = 0;i < G->nbs ;i++){
        mat[i]= malloc(G->nbs* sizeof(int));
    }
    for (int i = 0;i < G->nbs;i++ ){
        for (int j = 0;j < G->nbs;j++ ){
          if (estarete(G, i, j))mat[i][j] = 1;
          else mat[i][j] = 0 ;
        }
    }
    return mat;
}



int main(){
    graph* circuit = construit(1);
    printf("%d \n",circuit-> sommet [0] );
    libere_graph(circuit);
    return 0;
}