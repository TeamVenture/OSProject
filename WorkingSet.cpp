#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
using namespace std;
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
	int workingSetCallCount[DIFFERENT_PAGES];
	virtual ~WorkingSet(){};
	void printPageCallArray(){
			int i, max = 0, nextMax, topTenCount=0, tenpercent = DIFFERENT_PAGES /10;

			for(i = 0; i< DIFFERENT_PAGES; i++){
				if(max < workingSetCallCount[i]) {
					nextMax = max;
					max = workingSetCallCount[i];
				}
			}
			while(max >= 0){

				for( i = 0; i< DIFFERENT_PAGES; i++){
					if(workingSetCallCount[i]== max){

						if(tenpercent >0){
							printf("[%d] called: %d\n", i, workingSetCallCount[i]);
							topTenCount += workingSetCallCount[i];
							--tenpercent;
						}
					}else{
						if(workingSetCallCount[i]>nextMax && workingSetCallCount[i]<max){
							nextMax = workingSetCallCount[i];
						}
					}

				}
				max = nextMax;
				nextMax = -1;
			}
			printf("Percent of calls to top 10%% %2.2f", (double)topTenCount/(NUMBER_OF_PAGES/100.0));
			cout << endl;
		}
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
			double scatterer = rand() % 100;
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
			workingSet[i] = (rand() % 100);
			
			}
		return workingSet;
		}
	~BadProgram(){};

};

class WellBehavedModulesProgram: public WorkingSet{
public:
	int* buildSet(){
		int i, module = 0, temp;

		int switchChance[] = {50,70, 95,97};
		for(i = 0; i<DIFFERENT_PAGES;i++){ workingSetCallCount[i] = 0;}


		double r, modUpperEndSize= 9.0;
//		struct drand48_data localBuffer;
//		srand48_r(time(NULL) +  (5002) + 1, &localBuffer);

		srand(time(0));
		workingSet[0]=0;
		workingSetCallCount[0]=1;


		//Module 1 pages 0- 9
		//Module 2 pages 10 - 24
		//Module 3 pages 25 - 49
		//Module 4 pages 50 - 99
		int modStart= 0, modSize =10;

		for(i  = 1; i< NUMBER_OF_PAGES; i++) {
			r  = rand() % 100;//drand48_r(&localBuffer, &r);
			if(r > switchChance[module]){
				//printf("**SWITCH: %1.2f > %f from module %d\n", r, switchChance[module], module);
				r  = rand() % 4;//drand48_r(&localBuffer, &r);
				module = (int)(r);//note right now equal chance can be improved..
			}
			switch (module){
				case 0 :
					modStart = 0;
					modUpperEndSize = 9.0;
					modSize = 10;
					break;
				case 1:
					modStart = 10;
					modUpperEndSize = 18.0;
					modSize = 20;
					break;
				case 2:
					modStart = 30;
					modUpperEndSize = 27.0;
					modSize = 30;
					break;
				case 3:
					modStart = 50;
					modUpperEndSize = 36.0;
					modSize = 40;
					break;
			}

			r  = rand() % 10;//drand48_r(&localBuffer, &r);
			//cout<<r << endl;
			//cout << modStart <<endl;
			if(r< 9) {
				r  = rand() % (modSize/10);
				temp = ((int)((r * (10 / 9)) * ((modSize/10.0))) + modStart);
			}else{
				r  = rand() % (int)modUpperEndSize;
				temp = r + (modSize/10.0) + modStart;
			}
			if( temp != workingSet[i-1]){
				workingSet[i]=temp;
//				printf("Calling Page %d: %d time\n", temp, workingSet[temp] +1);
				int temp2 = workingSetCallCount[temp];
				temp2 = temp2 +1;
				workingSetCallCount[temp] = temp2;
			}else{
				--i;
			}
		}
		return workingSet;
	}
	~WellBehavedModulesProgram(){};
};



