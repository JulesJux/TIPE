#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void create_netlist();
char* traduit_info_code();

int main (void){
	create_netlist();
	return 0;
}

void create_netlist(void){
	FILE* netlist;
	netlist = fopen("circuit1", "w");
	bool continuer = true;
	char reponse;
  	char* code;
	while(continuer){
  		code = traduit_info_code();
		fprintf(netlist, "%s", code);
    		fprintf(netlist, "\n");
		printf("Continuer ? [O/n] \n");
		bool cond = true;
		while(cond){
			scanf("%c", &reponse);
			if(reponse=='O'&&reponse=='o'){
    				cond=false;
        		}
     			if (reponse=='n' || reponse == 'N'){
				continuer = false;
        			cond = false;
    			}
    		}
    	}
	fclose(netlist);
}



int tab[18] = {'V','I','E','F','G','H','B','R','L','C','D','Q','J','M','S','X','K','T'};

bool est_ok (char){
  for(int i = 0 ; i < 18 ; i++ ){
		if (tab[i] == char ){
  	return true ; 
  	}
  }
	return false;
}

char* traduit_info_code (){
	bool* cond = true ;
  
  char* type ;
  while(cond){
  	printf("type de composants : ");
  	scanf("%c",type);
    cond = est_ok(type)
	}
  int nom ;
  scanf("%d")
  
  
  
  
  
  

}









