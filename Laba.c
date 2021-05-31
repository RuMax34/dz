#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iso646.h>

struct Matrix//структура,описывающая матрицу
{
	void** values;
	int lines;
	int columns;
	size_t forcreate;
};

void* forinit;//void* переменная для выделения памяти

//   CREATE MATRIX
struct Matrix* Create(int lines,int columns,size_t forcreate,void* forinit);
struct Matrix* Create(int lines,int columns,size_t forcreate,void* forinit){
	
	struct Matrix* Matrix = malloc(sizeof(struct Matrix));
	Matrix->lines = lines;
	Matrix->columns = columns;
	Matrix->forcreate = forcreate;
	Matrix->values = malloc(forcreate*lines);
	for (int i = 0; i < lines; ++i)
	{
		int8_t** pos = (int8_t**)Matrix->values + i*forcreate;//заполняем матрицу элементами
		memcpy((void**)pos,forinit,forcreate);	
	}
	for (int i = 0; i < lines; ++i)
	{	
	 	Matrix->values[i] = malloc(forcreate*columns);
		for (int j = 0; j < columns; ++j)
			{
				int8_t* pos = (int8_t*)Matrix->values[i] + j*forcreate;
				memcpy((void*)pos,forinit,forcreate);		
			}	
	}
	return Matrix;
}


struct Matrix* DoubleCreate(int lines,int columns,size_t forcreate);//инициализация double матрицы
struct Matrix* DoubleCreate(int lines,int columns,size_t forcreate){
	
	forinit=malloc(forcreate);
	*(double*)forinit = 0.0;
	
	struct Matrix* ResMatrix = Create(lines,columns,forcreate,forinit);
	for (size_t i = 0; i < (size_t)lines;i++)
	{
		for (size_t j = 0; j < (size_t)columns;j++){
			if(scanf("%lf",(double*)(ResMatrix->values[i]+j*forcreate))!=1){
				return 0;
			}
		}	
	}
	free(forinit);
	return ResMatrix;
}

struct Matrix* TranspositionDoubleMatrix(struct Matrix* example);
struct Matrix* TranspositionDoubleMatrix(struct Matrix* example){
	int m,n;
	m = example->lines;
	n = example->columns;
	
	forinit=malloc(example->forcreate);
	size_t tmp = example->forcreate;
	*(double*)forinit = 0.0;
	
	struct Matrix* ResMatrix = Create(n,m,example->forcreate,forinit);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			*(double*)(ResMatrix->values[i]+j*tmp) = *(double*)(example->values[j]+i*tmp);
		}
	}
	return ResMatrix;
}

struct Matrix* MultiplyTwoDoubleMatrix(struct Matrix* first,struct Matrix* second);
struct Matrix* MultiplyTwoDoubleMatrix(struct Matrix* first,struct Matrix* second){
	if(first->columns != second->lines){
		printf("WRONG SIZES OF MATRIX\n");
		return 0;
	}
	int m,n,q;
	m = first->lines;
	n = first->columns;
	q = second->columns;
	forinit=malloc(first->forcreate);
	size_t tmp = first->forcreate;
	*(double*)forinit = 0.0;
	struct Matrix* ResMatrix = Create(first->lines,second->columns,first->forcreate,forinit);
	for(int i = 0; i < m; i++){
	    for(int j = 0; j < q; j++)
	    {
	        *(double*)(ResMatrix->values[i]+j*tmp) = 0;
	        for(int k = 0; k < n; k++){
	        	*(double*)(ResMatrix->values[i]+j*tmp)+=(*(double*)(first->values[i]+k*tmp))*(*(double*)(second->values[k]+j*tmp));
	        }
	    }
	}
	return ResMatrix;
}

struct Matrix* SumTwoDoubleMatrix(struct Matrix* first,struct Matrix* second);
struct Matrix* SumTwoDoubleMatrix(struct Matrix* first,struct Matrix* second){
	if(first->lines != second->lines || first->columns != second->columns){
		printf("WRONG SIZES OF MATRIX\n");
		return 0;
	}

	forinit=malloc(first->forcreate);
	size_t tmp = first->forcreate;
	*(double*)forinit = 0.0;
	struct Matrix* ResMatrix = Create(first->lines,second->columns,first->forcreate,forinit);
	for(int i = 0; i < first->lines; i++){
		for (int j = 0; j < second->columns; j++)
		{
			*(double*)(ResMatrix->values[i]+j*tmp) = *(double*)(first->values[i]+j*tmp) + *(double*)(second->values[i]+j*tmp);
		}
	}
	return ResMatrix;
}

void PrintDoubleMatrix(struct Matrix* Matrix);
void PrintDoubleMatrix(struct Matrix* Matrix){
	for(int i = 0;i < Matrix->lines;i++){
		for(int j = 0;j < Matrix->columns;j++){
			printf("%lf ", *(double*)(Matrix->values[i]+j*Matrix->forcreate));
		}
		printf("\n");
	}
}
//🤡🤡🤡
void PrintDoubleMatrixfcs(struct Matrix* Matrix);
void PrintDoubleMatrixfcs(struct Matrix* Matrix){
    for(int i = 0;i < Matrix->lines;i++){
        for(int j = 0;j < Matrix->columns;j++){
            printf("%.0lf ", *(double*)(Matrix->values[i]+j*Matrix->forcreate));
        }
        printf("\n");
    }
}
void SumString(struct Matrix* Matrix, int* mas, int size, int target);
void SumString(struct Matrix* Matrix, int* mas, int size, int target) {

    for (int i = 0; i < size; i++) {
        for(int j = 0; j< Matrix->columns; j++){
            *(double*)(Matrix->values[target]+j*Matrix->forcreate)  += *(double*)(Matrix->values[mas[i]]+j*Matrix->forcreate);
        }
    }
}





int main(int argc, char const *argv[])
{
	printf("\t\t\tDOUBLE\n");
	int m,n;
	printf("ENTER SIZES OF FIRST DOUBLE MATRIX: lines and columns\n");
	scanf("%d %d",&m,&n);
	printf("\nENTER %d ELEMENTS FOR FIRST DOUBLE MATRIX\n",m*n);
	struct Matrix* first;
	first = DoubleCreate(m,n,sizeof(double));
	printf("\nFIRST DOUBLE MATRIX\n");
	PrintDoubleMatrix(first);

	int a,b;
	printf("ENTER SIZES OF SECOND DOUBLE MATRIX: lines and columns\n");
	scanf("%d %d",&a,&b);
	printf("\nENTER %d ELEMENTS FOR SECOND DOUBLE MATRIX\n",a*b);
	struct Matrix* second;
	second = DoubleCreate(a,b,sizeof(double));
	printf("\nSECOND DOUBLE MATRIX\n");
	PrintDoubleMatrix(second);

	int am,target;
    printf("ENTER AMOUNT OF STRING FOR LINEAR COMBINATION FOR DOUBLE MATRIX\n");
    scanf("%d",&am);
    printf("ENTER TARGET STRING\n");
    scanf("%d",&target);
    int *mas = (int*)calloc(am,sizeof(int));
    printf("\nENTER %d NUMBER STRINGS\n",am);
    for ( int i =0; i< am;i++)
        scanf("%d", mas+i);
    for ( int i =0; i< am;i++)
        printf("%d", *mas+i);


	printf("\nMultiply Two Double Matrix\n");
	if(MultiplyTwoDoubleMatrix(first,second)!=0)
		PrintDoubleMatrix(MultiplyTwoDoubleMatrix(first,second));
	printf("\n");

	printf("\nSum Two Double Matrix\n");
	if(SumTwoDoubleMatrix(first,second)!=0)
		PrintDoubleMatrix(SumTwoDoubleMatrix(first,second));
	printf("\n");

	printf("\nTransposition FIRST Double Matrix\n");
	PrintDoubleMatrix(TranspositionDoubleMatrix(first));
	printf("\n");

	printf("\nTransposition SECOND Double Matrix\n");
	PrintDoubleMatrix(TranspositionDoubleMatrix(second));
	printf("\n");

    printf("\nlinear combination for double matrix  \n");
    SumString(first,mas,am,target);
    PrintDoubleMatrix(first);



	printf("\t\t\tInteger\n");

    printf("\t\t\tInteger\n");
    printf("ENTER SIZES OF FIRST Integer MATRIX: lines and columns\n");
    scanf("%d %d",&m,&n);
    printf("\nENTER %d ELEMENTS FOR FIRST Integer MATRIX\n",m*n);
    struct Matrix* first1;
    first1 = DoubleCreate(m,n,sizeof(double));
    printf("\nFIRST Integer MATRIX\n");
    PrintDoubleMatrixfcs(first1);

    printf("ENTER SIZES OF SECOND Integer MATRIX: lines and columns\n");
    scanf("%d %d",&a,&b);
    printf("\nENTER %d ELEMENTS FOR SECOND Integer MATRIX\n",a*b);
    struct Matrix* second1;
    second1 = DoubleCreate(a,b,sizeof(double));
    printf("\nSECOND Integer MATRIX\n");
    PrintDoubleMatrixfcs(second1);

    printf("ENTER AMOUNT OF STRING FOR LINEAR COMBINATION FOR INTEGER MATRIX\n");
    scanf("%d",&am);
    printf("ENTER TARGET STRING\n");
    scanf("%d",&target);
    int *mas1 = (int*)calloc(am,sizeof(int));
    printf("\nENTER %d NUMBER STRINGS\n",am);
    for ( int i =0; i< am;i++)
        scanf("%d", mas1+i);


    printf("\nMultiply Two Integer Matrix\n");
    if(MultiplyTwoDoubleMatrix(first1,second1)!=0)
        PrintDoubleMatrixfcs(MultiplyTwoDoubleMatrix(first1,second1));
    printf("\n");

    printf("\nSum Two Integer Matrix\n");
    if(SumTwoDoubleMatrix(first1,second1)!=0)
        PrintDoubleMatrixfcs(SumTwoDoubleMatrix(first1,second1));
    printf("\n");

    printf("\nTransposition FIRST Integer Matrix\n");
    PrintDoubleMatrixfcs(TranspositionDoubleMatrix(first1));
    printf("\n");

    printf("\nTransposition SECOND Integer Matrix\n");
    PrintDoubleMatrixfcs(TranspositionDoubleMatrix(second1));
    printf("\n");

    printf("\nlinear combination for integer matrix  \n");
    SumString(first1,mas1,am,target);
    PrintDoubleMatrix(first1);


	return 0;
}