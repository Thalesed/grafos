/*
Busca grafos
Busca em Largura
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

fl * finit(){
	fl *f = (fl *) malloc(sizeof(fl));
	f->ini = f->fim = NULL;
	return f;
}

void fpush(fl *f, int v){
	lst *n = (lst *) malloc(sizeof(lst));
    lst * tmp = f->ini;
	n->val =v;
	n->prox = NULL;

    if (f->ini == NULL){
        f->ini = n;
        f->fim = n;
        return;
    }

    while(tmp->prox != NULL){
        tmp = tmp->prox;
    }

    tmp->prox = n;
    f->fim = n;
}

int fpop(fl *f){
	lst *t;
	int v;
	if(f->ini == NULL){
		printf("Fila vazia!");
		exit(1);
	}
	t = f->ini;
	v = t->val;
	f->ini = t->prox;
	if(f->ini==NULL) 
        f->fim = NULL;
	return v;
}

void fimprime(fl *f){
	lst *q;
    printf(">>");
	for(q=f->ini; q!= NULL; q=q->prox) 
        printf("%d\t",q->val);
    printf("\n");
}

int fvazia(fl *f){
	return (f->ini == NULL);
}

// Breadth-First Search
void bfs(int tam, lst ** faca){
    fl * Q = finit();
    int * d = (int *)malloc(tam * sizeof(int));
    char * c = (char *)malloc((tam+1) * sizeof(char));
    int n, i =0;
    lst * tmp;

    for(int i=0;i<tam;i++){
        c[i] = 'w';
    }
    for(int i=0;i<tam;i++){
        d[i] = 0;
    }

    c[tam] = '\0';

    n  = lstget(faca[i], 0);
    fpush(Q, n);


    while (fvazia(Q ) == 0 && i<tam){
        fimprime(Q);
        printf("%s\n", c);
        c[n-1] = 'b';
        tmp = faca[n-1]->prox;
        while(tmp != NULL && c[tmp->val-1] != 'w')
            tmp = tmp->prox;

        while(tmp != NULL){
            if(c[tmp->val-1] == 'w'){
                c[tmp->val-1] = 'g';
                fpush(Q, tmp->val);
                d[tmp->val-1] += i+1;
            }
            tmp = tmp->prox;
        }

        fpop(Q);
        //c[n-1] = 'b';
        if (fvazia(Q) == 0)
            n = Q->ini->val;
        i++;
    }
    printf("\nd = "); // Distancia
    for(i=0;i<tam;i++){
        printf("%d  ", d[i]);
    }
    printf("\n");
}

lst ** criaGarfo(int tam){
    int i, j;
    lst ** grf; 

    grf = (lst **)malloc(tam * sizeof(lst *));

    for(i=0;i<tam;i++){
        grf[i] = lst_cria();
        grf[i] = lst_insere(grf[i], i+1);
    }

    for(i=0;i<tam;i++){
        for(j=i+1;j<tam;j++){
            if(rand() % 2 != 0){
                linsere(grf[i], j+1);
                if(i!=j)
                    linsere(grf[j], i+1);
            }
        }
    }
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

void grfFree(int tam, lst ** grf){
    for(int i=0;i<tam;i++){
        lstFree(grf[i]);
    }
}

int main(){
    srand(time(NULL));

    int tam = ((rand() % 6) + 3);
    lst ** grf = criaGarfo(tam);

    
    bfs(tam, grf);

    printColher(grf, tam);
    grfFree(tam, grf);


    return SUCESSO;
}