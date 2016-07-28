#include "removeRedundantImpl.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int **A;
int **Apower;
int **temparr;

void giveMinImplSet()
{
	int i=0;
	int length =0;
	char array[256];
	
	char* temp_str;
	int N = 0;
	char* token;
	printf("INPUT:\n");
	temp_str = gets(array);
	N = atoi(temp_str);
	
	A=(int**)malloc(sizeof(int*)* N);
	temparr=(int**)malloc(sizeof(int*)* N);
	Apower=(int**)malloc(sizeof(int*)* N);

	for(i=0;i<N;++i)
	{
		A[i]=(int*)calloc(N,sizeof(int));	
		Apower[i]=(int*)calloc(N,sizeof(int));
		temparr[i]=(int*)calloc(N,sizeof(int));
	}


	for (i=0;i<N;i++)
	{
		memset(array,0,sizeof(array));
		gets(array);
		token = strtok(array," ");
		while (token!=NULL)
		{
			if(strcmp(token,"\n") == 0)
				break;
			
			A[i][atoi(token)] = 1;
			Apower[i][atoi(token)] = 1;
			token = strtok(NULL," ");
			length++;
		}

	}
matrixExpAndComb(A,N);
freeMemory(N);
}

void matrixExpAndComb(int **A,int N)
{
	int a =0,b=0,i=1,j=0,k=0,l=0,m=0,count=0,**S;

	S=(int**)malloc(sizeof(int*)* N);

	for(i=0;i<N;++i)
	{
		S[i]=(int*)calloc(N,sizeof(int));	
	}

	//Traverse through the matrices and perform OR to get S
	for (i=2;i<=N;i++)
	{
		Apower = matrixMultiply(Apower,A,N);
		for (j=0;j<N;j++)
		{
			for(k=0;k<N;k++)
			{   
				S[j][k] = S[j][k] || Apower[j][k]; 
			}
		}
		
	}
	//once we have S, now traverse through S and remove all the 1s in A that are 1s in S also
	printf("OUTPUT:\n");
	for (l=0;l<N;l++)
		{ 
			count =0;
			for(m=0;m<N;m++)
			{
				if (S[l][m]&&A[l][m])
				{
					A[l][m] =0;
				}
				//output to screen the values that remain
				if(A[l][m]>0)
				{
					count++;
					printf("%d\n",m);
				}
			}
			if (count==0)
			{
				printf("\n");
			}
		}
	
	//free S
	for (i = 0; i < N; i++)
	{
    free(S[i]);
	}
	free(S);

}

int** matrixMultiply(int **Apower,int **A, int N)
{
	int i=0;
	int j=0;
	int k=0;
	int sum =0;

	for ( i = 0 ; i <N ; i++ )
    {
      for ( j = 0 ; j < N ; j++ )
      {
        for ( k = 0 ; k < N ; k++ )
        {
          sum = sum + Apower[i][k]*A[k][j];
        }
 
        temparr[i][j] = sum;
        sum = 0;
      }
    }

	for ( i = 0 ; i <N ; i++ )
    {
      for ( j = 0 ; j < N ; j++ )
      {
		  Apower[i][j]=temparr[i][j];
	  }
	}
	return Apower;
}

void freeMemory(int N)
{
	int i=0;
	for (i = 0; i < N; i++)
	{
    free(A[i]);
	free(Apower[i]);
	free(temparr[i]);
	}

free(A);
free(Apower);
free(temparr);
}
