#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
//Base WorkingSet
/*
 * WorkingSet.cpp

 *
 *  Created on: Mar 16, 2016
 *      Author: David Weathers & Ryan McConn
 */
int const NUMBER_OF_REFERENCES = 10000;
int const NUMBER_OF_PAGES = 100;
class ReferenceSet
{

	public:
	//virtual for interface framework
	virtual int* buildSet()=0;
	int referenceString[NUMBER_OF_REFERENCES];
	int workingSetCallCount[NUMBER_OF_PAGES];
	virtual ~ReferenceSet(){};

	void printPageCallArray(){
		int i, max = 0, nextMax, topTenCount=0, tenpercent = NUMBER_OF_PAGES /10;

		for(i = 0; i< NUMBER_OF_PAGES; i++){
			if(max < workingSetCallCount[i]) {
				nextMax = max;
				max = workingSetCallCount[i];
			}
		}
		while(max >= 0){

			for( i = 0; i< NUMBER_OF_PAGES; i++){
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
		printf("Percent of calls to top 10%% %2.2f", (double)topTenCount/(SIZE_OF_REFERENCESTRING/100.0));
		cout << endl;
	}
};


// good program
class GoodProgram: public ReferenceSet
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

class BadProgram: public ReferenceSet
{
public:
	int* buildSet()
		{
		srand(time(0));
		for (int i = 0; i < NUMBER_OF_REFERENCES; i++)
			{
				referenceString[i] = (rand()% 100);
			
			}
		return referenceString;
		}
	~BadProgram(){};

};


class WellBehavedModulesProgram: public ReferenceSet{
public:
	int* buildSet(){
		int i, module = 0, temp;

		double switchChance[] = {.5,.7, .95,.97};
		for(i = 0; i<NUMBER_OF_PAGES;i++){ workingSetCallCount[i] = 0;}


		double r, modUpperEndSize= 1.0;
		struct drand48_data localBuffer;

		srand48_r(time(NULL) +  (5002) + 1, &localBuffer);
		referenceString[0]=0;
		workingSetCallCount[0]=1;


		//Module 1 pages 0- 9
		//Module 2 pages 10 - 24
		//Module 3 pages 25 - 49
		//Module 4 pages 50 - 99
		int modStart= 0, modSize =1;

		for(i  = 1; i< NUMBER_OF_REFERENCES; i++) {
			drand48_r(&localBuffer, &r);
			if(r > switchChance[module]){
				printf("**SWITCH: %1.2f > %f from module %d\n", r, switchChance[module], module);
				drand48_r(&localBuffer, &r);
				module = (int)(r * 4);//note right now equal chance can be improved..
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

			drand48_r(&localBuffer, &r);
			cout<<r << endl;
			cout << modStart <<endl;
			if(r<.9) {
				temp = ((int)((r * (1.0 /.9)) * ((modSize/10.0))) + modStart);
			}else{
				temp = (int)((r-.9) * 10.0 * modUpperEndSize) + (modSize/10.0) + modStart;
			}
			if( temp != referenceString[i-1]){
				referenceString[i]=temp;
//				printf("Calling Page %d: %d time\n", temp, workingSet[temp] +1);
				workingSetCallCount[temp] = workingSetCallCount[temp] + 1;
			}else{
				--i;
			}
		}
	}
	~WellBehavedModulesProgram(){};
};

class BadProgram2: public WorkingSet
{
public:
	int* buildSet() {
		int i, temp;

		for (i = 0; i < NUMBER_OF_PAGES; i++) { workingSetCallCount[i] = 0; }

		double x, y, r;
		struct drand48_data localBuffer;

		srand48_r(time(NULL) + (5002) + 1, &localBuffer);
		array[0] = 0;
		for (i = 1; i < size; i++) {
			drand48_r(&localBuffer, &r);
			if (r < .9) {
				temp = (int) (r * (1.0 / .9) * 10.0);
			} else {
				temp = (int) ((r - .9) * 900 + 10);
			}
			if (temp != array[i - 1]) {
				referenceString[i] = temp;
//            printf("Calling Page %d: %d time\n", temp, pageCallCount[temp] +1);
				workingSetCallCount[temp] = workingSetCallCount[temp] + 1;
			} else {
				--i;
			}
		}
	}

	~BadProgram2(){};

};


