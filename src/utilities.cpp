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
	string line;
	mystream.open(filename, ios::in);
	if (!mystream.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (ignoreFirstRow) {
		getline(mystream, line);
	}
	while(!mystream.eof()) {
		getline(mystream, line);
		stringstream ss(line);
		process_stats stat;
		string process_num;
		string start_time;
		string cpu_time;
		string io_time;
		getline(ss, process_num, ',');
		getline(ss, start_time, ',');
		getline(ss, cpu_time, ',');
		getline(ss, io_time, ',');
		if (process_num.length() < 1 || start_time.length() < 1 || cpu_time.length() < 1 || io_time.length() < 1) {
			continue;
		}
		stat.process_number = stoi(process_num);
		stat.start_time = stoi(start_time);
		stat.cpu_time = stoi(cpu_time);
		stat.io_time = stoi(io_time);
		stats.push_back(stat);
	}
	mystream.close();
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


