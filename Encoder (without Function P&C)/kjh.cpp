/*
 * kjh.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: shayantaheri
 */


 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 #include <deque>
 using namespace std;

 class func_in {					// Type for parsing inputs of the gate.
 	public:
 		string in_name;				// Input Name
 		bool in_val;				// Input Value
 	};

 class opnd {						// Type for parsing operands of each input.
 	 public:
	 	 string opnd_name;
	 	 bool opnd_val;
 };

 bool plus (bool x, bool y) {		// Defining "+"
	 return x | y;
 }

 bool star (bool x, bool y) {		// Defining "*"
 	 return x & y;
  }

 bool exct (bool x) {				// Defining "!"
	 return !x;
 }


 int main()
 {

	deque<string> function; // input of this Function

	deque<string> temp_func;
	deque<func_in> func_inputs;

	deque<string> rest;

	temp_func.clear();
	func_inputs.clear();
	rest.clear();

	func_in init;
	init.in_name = "0";
	init.in_val = 0;

	deque<func_in>::size_type in_count = 0;

	function.push_back("A");
	function.push_back("+");
	function.push_back("B");
	function.push_back("#");
	function.push_back("*");
	function.push_back("C");
	function.push_back("#");
	function.push_back("+");
	function.push_back("D");
	function.push_back("#");

	temp_func = function;

	// ***********  OUTPUT Function *************

	for (deque<string>::size_type i1 = 0; i1 < function.size(); i1++) {
		cout << function[i1];
	}

	cout << endl;

	// ******************************************

	// Finding the Inputs

	in_count = 0;
	for (deque<string>::size_type i2 = 0; i2 < function.size(); i2++) {
		if (function [i2] != "+" && function [i2] != "#" && function [i2] != "*") {
			func_inputs.push_back(init);
			func_inputs[in_count].in_name = function[i2];
			in_count++;
		}
	}

	// ***********  OUTPUT Inputs *************

	for (deque<func_in>::size_type i3 = 0; i3 < func_inputs.size(); i3++) {
		cout << func_inputs[i3].in_name;
	}

	// ******************************************




	return 0;

 }


