/*
 * TestMain.cpp

 *
 *  Created on: Mar 16, 2016
 *      Author: David Weathers
 */

#include <iostream>
#include <stdlib.h>
#include "WorkingSet.cpp"
#include "ReplacementStrategies.cpp"

int const RESIDENT_SET_SIZE = +10;
//int const NUMBER_OF_PAGES = +100000;

int LRU(int arr[]){
		list<int> residentSet;
		int pageFault = 0;
		for(int i = 0; i < NUMBER_OF_PAGES; i ++){
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
	for (int j = i; j < NUMBER_OF_PAGES; j++){
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
	for(int i = 0; i < NUMBER_OF_PAGES; i ++){
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



int main()
	{
		GoodProgram a;
		BadProgram b;
		int* good = a.buildSet();
		int* bad = b.buildSet();

		std::cout << LRU(good) << endl;
		std::cout << LRU(bad) << endl;

		std::cout << Optimal(good) << endl;
		std::cout << Optimal(bad) << endl;

	return 0;
	}


