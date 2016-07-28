// BreakTheString.cpp
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <algorithm>
#include <vector>

int L=0,N=0;
int *breaks;

std::map<std::pair<int,int>,int > my_map;
std::vector<int> vector_of_breaks;
int breakString(int start,int end)
{
	//find out all the breaks within [start,end)
	//std::vector<int> v(breaks,breaks+L);
	std::queue<int> B;
	std::vector<int>::iterator first_break;
	first_break=std::lower_bound (vector_of_breaks.begin(), vector_of_breaks.end(), start); //find the first break greater than start
	//if (*first_break==end)
	if (first_break==vector_of_breaks.end())
	{
		return 0;
	}
	else if (*first_break==end)
	{
		return 0;
	}
	else
	{
		for(std::vector<int>::iterator it = first_break; (it != vector_of_breaks.end() && *it<end) ; ++it)
		{
			B.push(*it);
		}
	}
	//up_break= std::lower_bound (v.begin(), v.end(), end); // find the last break less than end    
	/*for (int i = 0;i<L;++i)
	{
		if (breaks[i] >=start&&breaks[i]<end)
		{
			B.push(breaks[i]);
		}
	}*/

	//base case of recursion
	/*if (B.empty())
	{
		//no breaks
		return 0;
	}*/


	//cost for taking the breaks at this level
	int Cost = end-start+1;
	//recurse for each break and all possible options for the other breaks.
	int sum1=0,sum2=0;
	int minCost = L*N;
	while(!B.empty())
	{
		int j = B.front();
		B.pop();
		if (my_map.find(std::make_pair(start,j)) !=my_map.end())
		{
			sum1 = my_map[std::make_pair(start,j)];
		}
		else
		{
			sum1 = breakString(start,j);
			my_map[std::make_pair(start,j)] = sum1;
		}

		if (my_map.find(std::make_pair(j+1,end))!= my_map.end())
		{
			sum2 = my_map[std::make_pair(j+1,end)];
		}
		else
		{
			sum2 = breakString(j+1,end);
			my_map[std::make_pair(j+1,end)] = sum2;
		}

		if ((Cost+sum1+sum2)<minCost)
		{
			minCost = Cost+sum1+sum2;
		}
	}
	return minCost;
}


int main()
{	
	
	//memset(breaks,0,sizeof(breaks));
	int input=0,minimumTime=0;
	std::string line;

	//parse the input L and N first
	getline(std::cin,line);
	std::istringstream iss(line); 
	iss>>L;
	iss>>N;
	//breaks = new int[L]();
	 
	///get the next line which has the list of breaks
	std::string line2;
	getline(std::cin,line2);
	std::istringstream iss2(line2);

	vector_of_breaks.reserve(L);

	for (int i=0;i<L;i++)
	{ 
		iss2>>input;
		//change to 0 based indexing
		//breaks[i] = input-1;
		vector_of_breaks.push_back(input-1);
	}
	
	//std::cout<<breaks[0]<<std::endl;
	//std::cout<<breaks[1]<<std::endl;
	minimumTime = breakString(0,N-1);
	std::cout<<minimumTime<<std::endl;
	//delete [] breaks;
	return 0;
}