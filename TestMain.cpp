/*
 * TestMain.cpp

 *
 *  Created on: Mar 16, 2016
 *      Author: David Weathers
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "ReplacementStrategies.cpp"
#include "ReferenceSet.cpp"

using namespace std;
int RESIDENT_SET_SIZE;
//int NUMBER_OF_REFERENCES;
int const BREAK_POINT = 40;

int LRU(int arr[]){
	list<int> residentSet;
	int pageFault = 0;
	for(int i = 0; i < NUMBER_OF_REFERENCES; i ++){
		if(residentSet.size() < RESIDENT_SET_SIZE && !(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
			pageFault++;
			residentSet.push_back(arr[i]);
		}
		else if(!(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
			pageFault++;
			residentSet.pop_front();
			residentSet.push_back(arr[i]);
		}
		else {
			residentSet.remove(arr[i]);
			residentSet.push_back(arr[i]);
		}
	}
	return pageFault;
}

int FutureGazing(int i, list<int> set, int* arr){
	for (int j = i; j < NUMBER_OF_REFERENCES; j++){
		if(set.size() == 1){
			return set.front();
		}
		else if ((find(set.begin(), set.end(), arr[j]) != set.end())){
			set.remove(arr[j]);
		}
	}
	return set.front();
}

int Optimal(int arr[]){
	list<int> residentSet;
	int pageFault = 0;
	list<int> oracleSet;
	for(int i = 0; i < NUMBER_OF_REFERENCES; i ++){
		if(residentSet.size() < RESIDENT_SET_SIZE && !(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
			pageFault++;
			residentSet.push_back(arr[i]);
		}
		else if(!(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
			pageFault++;
			oracleSet = residentSet;
			residentSet.remove(FutureGazing(i,oracleSet, arr));
			residentSet.push_back(arr[i]);
		}

	}
	return pageFault;
}

int leastOU(int count[], list<int> currentSet){
	int replace = 10000000;
	int tempCount = 10000000;
	while(!currentSet.empty()){
		int temp = currentSet.front();
		currentSet.pop_front();
		if(count[temp] < tempCount){
			replace = temp;
			tempCount = count[temp];
		}
	}
	return replace;

}

void resetMax(int count[]){
	for (int i = 0; i < NUMBER_OF_PAGES; i++){
		count[i] = count[i]/2;
	}
}

int lou(int arr[] ){
	int count[NUMBER_OF_PAGES];
	int pageFault = 0;
	list<int> residentSet;

	for (int i = 0; i < NUMBER_OF_REFERENCES; i++){
		if(residentSet.size()< RESIDENT_SET_SIZE) {
			if  (!(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
				pageFault++;
				residentSet.push_back(arr[i]);
				count[i] = 1;
			}
			else {
				count[arr[i]] = count[arr[i]] + 1;
				if(count[arr[i]]>= BREAK_POINT){
					resetMax(count);
				}
			}
		}else {
			if(!(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
				int temp = leastOU(count, residentSet);
				residentSet.remove(temp);
				residentSet.push_back(arr[i]);
				count[arr[i]] = count[arr[i]] + 1;if(count[arr[i]]>= BREAK_POINT){
					resetMax(count);
				}
				pageFault++;




			}else{
				count[arr[i]] = count[arr[i]] + 1;
				if(count[arr[i]]>= BREAK_POINT){
					resetMax(count);
				}
			}


		}
	}
	return pageFault;
}





int main()
{
	GoodProgram a;
	BadProgram b;
	WellBehavedModulesProgram c;
	int* good = a.buildSet();
	int* bad = b.buildSet();
	int* realistic = c.buildSet();
	printf("LRU-Good, LRU-Bad, LRU-Well Behaved, OPTIMAL-Good, OPTIMAL-Bad, OPTIMAL-Well Behaved, LOU-Good, LOU-Bad, LOU-Well Behaved\n");
	for(int i = 1; i <= 50; i++){
		RESIDENT_SET_SIZE = i;


		printf("%d",i);
		printf("%d,", LRU(good));
		printf("%d,", LRU(bad));
		printf("%d,", LRU(realistic));
		printf("%d,", Optimal(good));
		printf("%d,", Optimal(bad));
		printf("%d,", Optimal(realistic));
		printf("%d,", lou(good));
		printf("%d", lou(bad));
		printf("%d\n", lou(realistic));

	}
	return 0;
	}


