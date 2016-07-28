// Zoo.cpp
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <map>
#include <deque>
std::map<unsigned int,unsigned int> forward_occurences;
std::map<unsigned int,unsigned int> reverse_occurences;
std::deque<unsigned int> exhibits;
std::map<unsigned int,unsigned int> my_freq_map;
std::map<unsigned int,unsigned int> my_freq_map_local;
unsigned int num_pairs =0;

int find_num_pairs()
{
	unsigned int highest_Local_Key=0;
	unsigned int sum1=0;
	unsigned int sum2=0;
	if (exhibits.size()<=1)
	{
		return num_pairs;
	}
	    unsigned int val_END = exhibits.back();
		exhibits.pop_back();
		unsigned int val_BEFORE_END = exhibits.back();
		exhibits.pop_back();
		
		reverse_occurences[val_END]++;
		//find number of keys in my_freq_map that are lesser than forward occurence of this value
		//iterate through them and find the number of pairs
		if ((forward_occurences[val_BEFORE_END] - reverse_occurences[val_BEFORE_END])>reverse_occurences[val_END])
		{
			num_pairs = num_pairs + 1;
		}

		typedef std::map<unsigned int,unsigned int>::iterator it_type;
			for(it_type iterator = my_freq_map.begin(); iterator != my_freq_map.end(); iterator++)
			{
				if ((forward_occurences[val_END]-reverse_occurences[val_END]+1)>iterator->first)
				{
					sum1 = sum1+iterator->second;
				}
				if ((forward_occurences[val_BEFORE_END]-reverse_occurences[val_BEFORE_END])>iterator->first)
				{
					sum2 = sum2+iterator->second;
				}
			}
			num_pairs = num_pairs+sum1+sum2;

			
			reverse_occurences[val_BEFORE_END]++;
			my_freq_map[reverse_occurences[val_END]]++;
			my_freq_map[reverse_occurences[val_BEFORE_END]]++;
			find_num_pairs();
			return num_pairs;
}

int main()
{	
	int i=0,N=0;
	unsigned int value_End=0,value_BeforeEnd=0,input=0;
	std::string line;

	//parse the input N first
	getline(std::cin,line);
	std::istringstream iss(line); 
	iss>>N;

	///get the next line
	std::string line2;
	getline(std::cin,line2);
	std::istringstream iss2(line2);
	for (int i=0;i<N;i++)
	{ 
		iss2>>input;
		exhibits.push_back(input);
		//arrange these in a map to get the occurence of these exhibits when going from east to west.
		forward_occurences[input]++;
	}
		
		//pop two values out and perform the last pair before starting divide and conquer recursion
	    value_End = exhibits.back();
		exhibits.pop_back();
		value_BeforeEnd = exhibits.back();
		exhibits.pop_back();
		reverse_occurences[value_End]++;
		my_freq_map[reverse_occurences[value_End]]++;
		reverse_occurences[value_BeforeEnd]++;
		my_freq_map[reverse_occurences[value_BeforeEnd]]++;
		
		//std::cout<<reverse_occurences[value]<<std::endl;
		if (forward_occurences[value_BeforeEnd]>reverse_occurences[value_End])
		{
			num_pairs = num_pairs + 1;
		}
		num_pairs = find_num_pairs();

	std::cout<<num_pairs<<std::endl;
	return 0;
}