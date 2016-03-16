/*
 * ReplacementStrategies.cpp

 *
 *  Created on: Mar 16, 2016
 *      Author: David Weathers
 */
#include <stdlib.h>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
class ReplacementStrategies{
public:
	int LRU(int arr[]){
		list<int> residentSet;
		int pageFault = 0;
		for(int i = 0; i < 10000; i ++){
			if(residentSet.size() < 8 && !(find(residentSet.begin(), residentSet.end(), arr[i]) != residentSet.end())){
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



};
