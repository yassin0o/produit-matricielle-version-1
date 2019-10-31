//YAHIAOUI MOHAMED YASSINE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NBthread 3
#define NBLigne_A 5
#define NBColonne_A 5
#define NBLigne_B 5
#define NBColonne_B 5
int A[NBLigne_A][NBColonne_A];
int B[NBLigne_B][NBColonne_B];
int resultp[NBLigne_A][NBColonne_B];
int results[NBLigne_A][NBColonne_B];
int BlockSize;
BlockSize=NBLigne_A/NBthread;
void *produit(void *id);



int main(int argc,char *argv[]){
	int th,rc,i,j,m;
	
	pthread_t threads[NBthread];
	double TDeb,TFin,TExSec,TExParal;
	
	srand(time(NULL));
	
	
	
	//initialisation des matrices
	for(i=0;i<NBLigne_A;i++){
		for(j=0;j<NBColonne_A;j++){
			A[i][j]=rand()%NBLigne_A;
		}
	}
	for(i=0;i<NBLigne_B;i++){
		for(j=0;j<NBColonne_B;j++){
			B[i][j]=rand()%NBLigne_B;
		}
	}
	for(i=0;i<NBLigne_A;i++){
		for(j=0;j<NBColonne_B;j++){
			
			resultp[i][j]=0;
			results[i][j]=0;
		}
	}
	
	
	
	
	//affichage des matrices A et B
	printf("Matrice A: \n");
	for(i=0;i<NBLigne_A;i++){
		for(j=0;j<NBColonne_A;j++){
			printf("%d  ",A[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrice B: \n");
	for(i=0;i<NBLigne_B;i++){
		for(j=0;j<NBColonne_B;j++){
			printf("%d  ",B[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	//debut de calcule sequantielle
	TDeb=clock();
	for(m=0;m<NBLigne_A;m++){
		for(i=0;i<NBColonne_B;i++){
			for( j=0;j<NBLigne_B;j++){
				results[m][i]=results[m][i]+A[m][j]*B[j][i];
			}
		}
	}
	TFin=clock();
	TExSec=(double)(TFin-TDeb)/CLOCKS_PER_SEC;
	
	
	
	
	//affichage du resultat sequentielle
	printf("resutat sequantielle : \n");
	for(i=0;i<NBLigne_A;i++){
		for(j=0;j<NBColonne_B;j++){
			printf("%d  ",results[i][j]);
		}
		printf("\n");
	}
	printf("le temps d execution =%f\n",TExSec);
    
	
	
	
	
	//debut de calcule paralelle
	TDeb=clock();
	for(th=0;th<NBthread;th++){
		rc=pthread_create(&threads[th],NULL,produit,(void *)th);
		if(rc){
			printf("err 0");
			exit(-1);
		}
	}

	for(th=0;th<NBthread;th++){
		pthread_join(threads[th],NULL);
	}
	TFin=clock();
	TExParal=(double)(TFin-TDeb)/CLOCKS_PER_SEC;
	
	
	
	
	
	//affichage du resultat paralelle
	printf("resutat paralelle : \n");
	for(i=0;i<NBLigne_A;i++){
		for(j=0;j<NBColonne_B;j++){
			printf("%d  ",resultp[i][j]);
		}
		printf("\n");
	}
	printf("le temps d execution =%f\n",TExParal);

	
}



void *produit(void *id){
	long tid=*((long*)(&id));
	int i,j,z,start,end;
	

	start=tid*BlockSize;
	if(tid!=NBthread-1){
	    end=start+BlockSize;
	}else{
	    end=NBLigne_A;
		
	}

    for(z=start;z<end;z++){
		for(i=0;i<NBColonne_B;i++){
			for( j=0;j<NBLigne_B;j++){
				resultp[z][i]=resultp[z][i]+A[z][j]*B[j][i];
			}
		}
	}
}

