//21/12/2015

#include <stdio.h>
#include <stdlib.h>
#define O 3
#define DIM (O*O)

int nodupes(int a[DIM]){
    int hits[DIM];
    int i;
    for (i=0; i<DIM;i++) hits[i] = 0;
    for (i=0; i<DIM;i++) {
        if (a[i]!=0) {
            if (hits[a[i]-1]>0)
                return 0;
            hits[a[i]-1]++;
        }
    }
    return 1;
}

int* estrai_riga(int m[DIM][DIM], int riga) {
    int *ritorno=malloc(sizeof(int)*DIM);
    int i;
    for (i=0;i<DIM;i++){
        ritorno[i] = m[riga][i];
    }
    return ritorno;
}

int* estrai_colonna(int m[DIM][DIM], int colonna) {
    int *ritorno=malloc(sizeof(int)*DIM);
    int i;
    for (i=0;i<DIM;i++){
        ritorno[i] = m[i][colonna];
    }
    return ritorno;
}
int* estrai_riquadro(int m[DIM][DIM], int x, int y) {
    int *ritorno=malloc(sizeof(int)*DIM);
    int i,j,h=0;
    for (i=0;i<O;i++)
        for (j=0;j<O;j++)
            ritorno[h++] = m[x+1][y+1];
	return ritorno;
}

int corretto(int m[DIM][DIM]) {
    //verifica che le righe siano corrette
    int i, j;
    for (i=0;i<DIM;i++) {
        if (!nodupes(estrai_riga(m, i)))
            return 0;
    }
    for (i=0;i<DIM;i++) {
        if (!nodupes(estrai_colonna(m, i)))
            return 0;
    }
    for (i = 0;i<O;i++)
        for(j=0;j<0;j++)
            if(!nodupes(estrai_riquadro(m, i*O, j*O)))
                return 0;
    return 1;
}

int *prima_libera(int m[DIM][DIM]) {
    int i, j;
    for(i = 0; i<DIM; i++)
        for(j=0;j<DIM;j++)
            if(m[i][j]==0)
                return &(m[i][j]);
    return NULL;
}

int risolvi(int m[DIM][DIM]) {
    
    int *p, i;
    if(corretto(m)==0)
        return 0;
    
    p = prima_libera(m);    
    if (p==NULL) {
        return 1;
    }
    
	if (corretto(m) == 1) {
   		for(i = 1; i<=DIM; i++) {
        	*p = i;
        	if(risolvi(m)==1) return 1;
		}
    }
    *p = 0;
    return 0;
}

void stampa_mbase(int m[DIM][DIM]) {
    int i,j;
    for(i=0;i<DIM;i++) {
        for(j=0;j<DIM;j++) {
            printf("%i\t", m[i][j]);
        }
        printf("\n");
    }
}

void stampa_mfattizza(int m[DIM][DIM]) {
	int i, j;
	for(i=0;i<DIM;i++) {
		for(j=0;j<DIM;j++) {
			if (m[i][j]==0)
				printf("%c\t", ' ');
			if (m[i][j]!=0)
				printf("%i\t", m[i][j]);
			if ((j+1) % 3 == 0)
				printf("|\t");
		}
		printf("\n");
		if ((i+1) % 3 == 0)
			printf("_________________________________________________________________________________________\n\n");
	}
}

int main(){
	int m[DIM][DIM] = {
        {7,1,0,0,0,3,0,0,9},
		{0,0,3,4,2,0,0,0,5},
		{0,0,0,0,0,5,7,6,0},
		{9,0,0,0,1,8,0,7,0},
		{0,6,0,9,0,0,3,0,0},
		{0,0,2,3,0,0,0,1,0},
		{3,0,0,0,8,1,2,0,0},
		{0,0,0,0,0,0,5,9,1},
		{0,7,1,2,5,0,0,0,0}
    };
	printf("Il sudoku iniziale:\n\n\n");
    stampa_mfattizza(m);
    printf("\n");
	printf("ecco la soluzione:\n\n\n");
    risolvi(m);
    stampa_mfattizza(m);
    return 0;
}
