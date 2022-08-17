/*
Busca grafos
Busca em Profundidade
Thales Eduardo - 203
Coltec - UFMG
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCESSO 0

struct ced {
    int val;
    struct ced* prox;
};

typedef struct  ced lst;

struct fila
{
    lst * ini;
    lst * fim;
};

typedef struct fila fl;

struct grafo{
    int tam;
    char * c;
    lst ** gr;
};
typedef struct grafo gar;

lst* lst_cria(){
	return NULL;
}

lst* lst_insere(lst *l, int i){
	lst *novo=(lst *)malloc(sizeof(lst));
	novo->val=i;
	novo->prox=l;
	return novo;
}

void lstprint(lst *l){
	lst *p;
	for(p=l;p!=NULL;p=p->prox){
		printf("%d\t", p->val);
	}
}

void linsere(lst * l, int n){
    lst * tmp = (lst *)malloc(sizeof(lst));
    tmp->val = n;
    tmp->prox = NULL;
    if(l == NULL)
        return;
    while(l->prox != NULL){
        l =l->prox;
    }
    l->prox = tmp;
}

int lstget(lst * l, int p){
    for(int i=0;i<p;i++){
        if (l == NULL)
            return 0;
        l = l->prox;
    }
    return l->val;
}

gar * criaGarfo(int tam){
    int i, j;
    gar * grf; 


    grf = (gar *)malloc(sizeof(gar));

    grf->gr = (lst **)malloc(tam * sizeof(lst *));
    grf->c = (char *)malloc((tam+1) * sizeof(char));

    for(i=0;i<tam;i++){
        grf->gr[i] = lst_cria();
        grf->gr[i] = lst_insere(grf->gr[i], i+1);
    }

    for(i=0;i<tam;i++){
        for(j=i+1;j<tam;j++){
            if(rand() % 2 != 0){
                linsere(grf->gr[i], j+1);
                if(i!=j)
                    linsere(grf->gr[j], i+1);
            }
        }
    }

    for(i=0;i<tam;i++){
        grf->c[i] = 'w';
    }
    grf->c[tam] = '\0';
    return grf;
}

void printColher(lst ** grf, int tam){
    for(int i=0;i<tam;i++){
        lstprint(grf[i]);
        printf("\n");
    }
}

void lstFree(lst *l){
	lst *p=l;
	while(p!=NULL){
		lst *t=p->prox;
		free(p);
		p=t;
	}
}

void grfFree(gar * grf){
    for(int i=0;i<grf->tam;i++){
        lstFree(grf->gr[i]);
    }
    free(grf->c);
    free(grf);
}

void dfs(gar * grf, int val){
    lst * adj = (grf->gr[val-1])->prox;
    lst * tmp = adj;
    int n;

    grf->c[val-1] = 'b';
    printf("%d\n%s\n", val, grf->c);

    while(tmp != NULL){
        n = tmp->val;
        if(grf->c[tmp->val-1] == 'w'){
            dfs(grf, tmp->val);
            grf->c[tmp->val-1] = 'g';
        }
        tmp = tmp->prox;
    }

}

int main(){
    srand(time(NULL));

    int tam = ((rand() % 6) + 3);
    gar * grf = criaGarfo(tam);

    dfs(grf, 1);

    printColher(grf->gr, tam);
    //grfFree(tam, grf);


    return SUCESSO;
}