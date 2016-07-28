#include <iostream>
#include <limits.h>
#include <string>
#include <queue>
#include <math.h>
#include <sstream>
#include <vector>
#include <set>

using namespace std;
struct output1 {
	int flag;
	int value;
	};
/*
void printAMatrix(vector <vector <int> > & A)
{
	int i=0,j=0;
	for (i=0;i<A.size();i++)
	{
		cout<<i<<" ";
		for(j=0;j<A[i].size();j++)
		{
			printf("%d",A[i][j]);
		}
		printf("\n");
	}
}
 */

bool bfs(vector < vector <int> >& rGraph, int s, int t, vector <int> & parent)
{
	int V = rGraph.size();
    vector <bool> visited(V, false);
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    return (visited[t] == true);
}
 
int fordFulkerson(vector < vector <int> > & graph, int s, int t)
{
	
    int u, v;
	int V = graph.size();

    vector <vector <int> > rGraph(graph); 
 
 
    vector <int> parent(V,-1);  
 
    int max_flow = 0;  
 
   
    while (bfs(rGraph, s, t, parent))
    {
       
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
      
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        max_flow += path_flow;
    }
 
    return max_flow;
}

int main()
{
	
	vector<output1> my_output_vector;
	int n=0,m=0,T=0,maxFlow=0;
	std::string numTestCases;
	//parse the input n m  first
	getline(std::cin,numTestCases);
	std::istringstream iss(numTestCases); 
	iss>>T;
	for(int t=0;t<T;++t)
	{
	std::string line;
	//parse the input n m  first
	getline(std::cin,line);
	std::istringstream iss(line); 
	iss>>n;
	iss>>m;

	vector<vector<int> > graph(n*n + 2, vector <int>(n*n+2, 0));
 
	//create the adjacency matrix for the grid. Source is the n^2 th column and sink is the n^2+1 th column
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		{
			int Lidx = i*n+j;
			if (i-1>=0)
			{
			int L1 =  (i-1)*n +j;
			graph[Lidx][L1] =1;
			graph[L1][Lidx] =1;
			}
			if (j-1>=0)
			{
				int L2 = i*n+j-1;
				graph[Lidx][L2] =1;
				graph[L2][Lidx] =1;
			}
			if(i+1<n)
			{
				int L3 = (i+1)*n+j;
				graph[Lidx][L3] =1;
				graph[L3][Lidx] =1;
			}
			if(j+1<n)
			{
				int L4 = i*n+j+1;
				graph[Lidx][L4]=1;
				graph[L4][Lidx]=1;
			}
		}
	}
	//add in the edges from border nodes to the sink
	for (int j=0;j<n;++j)
	{
		//graph[n*n+1][0*n+j] =1;
		graph[0*n+j][n*n+1] =1;
	}
	for (int j=0;j<n;++j)
	{
		//graph[n*n+1][j*n+0] =1;
		graph[j*n+0][n*n+1] =1;
	}
	for (int j=0;j<n;++j)
	{
		//graph[n*n+1][j*n+(n-1)] =1;
		graph[j*n+(n-1)][n*n+1] =1;
	}

	for (int j=0;j<n;++j)
	{
		//graph[n*n+1][n*(n-1)+j] =1;
		graph[n*(n-1)+j][n*n+1] =1;
	}

		//parse the coordinates of the caterpillars and add in the edges from source to these
		int rowIn, colIn;
		set<int> visitedLinIdx;
		for (int c=0;c<m;++c)
		{
			std::string line2;
			getline(std::cin,line2);
			std::istringstream iss2(line2); 
			iss2>>colIn;
			iss2>>rowIn;
			--rowIn; --colIn;
			int linIdx = (rowIn)*n+(colIn);
			graph[n*n][linIdx] =1;
			//graph[linIdx][n*n] =1;
			visitedLinIdx.insert(linIdx);
		}

		set<int>::iterator it;
		for (it = visitedLinIdx.begin(); it!= visitedLinIdx.end(); ++it){
			if (*it - 1 >=0 && visitedLinIdx.find(*it-1)!=visitedLinIdx.end()) {
				graph[*it][*it-1] = 0;
				graph[*it-1][*it] = 0;
			}
			if (*it + 1 <n*n && visitedLinIdx.find(*it+1)!=visitedLinIdx.end()) {
				graph[*it][*it+1] = 0;
				graph[*it+1][*it] = 0;
			}
			if (*it - n >=0 && visitedLinIdx.find(*it-n)!=visitedLinIdx.end()) {
				graph[*it][*it-n] = 0;
				graph[*it-n][*it] = 0;
			}
			if (*it +n < n*n && visitedLinIdx.find(*it+n)!=visitedLinIdx.end()) {
				graph[*it][*it+n] = 0;
				graph[*it+n][*it] = 0;
			}
		}
		
	//printAMatrix(graph);
	maxFlow = fordFulkerson(graph, n*n, n*n+1);
	output1 my_result;
	if (maxFlow < m)
	{
		my_result.flag =0;
		my_result.value = maxFlow;
		my_output_vector.push_back(my_result);
	}
	else
	{
		my_result.flag = 1;
		my_result.value = maxFlow;
		my_output_vector.push_back(my_result);
	}
 }
 //print output
	vector<output1>::iterator iter;
	for (iter = my_output_vector.begin(); iter!= my_output_vector.end(); ++iter)
	{
		if ((*iter).flag)
		{
			cout<<"possible"<<std::endl;
		}
		else
		{
			cout<<"not possible"<<std::endl;
			cout<<(*iter).value<<std::endl;
		}
	}
    return 0;
}