#include <iostream>
#include <stdlib.h>
#include <ctime>
//Base WorkingSet
/*
 * WorkingSet.cpp

 *
 *  Created on: Mar 16, 2016
 *      Author: David Weathers
 */
int const NUMBER_OF_PAGES = 10000;
int const DIFFERENT_PAGES = 100;
class WorkingSet
{

	public:
	//virtual for interface framework
	virtual int* buildSet()=0;
	int workingSet[NUMBER_OF_PAGES];
	virtual ~WorkingSet(){};
};


// good program
class GoodProgram: public WorkingSet
{

public:
	int* buildSet()
		{
		srand(time(0));
		for (int i = 0; i < NUMBER_OF_PAGES; i++)
			{
			double scatterer = rand()%100;
			if(scatterer > 89)
				{
				workingSet[i] = (rand() % 90 + 10);
				}
			else
				{
				workingSet[i] = (rand() % 10);
				}
			
			}
		return workingSet;
		}
	~GoodProgram(){};

};

class BadProgram: public WorkingSet
{
public:
	int* buildSet()
		{
		srand(time(0));
		for (int i = 0; i < NUMBER_OF_PAGES; i++)
			{
			workingSet[i] = (rand()% 100);
			
			}
		return workingSet;
		}
	~BadProgram(){};

};


