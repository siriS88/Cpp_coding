// TheGame.cpp
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>

struct person {
  int parent;
  unsigned int score;
  unsigned int rank;
  unsigned int max_score;
  std::list<int>my_children;
};
void makeset(int N,person *people)
{
	//initiaize these peoples parent pointers to themselves, ranks to 0 and scores to 1

	for(int i=0;i<N;i++)
	{
		people[i].parent = i;
		people[i].score =1;
		people[i].rank =0;
		people[i].max_score=people[i].score;
		//std::cout<<"my parent:"<<people[i].parent<<std::endl;
		//std::cout<<"my score:"<<people[i].score<<std::endl;
		//std::cout<<"my rank:"<<people[i].rank<<std::endl;
	}
}

int find(person *people,int i)
{
	if (people[i].parent == i)
		return i;
	else
	{
	 int j = people[i].parent;
	 int y =  find(people,j);
	 people[i].parent = y;
	 return y;
	}	
}
void unionSetAndIncrementScore(person * people, int x,int y)
{
	int x_parent = find(people,x);
	int y_parent = find(people,y);

	if (x_parent == y_parent)
	{
		//Two people from same corporation. NoOp
	}
	else if (people[x_parent].rank<=people[y_parent].rank) 
	{
		//Increment the score of Winner X and all its Children by the max value of score of Loser corp of Y
		people[x_parent].score = people[x_parent].score + people[y_parent].max_score;
		people[x_parent].max_score = people[x_parent].score;
		for (std::list<int>::iterator it=people[x_parent].my_children.begin(); it != people[x_parent].my_children.end(); ++it)
		{
			//std::cout << ' ' << *it<<::std::endl;
			people[*it].score = people[*it].score + people[y_parent].max_score;
			if (people[*it].score>people[x_parent].max_score)
			{
				people[x_parent].max_score = people[*it].score;
			}
			
		}
		people[x_parent].parent = people[y_parent].parent;
		//Push x_parent and all of its children as childern of y_parent
		people[y_parent].my_children.push_back(x_parent);
		//Also update the max_score of the parent
		people[y_parent].max_score = std::max(people[y_parent].max_score,people[x_parent].max_score); 
		for (std::list<int>::iterator it=people[x_parent].my_children.begin(); it != people[x_parent].my_children.end(); ++it)
		{
			people[y_parent].my_children.push_back(*it);
		}
		if (people[x_parent].rank==people[y_parent].rank)
		{
			people[y_parent].rank = people[y_parent].rank+1;
		}
	}
	else
	{
		people[x_parent].score = people[x_parent].score + people[y_parent].max_score;
		people[x_parent].max_score = people[x_parent].score;
		//Increment the score of Winner X and all its Children by the value of score of Loser Y
		for (std::list<int>::iterator it=people[x_parent].my_children.begin(); it != people[x_parent].my_children.end(); ++it)
		{
			//std::cout << ' ' << *it<<std::endl;
			people[*it].score = people[*it].score + people[y_parent].max_score;
			if(people[*it].score>people[x_parent].max_score)
			{
				people[x_parent].max_score = people[*it].score;
			}

		}

	people[y_parent].parent = people[x_parent].parent;
	//Push y_parent and all of its children as childern of x_parent
	people[x_parent].my_children.push_back(y_parent);
	//Also update the max score of the parent
	people[x_parent].max_score = std::max(people[x_parent].max_score,people[y_parent].max_score); 
	for (std::list<int>::iterator it=people[y_parent].my_children.begin(); it != people[y_parent].my_children.end(); ++it)
		{
			people[x_parent].my_children.push_back(*it);
		}
	}

}

int main()
{
	char array[20];
	int input_array[20];
	char* token;
	int i=0,j=0,N=0,M=0,L=0,length=0;
	unsigned long long totalDonation =0;
	std::string line;
	//parse the input N M L  first
	getline(std::cin,line);
	std::istringstream iss(line); 
	iss>>N;
	iss>>M;
	iss>>L;

	//std::cout<<"N is"<<N<<std::endl;
	//std::cout<<"M is"<<M<<std::endl;
	//std::cout<<"L is"<<L<<std::endl;
	//array of structures containing each person
	person*people = new person[N];
	makeset(N,people);

	//people[0].parent = 1;
	//people[1].parent = 2;
	//people[2].parent = 3;

	//std::cout<<"find of 0 is:"<<find(people,0)<<std::endl;
	//std::cout<<"find of 1 is:"<<find(people,1)<<std::endl;
	//std::cout<<"find of 2 is:"<<find(people,2)<<std::endl;
	//std::cout<<"find of 3 is:"<<find(people,3)<<std::endl;


	//get the next M+L lines
	for (i=0;i<(M+L);i++)
	{
		memset(array,0,sizeof(array));
		memset(input_array,0,sizeof(array));
		gets(array);
		token = strtok(array," ");
		int length =0;
		while (token!=NULL)
		{
			if(strcmp(token,"\n") == 0)
				break;
			input_array[length] = atoi(token);
			token = strtok(NULL," ");
			length++;
		}
		if (length ==2)
			{
			//This is a round input
				//std::cout<<"first input of round:"<<input_array[0]<<std::endl;
				//std::cout<<"second input of round:"<<input_array[1]<<std::endl;
				//std::cout<<"find of x:"<<find(people,input_array[0])<<std::endl;
				//std::cout<<"find of x:"<<find(people,input_array[2])<<std::endl;
				unionSetAndIncrementScore(people, input_array[0],input_array[1]);
			}
			else if (length==1)
			{
			//This is a donation input
				//std::cout<<"donation input:"<<input_array[0]<<std::endl;
				//std::cout<<"score:"<<people[input_array[0]].score<<std::endl;
				totalDonation = totalDonation + people[input_array[0]].score;
			}
	}
	std::cout<<totalDonation<<std::endl;
	delete[] people;
	return 0;
}