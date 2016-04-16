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
int const WORK_NUMBER_OF_REFERENCES = 10000;
class WorkingSet
{

	public:
	//virtual for interface framework
	virtual int* buildSet()=0;
	int workingSet[WORK_NUMBER_OF_REFERENCES];
	virtual ~WorkingSet(){};
};


// good program
class GoodProgram: public WorkingSet
{

public:
	int* buildSet()
		{
		srand(time(0));
		for (int i = 0; i < WORK_NUMBER_OF_REFERENCES; i++)
			{
			if(i%10 == 0)
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
		for (int i = 0; i < WORK_NUMBER_OF_REFERENCES; i++)
			{
			workingSet[i] = (rand()% 100);
			
			}
		return workingSet;
		}
	~BadProgram(){};

};


