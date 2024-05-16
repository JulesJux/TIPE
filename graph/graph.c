#include "graph.h"

int main(){
	int sommets = 3;
    	graph* circuit = construit(sommets);
	ajoute_A(circuit, 0, 1);
	ajoute_A(circuit, 1, 2);
	ajoute_A(circuit, 2, 0);
	print_mat(circuit);
	printf("\n");
	suppr_A(circuit, 2, 0);
	print_mat(circuit);
	ajoute_S(circuit);
	printf("\n");
	print_mat(circuit);
	printf("\n");
	ajoute_A(circuit, 3, 0);
	ajoute_A(circuit, 2, 3);
	print_mat(circuit);
	printf("\n");
	int* arb = arborescence(circuit, 0);
	for(int i =0; i < circuit->nbs; i++){
		printf("%d ", arb[i]);
	}
	//int* vois = voisins(circuit, 0);
	//printf("%d\n", vois[1]);
	printf("\n");
	libere_graph(circuit);	
    return 0;
}

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
    for (int i= 0 ; i < S;i++){
	    som[i]=i+1;
    }
    circuit->sommet = som;
    circuit->aretes = NULL;
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

void libere_mat(int** mat, int taille){
	for(int i = 0; i < taille; i++){
		free(mat[i]);	
	}
	free(mat);
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
    assert(estdansgraph(G, a) && estdansgraph(G, b));
    if (!estvoisin(G, a, b)){
	maillon* new = malloc(sizeof(maillon));
	new->a = a;
	new->b = b;
	new->next = G->aretes;
	G->aretes = new;
    }
}

//acquisition information

bool estdansgraph(graph* G,int s){return ((s < G->nbs)&&(s>= 0));}

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

bool estchemin(graph* G,maillon* chemin){
    return (chemin == NULL)||(estvoisin(G,chemin->a,chemin->b)&&(chemin->next==NULL||chemin->b == chemin->next->a)&&estchemin(G,chemin->next));
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
    int* vois = malloc(sizeof(int)*G->nbs+1) ;
    vois[0] = 0;
    maillon* act = G->aretes ;
    while (act != NULL) {
	if (act->a == s) {
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

int** mat_adj(graph* G){
    int** mat = malloc (G->nbs* sizeof(int*));
    for (int i = 0;i < G->nbs ;i++){
        mat[i]= malloc(G->nbs* sizeof(int));
    }
    for (int i = 0;i < G->nbs;i++ ){
        for (int j = 0;j < G->nbs;j++ ){
          if (estvoisin(G, i, j)){
		  mat[i][j] = 1;
	  }
          else {
		  mat[i][j] = 0 ;
	  }
        }
    }
    return mat;
}

void suppr_A(graph* G, int a, int b){
	if(estvoisin(G, a, b)){
		maillon* tmp = NULL;
		maillon* act = G->aretes;
		if(act->a == a && act->b == b){
			G->aretes = act->next;
			free(act);
		}
		else{
		while(act->next != NULL){
			if(act->next->a == a && act->next->b == b){
				tmp = act->next;	
				act->next = act->next->next;
				free(tmp);
		}
			act = act->next;
		}
	}}
}

void parcours(graph* G, int u, bool* dejaVu, int* peres){
	dejaVu[u] = true;
	int* vois = voisins(G, u);
	for(int j = 1; j <= vois[0]; j++){
		int v = vois[j];
		if(!dejaVu[v]){
			peres[v] = u;
			parcours(G, v, dejaVu, peres);
		}
	}
}

int* arborescence(graph* G, int u){
	bool* dejaVu = malloc(sizeof(bool)*G->nbs);
	for(int i = 0; i < G->nbs; i++){
		dejaVu[i] = false;
	}
	int* peres = malloc(sizeof(int)*G->nbs);
	for(int i = 0; i < G->nbs; i++){
		peres[i] = 0;
	}
	peres[u] = -1;
	parcours(G, u, dejaVu, peres);
	free(dejaVu);
	return peres;
}

int* enum_chordless_path(int** G, int s, int, t, int* Q){ // G -> graphe (en liste d'adjascence); s, t -> sommets; Q -> liste de sommets
	
}

// Affichage

void print_mat(graph* G){
	int** mat = mat_adj(G);
	for(int i = 0; i < G->nbs; i++){
		for(int j = 0; j < G->nbs; j++){
			printf("%d, ", mat[i][j]);
		}
		printf("\n");
	}
	libere_mat(mat, G->nbs);
}


