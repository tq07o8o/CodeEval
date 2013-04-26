/*
 * https://www.codeeval.com/open_challenges/56/
 *
 *
 * Robot Movements
 *
Challenge Description:

A robot is located at the top-left corner of a 4x4 grid. The robot can move either up, down, left, or right, but can not visit the same spot twice. The robot is trying to reach the bottom-right corner of the grid.

Input sample:

There is no input for this program.

Output sample:

Print out the unique number of ways the robot can reach its destination. (The number should be printed as an integer whole number eg. if the answer is 10 (its not !!), print out 10, not 10.0 or 10.00 etc)
 */


#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
const int SURROUND_EDGE = 2;
const int MATRIX_SIZE = 4 + SURROUND_EDGE;

void robotGo(vector<vector<bool> >  map, int x, int y, int & count) {
	if (map.at(x).at(y) == true) return;

	if (x == MATRIX_SIZE - SURROUND_EDGE && y == MATRIX_SIZE - SURROUND_EDGE) {
		count++;
		return;
	}
	map.at(x).at(y) = true;
	robotGo(map, x + 1, y,count);
	robotGo(map, x - 1, y,count);
	robotGo(map, x, y+1,count);
	robotGo(map, x, y-1,count);
}

void FourMatrixRobot(){
	//init a bigger map
	vector<bool> this_row(MATRIX_SIZE, false);
	vector<vector<bool> > map(MATRIX_SIZE, this_row);

	//surround map with true
	vector<bool> true_row(MATRIX_SIZE,true);
	map.at(0) = true_row;
	map.at(map.size() - 1) = true_row;
	for (int i = 1; i < MATRIX_SIZE - 1; i++) {
		map.at(i).at(0) = true;
		map.at(i).at(MATRIX_SIZE - 1) = true;
	}

	int count_ways = 0;
	robotGo(map,1,1,count_ways);
	cout<<count_ways<<endl;

}
