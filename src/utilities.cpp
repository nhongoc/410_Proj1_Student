/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************
vector<process_stats> stats;

bool compareProcessNumber(const process_stats &p1, const process_stats &p2) {
	return p1.process_number < p2.process_number;
}

bool compareStartTime(const process_stats &p1, const process_stats &p2) {
	return p1.start_time < p2.start_time;
}

bool compareCPUTime(const process_stats &p1, const process_stats &p2) {
	return p1.cpu_time < p2.cpu_time;
}

bool compareIOTime(const process_stats &p1, const process_stats &p2) {
	return p1.io_time < p2.io_time;
}
//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();
	fstream mystream;
	mystream.open(filename, ios::in);
	if(!mystream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder) {
	case PROCESS_NUMBER:
		sort(stats.begin(), stats.end(), compareProcessNumber);
		break;
	case CPU_TIME:
		sort(stats.begin(), stats.end(), compareCPUTime);
		break;
	case START_TIME:
		sort(stats.begin(), stats.end(), compareStartTime);
		break;
	case IO_TIME:
		sort(stats.begin(), stats.end(), compareIOTime);
		break;
	default:
		break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	myFirst = stats.front();
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


