// SubstringOccurrences.cpp
// using hashing by division 
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <math.h>
#define d 256 
int isPrime(int n) // assuming n > 1
{
    int i,root;

    if (n%2 == 0 || n%3 == 0)
        return 0;

    root = (int)sqrt(n);

    for (i=5; i<=root; i+=6)
    {
        if (n%i == 0)
           return 0;
    }

    for (i=7; i<=root; i+=6)
    {
        if (n%i == 0)
           return 0;
    }

    return 1;
}
int findPrimeNumber(int m)
{
	int q=m+1;
    while(1)
    {
        if(isPrime(q))
            break;
        q++;
    }
    return q;
}
int findSubstrings(std::string S,std::string T,int q,int n,int m)
{
 int h = 1;
 
 int p=0,t=0,count=0;

 // Compute the value of d^(m-1) --> Pre-processing in linear time
for(int i=0;i<m-1;i++)
{
	h=(d*h)%q;
}

 for(int i=0;i<m;++i)
 {
	 p = (d*p+T[i])%q; //modulo value of the pattern
	 t = (d*t+S[i])%q; //modulo value of the string
 }
 for (int j = 0;j<=n-m;++j)
 {
	 if (p==t) //hash values match
	 {
		 //compare the actual string to see if the match is spurious
		 if (n > 500000)
		 {
			if (T[0] == S[j]&&T[1] == S[j+1]&&T[m-2]==S[j+m-2]&&T[m-1]==S[j+m-1])
			{
			 count++;
			}
		 }
		 else
		 {
			if (T[0] == S[j]&&T[m/4]==S[j+m/4]&&T[m/2] == S[j+m/2]&&T[m-1]==S[j+m-1])
			{
			 count++;
			}
		 }
		 /*for (int k=0;k<m;++k)
		 {
			 if(T[k]!=S[j+k])
			 {
				break;
			 }
			 
			 if(k==m-1)
				{
				//std::cout<<"Match at index:"<<j<<std::endl;
				count++;
				}  
		 }*/
	 }
	 if(j<(n-m)) //move to the next slide
	 {
		 //get the next string of length m 
		 t= (d*(t-S[j]*h) + S[j+m])%q;
		 //handle the case when t becomes negative
		 if(t < 0)
		 {
			t = (t + q);
		 }

	 }

 }
 return count;
}
int main()
{	
	int q=0,numOccurrences=0;
	//parse the pattern T
	std::string T;
	getline(std::cin,T);

	//parse the actual string S
	std::string S;
	getline(std::cin,S);

	int m = strlen(T.c_str());
	int n = strlen(S.c_str());

	//q = findPrimeNumber(2*m);
	//std::cout<<"pattern is:"<<T<<std::endl;
	//std::cout<<"actual string is:"<<S<<std::endl;
	numOccurrences = findSubstrings(S,T,1001,n,m);
	std::cout<<numOccurrences<<std::endl;

	return 0;
}