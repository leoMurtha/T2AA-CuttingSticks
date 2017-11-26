#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/*52 por que adicionamos os extremos */
#define NCUTS 52
#define MAX_L 1000 
#define cutCost(xi,xj) cuts[xj] - cuts[xi]
/*
    cuts é o vetor de da posicões xi de corte do problema em que c[0] = 0(Start) e c[n] = tamanho do stick(End)
    K é o valor do corte naquele xi e xj, usando memorizacao paradigma de programacao dinamica
*/
int cuts[NCUTS];
int K[NCUTS][NCUTS];

/* Funcao que corta recursivamente o stick e pega o menor corte */
int kFunction(int xi, int xj){
    int cost,min = INT_MAX;

    if(xi + 1 == xj) return 0; /* Caso base, não tem como cortar mais */

    /*PD, se ja foi calculado esse corte*/
    if(K[xi][xj] != -1) return K[xi][xj];

    /*Calculando para os cortes k's usando a equação de recorrencia */
    for(int k = xi + 1; k < xj ; k++){
        cost = kFunction(xi,k) + kFunction(k,xj) + cutCost(xi,xj);
        min = cost < min ? cost:min;
    }
    /*Atualizando valor do corte */
    K[xi][xj] = min;

    return min;
}

int main(int argc, char const *argv[]){
    int l,n;
    
    cuts[0] = 0; /*Corte do comeco é 0*/

    /* Lendo input */
    while(true){
        memset(K,-1,sizeof(K)); /* Nenhum passo memorizado ainda e reset para outros casos */

        scanf("%d",&l); /* Comprimento(length) do stick */

        if(l == 0) break; /* Parar */

        scanf("%d",&n);

        for(int i = 1; i <= n; i++) scanf("%d",&cuts[i]);
        cuts[++n] = l; /* Fim e igual ao tamanho do stick */

        kFunction(0,n);

        printf("The minimum cutting is %d.\n", K[0][n]);
    }

    return 0;
}