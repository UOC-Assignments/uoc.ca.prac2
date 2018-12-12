/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

//INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dos.h>

// DECLARE FUNCTIONS

void getInputParameters(int*, int*, int*);
void initializeUpperTriangleMatrix(int**, int);
void printVector(int*, int);
void resetVector(int*, int);
void printMatrix(int**, int);
void sequentialAlgorithm1(int*, int**, int, int, int);
void sequentialAlgorithm2(int*, int**, int, int, int);
void sequentialBlockAlgorithmJOSEP(int*, int**, int, int, int);
void sequentialBlockAlgorithmJORDI(int*, int**, int, int, int);


// MAIN FUNCTION

int main()
{
    /* 0.1 - declare local variables & pointers*/
    int N, B, X;
    int i = 0;
    int j = 0;
    int **matrix;
    int *vector;
    
    /* 0.2 - get matrix & block sizes */ 
    getInputParameters(&N, &B, &X);
    system("cls");
    printf("0.1 - Matrix Size (N), Block Size (B) and Escalar value (x) Parameter Initialization ---> [OK]\n\n");
    printf("N = %d, B = %d, X = %d\n\n", N,B,X);
    
    /* 0.3 - allocate the matrix */
    matrix = malloc(N * sizeof *matrix);
    for (i=0; i<N; i++)
    {
        matrix[i] = malloc(N * sizeof *matrix[i]);
    }
    
    /* 0.4 - Allocate the results vector */
    vector = malloc(N * sizeof(int));
    
    /* 0.5 - initialize the matrix */
    printf("0.2 - Upper Triangle / Diagonal Matrix Random Initialization ---------------------------> [OK]\n\n");
    initializeUpperTriangleMatrix(matrix, N);
    printMatrix(matrix,N);printf("\n");

    /* 1.0 - Sequential Algorithm */
    printf("1.0 - Sequential Algoritm Execution  ---------------------------------------------------> [OK]\n\n");
    sequentialAlgorithm1(vector, matrix, N, X, 0);
	printf("\n");
    printVector(vector,N);
    resetVector(vector,N); //WE DO REINITIALIZE THE VECTOR BEFORE USING IT AGAIN TO STORE THE RESULT OF OTHER FUNCTIONS
    
    /* 1.1.A -  Block Sequential Algorithm 
    printf("1.1.A - Sequential Block Algorithm Execution (JOSEP) ------------------------------------> [OK]\n\n");
    sequentialBlockAlgorithmJOSEP(vector, matrix, N, B, X);
	printf("\n");
    printVector(vector,N);
    resetVector(vector,N); //WE DO REINITIALIZE THE VECTOR BEFORE TO USE IT AGAIN TO STORE THE RESULT OF OTHER FUNCTIONS */
    
    /* 1.1.B -  Block Sequential Algorithm */
    printf("1.1.B - Sequential Block Algorithm Execution (JORDI) ------------------------------------> [OK]\n\n");
    sequentialBlockAlgorithmJORDI(vector, matrix, N, B, X);
	printf("\n");
    printVector(vector,N);
    resetVector(vector,N); //WE DO REINITIALIZE THE VECTOR BEFORE TO USE IT AGAIN TO STORE THE RESULT OF OTHER FUNCTIONS
	    
    /* 1.1 -
    
    /* 1.2 - Block parallel Algorithm */
      
    //MORE WORKLOAD
    
    /* z.1 - print Matrix */ 
    //printMatrix(matrix,N,N);
    
    /* z.z - deallocate the matrix */
    for (i=0; i<N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    
    return 0;
}

// FUNCTIONS

/*
*
* FUNCIÓ: 
* .....
*
* INPUT:
* OUTPUT: 
*
*/

void getInputParameters(int *N, int *B, int *X)
{
    int n,b,x;
    while(1){
    system("cls");printf("Introdueix la mida de la matriu (N): ");
    scanf("%d",&n);printf("\n");
    system("cls");printf("Introdueix la mida dels blocs (B): ");
    scanf("%d",&b);printf("\n");
    system("cls");printf("Introdueix un nombre escalar per a multiplicar per la matriu triangular (x): ");
    scanf("%d",&x);printf("\n");
    // si B i N són multiples sortir del loop (els inputs de B i N s'han passat per referència, no cal retorn)
    if (n % b == 0) {*N = n; *B = b; *X = x; break;}
    // si no B i N no són multiples seguir amb el loop
    else {printf("B no és múltiple de N. Try again...\n");}
    }
}

/*
*
* FUNCIÓ: void initializeUpperTriangleMatrix(int** matrix, int N)
* INICIALITZA UNA MATRIU NxN TRIANGULAR SUPERIOR SEQUENCIALMENT SENSE BLOCS.    
*
* INPUT: Punter a enter
* OUTPUT: mida de matriu "N" i de bloc "B" (per referència)
*
*/

void initializeUpperTriangleMatrix(int** matrix, int N)
{
    int k=0; int m=0; int r=0;

    for (k=0;k<N;k++){
        for (m=0;m<N;m++){
            if (k>m){
                matrix[k][m] = 0;
            }
            else {
				r = rand(); // <-- GENERATE RANDOM INT
                matrix[k][m] = 1;//r / 100000000;
            }
        }
    }
}


/*
*
* FUNCIÓ: void printMatrix(row, columns);
* IMPRIMEIX MATRIU FORMATADA PER PANTALLA
*
* INPUT: punter a matriu i mida N
* OUTPUT: N/A
*
*/

void printMatrix(int** matrix, int N)
{
    int i,j;
    for (i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            printf("%5d", matrix[i][j]);
        }   
    printf("\n");
    }
}

/*
*
* FUNCIÓ: void printMatrix(row, columns);
* IMPRIMEIX MATRIU FORMATADA PER PANTALLA
*
* INPUT: punter a matriu i mida N
* OUTPUT: N/A
*
*/

void printVector(int* v, int N)
{
    int i;
    printf("vector = { ");
    for (i=0; i<N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("}\n\n");
}

void resetVector(int* v, int N)
{
    int i;
    for (i=0; i<N; i++)
    {
        v[i] = 0;
    }
}

/*
*
* FUNCIÓ: void sequentialAlgorithm(int** matrix, int N);
* .....
*
* INPUT: 
* OUTPUT: 
*
*/

void sequentialAlgorithm1(int* v, int** m, int N, int x, int I){
    int i,j,k,z;
    z=0;
    for (i=I; i<N; i++)
    {
        v[i] = 0; //inicialitzem la posició del vector a zero
        for (k=0;k<z;k++){printf("     ");} // WE PRINT "Z" SPACES TO THE LEFT IN ORDER TO ALIGN ROWS TO THE RIGHT SO WE CAN VISUALIZE THE SEQUENCE PROPERLY
        for(j=i; j<N; j++)
        {
            v[i] = v[i] + (x * m[i][j]); 
			
            printf("%5d", x * m[i][j]);
            Sleep(250); // DELAY TO HUMANLY DISPLAY MATRIX FOLLOW PATH
        }
        printf("\n");
		z++;
    }
}

void sequentialAlgorithm2(int* v, int** m, int N, int x, int I){
    int i,j,k,z;
    z=0;
    for (i=I; i<N; i++)
    {
        v[i] = 0; //inicialitzem la posició del vector a zero
        for(j=0; j<N; j++)
        {
            v[i] = v[i] + (x * m[i][j]); 
			
            printf("%5d", x * m[i][j]);
            Sleep(250); // DELAY TO HUMANLY DISPLAY MATRIX FOLLOW PATH
        }
        printf("\n");
		z++;
    }
}

void sequentialBlockAlgorithmJOSEP(int* V, int** M, int N, int B, int x)
{
	int i, j, m, k;
	m = 0; k = 0;
	for (i=0; i<N; i=i+B)
	{
		for (j=i; j<N; j=j+B)
		{
			for (m=i; m<(j+B); m++)
			{
				if(i==j)
				{
					for (k=m; k<(j+B); k++)
					{
						V[m]=V[m] + x * M[m][k];						
					}
				}
				else
				{
					for (k=j; k<(j+B); k++)
					{
						V[m]=V[m] + x * M[m][k];
					}			
				}		
			}
			printf("%5d", x * M[m][k]);
            Sleep(250); // DELAY TO HUMANLY DISPLAY MATRIX FOLLOW PATH		
		}
		printf("\n");
	}
}

void sequentialBlockAlgorithmJORDI(int* V, int** M, int N, int B, int x)
{
    int i,j;
    for(i=0; i<N; i=i+B)
	{
		for(j=i; j<N; j=j+B)
		{
			printf("i = %d, j = %d \n",i,j);
			if (i==j){sequentialAlgorithm1(V, M, B, x, i);}
			else{sequentialAlgorithm2(V, M, B, x, i);}			
	    }
	    printf("i = %d, j = %d \n",i,j);
    }
    printf("FINAL BUCLE FOR --> i = %d, j = %d \n",i,j);
}

void sequentialBlockAlgorithmJORDI_BAK(int* V, int** M, int N, int B, int x)
{
    int i,j,m,k;
    for(i=0; i<N; i+B)
	{
		for(j=i; j<N; j+B)
		{
		    for (m=j; m<B; m++)
		    {
		        V[m] = 0; //inicialitzem la posició del vector a zero
		        for(k=0; k<B; k++)
		        {
		            V[m] = V[m] + (x * M[m][k]);  
		            printf("%5d", x * M[m][k]);
		            Sleep(250); // DELAY TO HUMANLY DISPLAY MATRIX FOLLOW PATH
		        }
		        printf("\n");
		    }
		    printf("\n");
	    }
    }
}
