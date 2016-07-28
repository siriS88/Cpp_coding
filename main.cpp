#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <queue>
struct coordinates {
  coordinates()
  {
	  x=0;y=0;
  for (int i=0;i<9;i++)
  {
   Sbody_X[i]=0;
   Sbody_Y[i]=0;
  }
  }

  int x;
  int y;
  int Sbody_X[9];
  int Sbody_Y[9];
};
void printAMatrix(int** A,int m,int n)
{
	int i=0,j=0;
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d  ",A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
coordinates findHead(int **A,int m,int n)
{
	int i =0,j=0;
	coordinates Head;
	Head.x =0;
	Head.y =0;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
        if (A[i][j] == 1)
			{
            Head.x=i;
            Head.y=j;
			}
		}
	}
	return Head;
}
coordinates findBodyParts(int **A,int m,int n,int num)
{
	int i=0,j=0;
	coordinates bodyPart;
	bodyPart.x=0;
	bodyPart.y=0;
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if (A[i][j] == num)
			{
            bodyPart.x=i;
            bodyPart.y=j;
            
			}
		}
	}
	return bodyPart;
}

int isTargetPresent(int **A,int m, int n)
{
	int flag=0;
	for (int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if (A[i][j] == 100)
			{
            flag=1;
			break;
            
			}
		}
		if(flag)
			break;
	}
	if(!flag)
		return -1;
	else
	  return 0;
	
}


int BFS(int m,int n,int k,int** A, coordinates InitialHeadLocation)
{
	std::queue<coordinates> my_queue;
	std::queue<coordinates> inner_queue;
	coordinates u;	
	coordinates w;

	int** dist = new int*[m];
	
	for (int i = 0; i < m; ++i)
	{
 	dist[i] = new int[n]();
	}
	

	int minsteps =-1;
	dist[InitialHeadLocation.x][InitialHeadLocation.y] =0;
	
	InitialHeadLocation.Sbody_X[0] = InitialHeadLocation.x;
	InitialHeadLocation.Sbody_Y[0] = InitialHeadLocation.y;
	coordinates B;
	B.x = InitialHeadLocation.x;
	B.y = InitialHeadLocation.y;
	//populate initial snake locations
		if(k>1)
		{
			for(int i =1;i<k;i++)
			{
				//B = findBodyParts(A,m,n,i+1);

				if ((B.x!=m-1)&&(((B.x)+1)<=m-1)&&(A[(B.x)+1][B.y]!=99))
				{
					if (A[(B.x)+1][B.y]==i+1)
					{
						InitialHeadLocation.Sbody_X[i] = (B.x)+1;
						InitialHeadLocation.Sbody_Y[i] = B.y;
						B.x = B.x+1;
						continue;
					}
				}
				if ((B.x!=0)&&(((B.x)-1)>=0)&&(A[(B.x)-1][B.y]!=99))
				{
					if (A[(B.x)-1][B.y]==i+1)
					{
						InitialHeadLocation.Sbody_X[i] = (B.x)-1;
						InitialHeadLocation.Sbody_Y[i] = B.y;
						B.x = (B.x)-1;
						continue;

					}
				}
				if ((B.y!=n-1)&&(((B.y)+1)<=n-1)&&(A[B.x][(B.y)+1]!=99))
				{
					if (A[B.x][(B.y)+1]==i+1)
					{
						InitialHeadLocation.Sbody_X[i] = B.x;
						InitialHeadLocation.Sbody_Y[i] = (B.y)+1;
						B.y = (B.y)+1;
						continue;

					}
				}
				if ((B.y!=0)&&((B.y)-1>=0)&&(A[B.x][(B.y)-1]!=99) )
				{
					if (A[B.x][(B.y)-1]==i+1)
					{
						InitialHeadLocation.Sbody_X[i] = B.x;
						InitialHeadLocation.Sbody_Y[i] = (B.y)-1;
						B.y = (B.y)-1;
						continue;

					}
				}
			}
		}


	my_queue.push(InitialHeadLocation);

	while (my_queue.size()>0)
	{
		u = my_queue.front();
		my_queue.pop();
		//look at the four neighbours of the current location and decide which ones to put in inner queue
		if ((u.x!=m-1)&&(((u.x)+1)<=m-1)&&(A[(u.x)+1][u.y]!=99))
		{
			w.x = (u.x)+1;
			w.y = u.y;

			int validNeighbor = 1;
			if(k>1)
			{
				for (int i = 0;i<k;i++)
				{
				if ((w.x == u.Sbody_X[i]) &&(w.y==u.Sbody_Y[i]) && (i!=k-1))
					{
						validNeighbor =0;
						break;
					}
				}
			}
			if (validNeighbor)
			{
			inner_queue.push(w);
			}
		}
		if ((u.x!=0)&&(((u.x)-1)>=0)&&(A[(u.x)-1][u.y]!=99))
		{
			w.x = (u.x)-1;
			w.y = u.y;
			int validNeighbor = 1;
			if(k>1)
			{
				for (int i = 0;i<k;i++)
				{
				if ((w.x == u.Sbody_X[i]) &&(w.y==u.Sbody_Y[i]) && (i!=k-1))
					{
						validNeighbor =0;
						break;
					}
				}
			}
			if (validNeighbor)
			{
			inner_queue.push(w);
			}
		}
		if ((u.y!=n-1)&&(((u.y)+1)<=n-1)&&(A[u.x][(u.y)+1]!=99))
		{
			w.x = u.x;
			w.y = (u.y)+1;

			int validNeighbor = 1;
			if(k>1)
			{
				for (int i = 0;i<k;i++)
				{
				if ((w.x == u.Sbody_X[i]) &&(w.y==u.Sbody_Y[i]) && (i!=k-1))
					{
						validNeighbor =0;
						break;
					}
				}
			}
			if (validNeighbor)
			{
			inner_queue.push(w);
			}
		}
		if ((u.y!=0)&&((u.y)-1>=0)&&(A[u.x][(u.y)-1]!=99) )
		{
			w.x = u.x;
			w.y = (u.y)-1;

			int validNeighbor = 1;
			if(k>1)
			{
				for (int i = 0;i<k;i++)
				{
				if ((w.x == u.Sbody_X[i]) &&(w.y==u.Sbody_Y[i]) && (i!=k-1))
					{
						validNeighbor =0;
						break;
					}
				}
			}
			if (validNeighbor)
			{
			inner_queue.push(w);
			}
		}
	
		while(inner_queue.size()>0)
		{
			w=inner_queue.front();
			inner_queue.pop();

            dist[w.x][w.y] = dist[u.x][u.y]+1;
				
            
            //update S location
				if (A[w.x][w.y]==100)
				{
                minsteps =dist[w.x][w.y];
                return minsteps;
				}
				else
				{
				//set new head
                //A[w.x][w.y] = 1;
				//set old tail location to 0
                A[u.Sbody_X[k-1]][u.Sbody_Y[k-1]] =0;
				//set the positions of S body for w
				w.Sbody_X[0] = w.x;
				w.Sbody_Y[0] = w.y;
                if (k>1)
				{
                for (int p = 0;p<k-1;p++)
					{
						w.Sbody_X[p+1] = u.Sbody_X[p];
						w.Sbody_Y[p+1] = u.Sbody_Y[p];
						
					}
				

				/*for (int p=0;p<k;++p)
					{
				      //redraw the snake
					  A[w.Sbody_X[p]][w.Sbody_Y[p]] = p+1;
					}*/
				}
				my_queue.push(w);
				}
		}
	}
return minsteps;
}

int BFS2(int m,int n,int k,int** A, coordinates InitialHeadLocation)
{
	std::queue<coordinates> my_queue;
	std::queue<coordinates> inner_queue;
	coordinates u;	
	coordinates w;
	int** prev_x = new int*[m];
	int** prev_y = new int*[m];
	int** dist = new int*[m];
	int** visited = new int*[m];
	for (int i = 0; i < m; ++i)
	{
    prev_x[i] = new int[n]();
	prev_y[i] = new int[n]();
	dist[i] = new int[n]();
	visited[i] = new int[n]();
	}
	

	//initialise dist array to something big
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			dist[i][j]=100;
		}
	}

	int minsteps =-1;
	dist[InitialHeadLocation.x][InitialHeadLocation.y] =0;
	visited[InitialHeadLocation.x][InitialHeadLocation.y] =1;

	coordinates* SbodyParts = new coordinates[k];
	SbodyParts[0].x = InitialHeadLocation.x;
	SbodyParts[0].y = InitialHeadLocation.y;
	coordinates B;
	//set up the initial prev values
	for (int t = 0;t<k-1;t++)
	{
	prev_x[SbodyParts[t].x][SbodyParts[t].y] = SbodyParts[t+1].x;
	prev_y[SbodyParts[t].x][SbodyParts[t].y] = SbodyParts[t+1].y;
	}

	my_queue.push(InitialHeadLocation);

	while (my_queue.size()>0)
	{
		u = my_queue.front();
		my_queue.pop();
		//look at the four neighbours of the current location and decide which ones to put in inner queue
		if ((u.x!=m-1)&&(((u.x)+1)<=m-1)&&((A[(u.x)+1][u.y]==0)||(A[(u.x)+1][u.y]==100)||((k!=2)&&(A[(u.x)+1][u.y]==k))))
		{
			w.x = (u.x)+1;
			w.y = u.y;
			inner_queue.push(w);
		}
		if ((u.x!=0)&&(((u.x)-1)>=0)&&((A[(u.x)-1][u.y]==0)||(A[(u.x)-1][u.y]==100)||((k!=2)&&(A[(u.x)-1][u.y]==k))))
		{
			w.x = (u.x)-1;
			w.y = u.y;
			inner_queue.push(w);
		}
		if ((u.y!=n-1)&&(((u.y)+1)<=n-1)&&((A[u.x][(u.y)+1]==0)||(A[u.x][(u.y)+1]==100)||((k!=2)&&(A[u.x][(u.y)+1]==k))))
		{
			w.x = u.x;
			w.y = (u.y)+1;
			inner_queue.push(w);
		}
		if ((u.y!=0)&&((u.y)-1>=0)&&((A[u.x][(u.y)-1]==0)||(A[u.x][(u.y)-1]==100)||((k!=2)&&(A[u.x][(u.y)-1]==k))))
		{
			w.x = u.x;
			w.y = (u.y)-1;
			inner_queue.push(w);
		}
	
		while(inner_queue.size()>0)
		{
			w=inner_queue.front();
			inner_queue.pop();
			if (!visited[w.x][w.y])
			{
            visited[w.x][w.y] =1;
            dist[w.x][w.y] = dist[u.x][u.y]+1;
			my_queue.push(w);	
            prev_x[w.x][w.y] = u.x;
			prev_y[w.x][w.y] = u.y;
            
            //update S location
				if (A[w.x][w.y]==100)
				{
                minsteps =dist[w.x][w.y];
                return minsteps;
				}
				else
				{
                A[w.x][w.y] = 1;
                int index_1 = prev_x[w.x][w.y];
                int index_2 = prev_y[w.x][w.y];
                //set current tail to 0
                A[index_1][index_2] = 0;
				
				}
				}
		}
	}
return minsteps;
}

int main()
{
	//parse the input and put it in A
	std::string line;
	char array[11];
	char token[2];
	int minSteps =-1;
	
	int i=0,j=0,m=0,n=0,k=0;
	getline(std::cin,line);
	std::istringstream iss(line); 
	iss>>m;
	iss>>n;
	iss>>k;

	//allocate mem for the grid
	int** A = new int*[m];
	for (int i = 0; i < m; ++i)
	{
    A[i] = new int[n]();
	}

	//parse the grid input
	for (i=0;i<m;i++)
	{
		memset(array,0,sizeof(array));
		gets(array);
		j=0;
		while(array[j]!=NULL)
		{
			switch (array[j])
			{
			case 'X':
			A[i][j] =99;
			break;
			case '.':
				A[i][j] =0;
				break;
			case 'A':
				A[i][j] = 100;
				break;
			default:
				token[0]=array[j]; 
				token[1] = NULL;
				A[i][j] = atoi(token);
			}
			j++;
		}
	}

	if( isTargetPresent(A,m,n)!=-1)
	{
	coordinates InitialHeadLocation = findHead(A,m,n);
		if (k==1)
		{
			minSteps = BFS2(m,n,k,A,InitialHeadLocation);
		}
		else
		{
			minSteps = BFS(m,n,k,A,InitialHeadLocation);
		}
	}
	else
	{
		minSteps=-1;
		
	}
	std::cout<<minSteps<<std::endl;
return 0;
}
