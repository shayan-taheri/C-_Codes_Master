/*
 * dsvz.cpp
 *
 *  Created on: May 8, 2014
 *      Author: shayantaheri
 */


 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 #include <deque>
 #include <vector>
 #include <math.h>
 #include <cmath>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 using namespace std;


 // ***************** TRUTH TABLE Start *******************

 static std::vector<std::vector<unsigned int> > TT_gen (unsigned int n) {

 	std::vector<std::vector<unsigned int> > output(n, std::vector<unsigned int>(1 << n));

 	    unsigned num_to_fill = 1U << (n - 1);
 	    for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
 	    {
 	        for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
 	        {
 	            std::fill_n(&output[col][row], num_to_fill, 1);
 	        }
 	    }

 	    return output;
 }

 // ******************* TRUTH TABLE End *********************



 // ***************** Function's Inputs Type *******************

 class func_in {					// Type for parsing inputs of the gate.
 	public:
 		string in_name;				// Input Name
 		bool in_val;				// Input Value
 	};

 // ************************************************************



 // ************************************** Generating Vector of Control Values **************************************

 std::vector<double> control_function (deque<func_in> & FUNC_INS, vector<std::vector<unsigned int> > & table) {

	 	 vector<double> cont_vals;

	 	 bool res1 = 0, res2 = 0;

	 	 long unsigned int conflict_count = 0;

	 	 double temp_cont = 0.0;

	 	 cont_vals.clear();

	 	 srand (time(NULL));

	 	 for (deque<string>::size_type ptr = 0; ptr < FUNC_INS.size(); ptr++) {

					for(unsigned x = 0; x < table[0].size(); x++)
					{

						FUNC_INS[ptr].in_val = 0;

						if (ptr > 0) {

							for(unsigned yy = 0; yy < ptr; yy++) {
								FUNC_INS[yy].in_val = table[yy][x];}

							for(unsigned zz = ptr+1; zz < table.size(); zz++) {
								FUNC_INS[zz].in_val = table[zz][x];}

						}

						else if (ptr == 0) {

							for(unsigned kk = 1; kk < table.size(); kk++) {
								FUNC_INS[kk].in_val = table[kk][x];}

						}

						// res1 = parse_calc (FUNCTION,FUNC_INS)

						FUNC_INS[ptr].in_val = 1;

						// res2 = parse_calc (FUNCTION,FUNC_INS)

						// if (res1 != res2) {
						//		conflict_count++;}

					}

					// temp_cont = conflict_count / pow (2.0, FUNC_INS.size()-1);
					// cont_vals.push_back(temp_cont);

		}

	 	return cont_vals;

 }

 // **************************************************************************************************



 int main()
 {

	deque<string> function;				// The Function of the Wire

	deque<func_in> func_inputs;			// Inputs of the Function

	vector<double> control_values;		// Vector of Control Values

	vector<std::vector<unsigned int> > truth_table;

	unsigned int rand_index[12];

	deque<func_in> rand_inputs;

	func_inputs.clear();

	control_values.clear();

	truth_table.clear();

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


	// ***********  Finding Inputs *************

	in_count = 0;
	for (deque<string>::size_type i2 = 0; i2 < function.size(); i2++) {
		if (function [i2] != "+" && function [i2] != "#" && function [i2] != "*") {
			func_inputs.push_back(init);
			func_inputs[in_count].in_name = function[i2];
			in_count++;
		}
	}

	// ******************************************


	// ***********  Body of The Code *************

		if (func_inputs.size() <= 12) {

			truth_table = TT_gen (func_inputs.size()-1);

			control_values = control_function (func_inputs, truth_table);

		}

		else if (func_inputs.size() > 12) {

			truth_table = TT_gen (11);

			for (unsigned int inp_num = 0; inp_num <= 11; inp_num++) {
				rand_index[inp_num] = rand() % (func_inputs.size());
			}

			for (unsigned int r1 = 0; r1 <= 11; r1++) {
				rand_inputs.push_back(func_inputs[rand_index[r1]]);
			}

			control_values = control_function (rand_inputs, truth_table);

		}

	// ******************************************











	// OUTPUT Function:

	for (deque<string>::size_type i1 = 0; i1 < function.size(); i1++) {
		cout << function[i1];
	}

	cout << endl;


	// OUTPUT Inputs:

	for (deque<func_in>::size_type i3 = 0; i3 < func_inputs.size(); i3++) {
		cout << func_inputs[i3].in_name;
	}

	return 0;

 }

