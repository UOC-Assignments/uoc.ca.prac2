/******************************************************************************

                    PRAC2 ARQUITECTURA DE COMPUTADORS - UOC
                       
					   Codi addicional a la pregunta 1.1
						 						 
					 J.MARI�O - J.BERICAT (Tardor 2018/19)

*******************************************************************************/

//INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// DECLARE FUNCTIONS

void getInputParameters(int*, int*, int*);
void initializeUpperTriangleMatrix(int**, int);
void printVector(int*, int);
void resetVector(int*, int);
void printMatrix(int**, int);
void sequentialAlgorithm0(int*, int**, int, int, int);
int sequentialAlgorithm1(int**, int, int, int);
int sequentialAlgorithm2(int**, int, int, int, int);
void sequentialBlockAlgorithm(int*, int**, int, int, int);


// MAIN FUNCTION

int main()
{
	while(1)
	{
	    /* 0.1 - declare local variables & pointers*/
	    int N, B, X, Q;
	    float q;
	    int i = 0;
	    int j = 0;
	    int **matrix;
	    int *vector;
	    int *vectorBlock;
	    
	    /* 0.2 - get matrix & block sizes */ 
	    getInputParameters(&N, &B, &X);
	    system("cls");
	    printf("0.1 - Matrix Size (N), Block Size (B) and scalar value (x) Parameters Initialization ---> [OK]\n\n");
	    printf("N = %d, B = %d, X = %d\n\n", N,B,X);
	    
	    /* 0.3 - allocate the matrix */
	    matrix = malloc(N * sizeof *matrix);
	    for (i=0; i<N; i++)
	    {
	        matrix[i] = malloc(N * sizeof *matrix[i]);
	    }
	    
	    /* EL vector tindr� com a m�xim mida Q=(N^2/B^2), (comptant les posicions de la matriu que queden 
		per sota de la diagonal, o sigui quedaran posicions del vector en desus) en el cas que apliquem 
		l'algorisme per blocs i N en el cas que apliquem el seq��ncial sense blocs. UTilitzem dos vectors 
		diferents, un per a cada cas. */
	    Q = (N*N)/(B*B);
	    //Q = ((((N*N)-N)/2)+N)/(B*B); --> INTENT FALLIT (PER� CREC QUE PROPER) DE CALCULAR EL NOMBRE EXACTE DE BLOCS
	    
	    /* Allocate the results vectors */
	    vector = malloc(N * sizeof(int));
	    vectorBlock = malloc(Q * sizeof(int));
	    
	    /* 0.4 - initialize the matrix */
	    printf("0.2 - Upper Triangle / Diagonal Matrix Random Initialization ---------------------------> [OK]\n\n");
	    initializeUpperTriangleMatrix(matrix, N);
	    printMatrix(matrix,N);printf("\n");
	
	    /* 1.0 - Sequential Algorithm */
	    printf("1.0 - Sequential Algorithm Execution  ---------------------------------------------------> [OK]\n\n");
	    resetVector(vector,N); //WE DO REINITIALIZE THE VECTOR BEFORE USING IT AGAIN TO STORE THE RESULT OF OTHER FUNCTIONS
	    sequentialAlgorithm0(vector, matrix, N, X, 0);printf("\n");
		printVector(vector,N);	    
	         
	    /* 1.1 - Sequential Block Algorithm */
	    printf("1.1 - Sequential Block Algorithm Execution ------------------------------------> [OK]\n\n");
	    resetVector(vectorBlock,Q);
	    sequentialBlockAlgorithm(vectorBlock, matrix, N, B, X);printf("\n");
	    printVector(vectorBlock,Q);
		    
	    /* 1.2 - Parallel Block Algorithm */
	    //TO-DO
	
	    /* 2.1 - deallocate the matrix */
	    for (i=0; i<N; i++)
	    {
	        free(matrix[i]);
	    }
	    free(matrix);
	    free(vector);
	    free(vectorBlock);
	    
	    system("pause");
	}
    return 0;
}

// FUNCTIONS

/****************************************************************
* FUNCI�: void getInputParameters()

* DESCRIPCI�: CAPTURA ELS PAR�METRES DE PROGRAMA (MIDA DE MATRIU "N",
			  MIDA DE BLOC "B" I ESCALAR "X") I ELS DESA A LES VARIABLES
			  CORRESPONENTS. COM QUE NO EXISTEIX PARALEL�LITZACI�,
			  L'�NIC PROC�S ACTIU TINDR� ACC�S DEDICAT A LA SECCI�
			  CR�TICA (MEM�RIA DADES), FET PEL QUAL NO ES PODEN PRODU�R
			  CONFLICTES DE DADES.
*
* INPUT: n/a

* OUTPUT: Variables de sortida per refer�ncia N, B i X
*****************************************************************/

void getInputParameters(int *N, int *B, int *X)
{
    int i,n,b,x;
    while(1){
	    system("cls");printf("Introdueix la mida de la matriu (N): ");
	    scanf("%d",&n);printf("\n");
	    system("cls");printf("Introdueix la mida dels blocs (B): ");
	    scanf("%d",&b);printf("\n");
	    system("cls");printf("Introdueix un nombre escalar per a multiplicar per la matriu triangular (x): ");
	    scanf("%d",&x);printf("\n");
	    // si B i N s�n multiples sortir del loop (els inputs de B i N s'han passat per refer�ncia, no cal retorn)
	    if (n % b == 0) {*N = n; *B = b; *X = x; break;}
	    // si no B i N no s�n multiples seguir amb el loop
	    else {
	    	system("cls");
			printf("%d no es multiple de %d. Try again",n,b);
			for (i=0;i<10;i++){
				printf("."); //LOADER....
				Sleep(250);
			}
		}
    }
}

/****************************************************************
* FUNCI�: void initializeUpperTriangleMatrix()

* DESCRIPCI�: INICIALITZA UNA MATRIU NxN TRIANGULAR 
* 			  SUPERIOR SEQUENCIALMENT SENSE BLOCS.  
*
* INPUT: Punter a enter

* OUTPUT: mida de matriu "N" i de bloc "B" (per refer�ncia)
*****************************************************************/

void initializeUpperTriangleMatrix(int** matrix, int N)
{
    int i=0; int j=0; 
    
    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            if (i>j){
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = 1;
            }
        }
    }
}


/****************************************************************
* FUNCI�: void printMatrix();

* DESCRIPCI�: IMPRIMEIX MATRIU FORMATADA PER PANTALLA
*
* INPUT: punter a matriu i mida N de la matriu

* OUTPUT: N/A
*****************************************************************/

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


/****************************************************************
* FUNCI�: void printVector();

* DESCRIPCI�: IMPRIMEIX VECTOR FORMATAT PER PANTALLA 
*
* INPUT: punter a matriu i mida N de la matriu

* OUTPUT: N/A
*****************************************************************/

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


/****************************************************************
* FUNCI�: void resetVector();

* DESCRIPCI�: REINICIALITZA A ZERO LES POSICIONS DEL VECTOR
*			  V DE RESULTATS
*
* INPUT: punter a vector i mida N (MAX) del mateix

* OUTPUT: vector de resultats per referencia
*****************************************************************/

void resetVector(int* v, int N)
{
    int i;
    for (i=0; i<N; i++)
    {
        v[i] = 0;
    }
}


/****************************************************************
* FUNCI�: void sequentialAlgorithm0();

* DESCRIPCI�: REALITZA UN RECORREGUT DE LA MATRIU TRIANGULAR 
*			  SUPERIOR EN L'ORDRE PROPOSAT A L'ENUNCIAT DE LA 
*			  PRAC2, PREVI A LA PREGUNTA 1.1. EMMAGATZEMA EL 
*			  PRODUCTE ESCALAR DE "X" I "M" A UN VECTOR DE 
*			  RESULTATS "V"
*
* INPUT: Matriu M i mida N, escalar X per a fer el producte amb M
*		 i els �ndexs "i" i "j" per a seg�ir l'ordre en elrecorregut 
*		 de la matriu.

* OUTPUT: Es desa el resultat sumatori a V per refer�ncia. Cada 
		  posici� del vector correspon al sumatori d'una linia 
		  de la matriu (elements amb valors, els que estan per 
		  sobre de la diagonal)
*****************************************************************/

void sequentialAlgorithm0(int* v, int** m, int N, int x, int I){
    int i,j,k,z;
    z=0;
    for (i=I; i<N; i++)
    {
        v[i] = 0; //inicialitzem la posici� del vector a zero
        for (k=0;k<z;k++){printf("     ");} // WE PRINT "Z" SPACES TO THE LEFT IN ORDER TO ALIGN ROWS TO THE RIGHT SO WE CAN VISUALIZE THE SEQUENCE PROPERLY
        for(j=i; j<N; j++)
        {
            v[i] = v[i] + (x * m[i][j]); 
			
            printf("%5d", x * m[i][j]);
            Sleep(125); // DELAY TO HUMANLY DISPLAY MATRIX FOLLOW PATH
        }
        printf("\n");
		z++;
    }
}


/****************************************************************
* FUNCI�: sequentialAlgorithm1() --> SIMULA UNA "SOBREC�RREGA" 
									 DE JAVA EN C DE LA FUNCI� 
									 sequentialAlgorithm0()

* DESCRIPCI�: REALITZA EL RECORREGUT DELS ELEMENTS QUE QUEDEN
* 			  PER SOBRE DE LA DIAGONAL (INCLOSA) DELS BLOCS 
*			  DE LA MATRIU ON EL PRIMER ELEMENT DEL
*			  BLOC �S "i == j". EL RECORREGUT ES REALITZA 
*			  EN L'ORDRE INDICAT A L'ENUNCIAT DE LA PRAC2, 
*			  PREGUNTA 1.1, I EMMAGATZEMA EL PRODUCTE 
*			  ESCALAR DE "X" I "M" A UN VECTOR DE RESULTATS "V"
*
* INPUT: Matriu M i mida N, escalar X per a fer el producte amb M
*		 i els �ndexs "i" i "j" per a seg�ir l'ordre en elrecorregut 
*		 de la matriu.
*
* OUTPUT: Retorna el valor de V[i] que ha de contenir una de les 
*		  posicions del vector v. Correspon al sumatori del valors
*		  de tots elements d'un sol bloc
*****************************************************************/

int sequentialAlgorithm1(int** m, int N, int x, int I){
    int i,j,k,z,r;
    z=0;r=0;
    for (i=I; i<N+I; i++)
    {
    	/* WE PRINT "Z" SPACES TO THE LEFT IN ORDER TO ALIGN ROWS 
		TO THE RIGHT SO WE CAN VISUALIZE THE SEQUENCE PROPERLY */
        for (k=0;k<z;k++){printf("     ");} 
        for(j=i; j<N+I; j++)
        {
            r = r + (x * m[i][j]); 			
            printf("%5d", x * m[i][j]);
            /* DELAY TO DISPLAY THE PROCESS IN A "HUMAN-FRIENDLY"
            FASHION */
            Sleep(250); 
        }
        printf("\n");
		z++;
    }
	return r;
}


/****************************************************************
* FUNCI�: sequentialAlgorithm1() --> SIMULA UNA "SOBREC�RREGA" 
									 DE JAVA EN C DE LA FUNCI� 
									 sequentialAlgorithm0()
*
* DESCRIPCI�: REALITZA EL RECORREGUT DE TOTS ELS ELEMENTS D'UN BLOC 
*			  DE LA MATRIU (AQUELLS EN QU� CAP DELS SEUS ELEMENTS 
*			  CONT� UN VALOR NUL). EL RECORREGUT ES REALITZA EN 
*			  L'ORDRE INDICAT A L'ENUNCIAT DE LA PRAC2, PREGUNTA 1.1,
*			  I EMMAGATZEMA EL PRODUCTE ESCALAR DE "X" I "M" A UN 
*			  VECTOR DE RESULTATS "V"
*
* INPUT: Matriu M i mida N, escalar X per a fer el producte amb M
*		 i els �ndexs "i" i "j" per a seg�ir l'ordre en elrecorregut 
*		 de la matriu.
*
* OUTPUT: Retorna el valor de V[i] que ha de contenir una de les 
*		  posicions del vector v. Correspon al sumatori del valors
*		  de tots elements d'un sol bloc
*****************************************************************/

int  sequentialAlgorithm2(int** m, int N, int x, int I, int J)
{
    int i,j,z,r;
    r = 0;
    if (m[I][J]!=0)
	{	
	    for (i=I; i<N+I; i++)
	    {
	        for(j=J; j<N+J; j++)
	        { 
				r = r + (x * m[i][j]) ;
	            printf("%5d", x * m[i][j]);
	            /* DELAY TO DISPLAY THE PROCESS IN A "HUMAN-FRIENDLY"
           	 	FASHION */
	            Sleep(250);
	        }
	        printf("\n");
	    }
    }   
	return r;
}


/****************************************************************
* FUNCI�: void sequentialBlockAlgorithm();
*
* DESCRIPCI�: PROPOSTA DE SOLUCI� PER A LA PREGUNTA 1.1 DE LA 
*			  PR�CTICA2. REALITZA UN RECORREGUT PER BLOCS DE MIDA
*			  QUE S'ENCARREGARAN DE REALITAR EL RECORREGUT DEL BLOC
*			  EN L'ORDRE INDICAT, TAL I COM ES REALITZA A LA FUNCI�
*	 	 	  sequentialAlgorithm0() I QUE IMPLEMENTA L'ALGORITME 
*			  SEQUENCIAL PROPOSAT INICIALMENT.
*			  
* INPUT: Matriu triangular superior M i mida N, mida de cada bloc "B" 
*		 i constant escalar per a realitzar el producte amb M
*
* OUTPUT: S'acutalitza el vector V per refer�ncia amb el resultat 
		  del sumatori d'elements de cada bloc. Cada posici� del 
		  vector V correspon al sumatori d'un bloc (Hi haur�
		  (N^2 / B^2) blocs o posicions a V en total)
*****************************************************************/

void sequentialBlockAlgorithm(int* V, int** M, int N, int B, int x)
{
    int i,j,b;
    
    /* Implementem un comptador de blocs "b" per a adre�arla posici�
    Correcta on desarem el sumatori al vector V (una posici� del 
	vector per bloc) */
    b = 0; 
    
    resetVector(V,N);
    /* Fem un recorregut de les fileres de la matriu de "B en B" elements */
    for(i=0; i<N; i=i+B)
	{
		printf("*** Row #%d ***\n\n",i);
		/* El mateix amb les columnes, fem un recorregut de "B en B", 
		de manera que sempre tindrem un �ndex (i,j) "apuntant" al primer
		element de cada bloc. A partir d'aqu� podem tractar cada bloc com
		si fos una matriu independent amb el mateix algorisme seq��ncial 
		que utilitzavem quan no haviem de dividir la matriu en blocs
		(una mica adaptat per a cada cas que veurem ara, per� les variacions
		s�n petites) */
		for(j=i; j<N; j=j+B)
		{
			printf("Block #%d\n\n",b);
			/*Si el bloc cont� valors nom�s de la diagonal cap
			amunt, aleshores nom�s fem el recorregut de la part de dalt
			i acumulem el sumatori dels valors dels elements a v[i] 
			(par�metre de sortida)*/
			if (i==j)
			{
				V[b] = sequentialAlgorithm1(M, B, x, i);
			}
			/*Si no; en el cas que tots els elements contenen valors, 
			aleshores fem el recorregut de tot els elements del bloc 
			(en els casos en que tot el bloc contingui zeros la 
			crida a la funci� s'acabar� sense consumir cap recurs
			abans de la primera iteraci�, i no actualitzar� v[i])*/
			else
			{
				V[b] = sequentialAlgorithm2(M, B, x, i, j);
			}
			/* Incrementem el comptador de blocs "b" */
			b++;					
	    }
	    printf("\n");
    }
}

