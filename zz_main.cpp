//============================================================================
// Name        : codeEval.cpp
// Author      : DaisySun
// Version     :
// Copyright   : Released by DaisySun
// Description : https://www.codeeval.com/open_challenges/48/
//============================================================================

/*
 * Challenge Description:

 Our marketing department has just negotiated a deal with several local merchants that will allow us to offer exclusive discounts on various products to our top customers every day. The catch is that we can only offer each product to one customer and we may only offer one product to each customer.

 Each day we will get the list of products that are eligible for these special discounts. We then have to decide which products to offer to which of our customers. Fortunately, our team of highly skilled statisticians has developed an amazing mathematical model for determining how likely a given customer is to buy an offered product by calculating what we call the "suitability score" (SS). The top-secret algorithm to calculate the SS between a customer and a product is this:

 1. If the number of letters in the product's name is even then the SS is the number of vowels (a, e, i, o, u, y) in the customer's name multiplied by 1.5.
 2. If the number of letters in the product's name is odd then the SS is the number of consonants in the customer's name.
 3. If the number of letters in the product's name shares any common factors (besides 1) with the number of letters in the customer's name then the SS is multiplied by 1.5.

 Your task is to implement a program that assigns each customer a product to be offered in a way that maximizes the combined total SS across all of the chosen offers. Note that there may be a different number of products and customers. You may include code from external libraries as long as you cite the source.

 Input sample:

 Your program should accept as its only argument a path to a file. Each line in this file is one test case. Each test case will be a comma delimited set of customer names followed by a semicolon and then a comma delimited set of product names. Assume the input file is ASCII encoded. For example (NOTE: The example below has 3 test cases):


 Jack Abraham,John Evans,Ted Dziuba;iPad 2 - 4-pack,Girl Scouts Thin Mints,Nerf Crossbow
 Jeffery Lebowski,Walter Sobchak,Theodore Donald Kerabatsos,Peter Gibbons,Michael Bolton,Samir Nagheenanajar;Half & Half,Colt M1911A1,16lb bowling ball,Red Swingline Stapler,Printer paper,Vibe Magazine Subscriptions - 40 pack
 Jareau Wade,Rob Eroh,Mahmoud Abdelkader,Wenyi Cai,Justin Van Winkle,Gabriel Sinkin,Aaron Adelson;Batman No. 1,Football - Official Size,Bass Amplifying Headphones,Elephant food - 1024 lbs,Three Wolf One Moon T-shirt,Dom Perignon 2000 Vintage
 Output sample:

 For each line of input, print out the maximum total score to two decimal places. For the example input above, the output should look like this:

 21.00
 83.50
 71.25
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void showVector(vector<string>& v) {
	for (unsigned i = 0; i < v.size(); i++)
		cout << "(" << v.at(i) << ")" << " ";
	cout << endl;
}

int numberofLetters(string& s) {
	int num = 0;
	for (unsigned i = 0; i < s.size(); i++) {
		if (s.at(i) >= 'a' && s.at(i) <= 'z') num++;
		if (s.at(i) >= 'A' && s.at(i) <= 'Z') num++;
	}
	return num;
}

int getNumberOfVowels(string& s) {
	unsigned i = 0;
	int count = 0;
	while (i < s.size()) {
		if (s.at(i) == 'a' || s.at(i) == 'A' || s.at(i) == 'e' || s.at(i) == 'E'
		        || s.at(i) == 'i' || s.at(i) == 'I' || s.at(i) == 'o'
		        || s.at(i) == 'O' || s.at(i) == 'y' || s.at(i) == 'Y'
		        || s.at(i) == 'u' || s.at(i) == 'U') {
			count++;
		}
		i++;
	}
	return count;
}

int getNumberofConsonants(string&s) {
	return numberofLetters(s) - getNumberOfVowels(s);
}

bool shareCommonFactor(string& name, string& produce) {
	int a = numberofLetters(name);
	int b = numberofLetters(produce);

	int remainder;
	while (b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	if (a == 1) return false;
	else return true;
}

double calculateSS(string& name, string& product) {

	double rst = 0;
	//case 1, name even
	if (numberofLetters(product) % 2 == 0) {
		rst = getNumberOfVowels(name) * 1.5;
	}
	//case 2, name odd
	else {
		rst = getNumberofConsonants(name);
	}
	// additional case 3
	if (shareCommonFactor(name, product)) rst *= 1.5;

	return rst;
}
//"," as separator, end exclusive
void getItems(string & input, vector<string>& items, const int start,
        const int end) {

	int start_the_word = start;
	int end_the_word; //exclusive

	while (true) {
		end_the_word = input.find_first_of(',', start_the_word);
		if (end_the_word < 0 || end_the_word >= end) {
			items.push_back(input.substr(start_the_word, end - start_the_word));
			break;
		} else items.push_back(
		        input.substr(start_the_word, end_the_word - start_the_word));

		start_the_word = end_the_word + 1;
	}
}

void getNamesandProductsFromString(string & input, vector<string>& names,
        vector<string>&produces) {
	//Jack Abraham,John Evans,Ted Dziuba;iPad 2 - 4-pack,Girl Scouts Thin Mints,Nerf Crossbow
	int end_of_names = input.find_first_of(";");
	getItems(input, names, 0, end_of_names);
	getItems(input, produces, end_of_names + 1, input.size());

}

double maxSSnew(vector<string>& names, vector<string>& produces) {
	double max_sum = 0;
	double sum = 0;
	vector<bool> bought(produces.size(), false);
	vector<double> this_customer_ss(produces.size(), false);
	vector<vector<double> > ss_matrix(names.size(), this_customer_ss);

	for (unsigned i = 0; i < names.size(); i++) {
		for (unsigned j = 0; j < produces.size(); j++) {
			ss_matrix.at(i).at(j) = calculateSS(names.at(i), produces.at(j));
		}
	}

	return max_sum;
}

double maxSS(vector<string>& names, vector<string>& produces) {
	double sum = 0;
	double tmp;
	for (unsigned i = 0; i < names.size(); i++) {
		double max_for_this_person = 0;
		for (unsigned j = 0; j < produces.size(); j++) {
			tmp = calculateSS(names.at(i), produces.at(j));
			cout << names.at(i) << "  and   " << produces.at(j) << "= " << tmp
			        << endl;
			if (tmp > max_for_this_person) max_for_this_person = tmp;
		}
		sum += max_for_this_person;
	}
	return sum;
}

int main(int argc, char* argv[]) {
	/*ifstream file;
	 string lineBuffer;
	 file.open(argv[1]);
	 while (!file.eof()) {
	 getline(file, lineBuffer);
	 if (lineBuffer.length() == 0) continue; //ignore all empty lines
	 else {
	 //do something here
	 }
	 }*/

	string lineBuffer(
	        "Jareau Wade,Rob Eroh,Mahmoud Abdelkader,Wenyi Cai,Justin Van Winkle,Gabriel Sinkin,Aaron Adelson;Batman No. 1,Football - Official Size,Bass Amplifying Headphones,Elephant food - 1024 lbs,Three Wolf One Moon T-shirt,Dom Perignon 2000 Vintage");
	vector<string> names;
	vector<string> produces;
	getNamesandProductsFromString(lineBuffer, names, produces);
	showVector(names);
	showVector(produces);
	double rst = maxSS(names, produces);
	cout << rst << endl;

	/*string s("Wenyi Cai");
	 cout<<"numberofLetters="<<numberofLetters(s)<<endl;
	 cout<<"getNumberofConsonants="<<getNumberofConsonants(s)<<endl;
	 cout<<"getNumberOfVowels="<<getNumberOfVowels(s)<<endl;*/

	return 0;
}
