/*
 *
 * Mth to last element  Share on LinkedIn

 Challenge Description:

 Write a program to determine the Mth to last element of a list.

 Input sample:

 The first argument will be a text file containing a series of space delimited characters followed by an integer representing a index into the list(1 based), one per line. e.g.

 a b c d 4
 e f g h 2
 Output sample:

 Print to stdout, the Mth element from the end of the list, one per line. If the index is larger than the list size, ignore that input.
 e.g.

 a
 g
 Submit your solution in a file (some file name).(py2| c| cpp| java| rb| pl| php| tcl| clj| js| scala| cs| m| py3) or use the online editor.
 */
#ifndef LAST_N_CHAR_HPP_
#define LAST_N_CHAR_HPP_


#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

void showTheNthChar(string& in) {
	int last_space = in.find_last_of(' ');

	int position_from_back = 0;
	int pos_tmp = last_space + 1;
	while (pos_tmp < in.size()) {
		position_from_back *= 10;
		position_from_back += in.at(pos_tmp) - '0';
		pos_tmp++;
	}

	in.erase(last_space + 1, in.size() - last_space - 1);

	int position_from_front = in.size() - position_from_back * 2;
	if (position_from_front >= 0) cout << in.at(position_from_front) << endl;
}



#endif /* LAST_N_CHAR_HPP_ */
