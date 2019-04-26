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


 class func_in {						// Class for the inputs of the function.
  	public:
  		string in_name;					// Input Name
  		bool in_val;					// Input Value
  	};

  class split {							// Class for the splitter which places the function of each 2-Input gate in a section.
  	 public:
 	 	 deque<string> sect;			// The function of 2-Input gate = A section.
 	 	 string sign;					// The sign for the section.
 	 	 bool value;					// The result of each section "with considering the Sign".
  };

  class oprt_type {						// Class for major operators of the whole function.
  	 public:
 	 	 string oprt;					// Major operator
 	 	 string sign;					// Associated sign with major operator.
  };

  class encoder {
  public:
	  static std::vector<double> control_function (deque<string> FUNCTION);
  private:
	  static bool parse_calc (deque<string> function, deque<func_in> func_inputs);
	  static vector<std::vector<unsigned int> > TT_gen (unsigned int n);
  };



	 vector<double> cont_vals;

	 unsigned long long int conflict_count = 0;

	 bool temp_value = 0;

	 vector<bool> res0_vect, res1_vect;

	 double temp_cont = 0.0;

	 double tmp_size = 0.0;

	 vector<std::vector<unsigned int> > table;

	 deque<func_in> FUNC_INS;









  bool encoder::parse_calc (deque<string> function, deque<func_in> func_inputs) {

 	 	deque<split> splitter;							// For splitting the function based on the result of each 2-input gate.

 		splitter.clear();

 		split split_init;

 		split_init.sect.clear();

 		split_init.sign = "0";

 		split_init.value = 0;

 		deque<oprt_type> operate;						// Container for major operators (AND or OR) of the function.

 		operate.clear();

 		oprt_type oprt_init;

 		oprt_init.oprt = "0";

 		oprt_init.sign = "0";

 		string temp_oprt_signs;							// The signs for major operators.

 		temp_oprt_signs.clear();

 		vector<bool> vect_results;						// Container for the result of each section in "Splitter".

 		vect_results.clear();

 		bool final_result = 0;

 		unsigned long long input_iter = 0;				// Input iterator for the "func_inputs" container.

 		bool temp_res = 0;								// Raw result of the "parse_calc" function.

 		unsigned long long int mm = 0;					// Index for "splitter" container.

 		unsigned long long int pp = 0;					// Index for "operate" container.

 		bool add_sect = 0;								// Condition for adding section to "Splitter" container.



 		// *************************** Building the "Splitter" and "Major Operator" containers ********************************

 		splitter.push_back(split_init);
 		for (deque<string>::size_type ff = 0; ff < function.size(); ff++) {
 			if (function[ff] != "#") {
 				splitter[mm].sect.push_back(function[ff]);
 			}
 			else if (function[ff] == "#") {
 				if (ff+1 < function.size()) {ff++;}
 				splitter[mm].sign = function[ff];
 				if (ff+1 < function.size()) {ff++;}
 				add_sect = 0;
 				for (deque<string>::size_type tt = ff; tt < function.size(); tt++) {
 					if (function[tt] == "+" || function[tt] == "*") {
 						add_sect = 1;
 					}
 				}
 				if (add_sect == 1) {
 					mm++;
 					splitter.push_back(split_init);
 				}
 				while (function[ff] == "#") {
 					if (ff+1 < function.size()) {ff++;}
 					temp_oprt_signs += function[ff];
 					if (ff+1 < function.size()) {ff++;}
 				}
 				if (function[ff] == "*" || function[ff] == "+") {
 					operate.push_back(oprt_init);
 					operate[pp].oprt = function[ff];
 					pp++;
 				}
 			}
 		}

 		for (deque<oprt_type>::size_type ss = 0; ss < operate.size(); ss++) {
 			operate[ss].sign = temp_oprt_signs[operate.size()-1-ss];
 		}

 		// **********************************************************************************************************************



 		// *************************** Calculating the Result of each Section in Splitter ********************************

 		input_iter = 0;
 		for (deque<split>::size_type ww1 = 0; ww1 < splitter.size(); ww1++) {
 			temp_res = 0;

 			if (splitter[ww1].sect[0] != "YEK") {
 				if (splitter[ww1].sect[1] == "-") {
 					temp_res = func_inputs[input_iter].in_val;
 				}
 				else if (splitter[ww1].sect[1] == "!") {
 					temp_res = !func_inputs[input_iter].in_val;
 				}
 				if (input_iter+1 < func_inputs.size()) {input_iter++;}
 			}
 			else if (splitter[ww1].sect[0] == "YEK") {
 				temp_res = 1;
 			}

 			if (splitter[ww1].sect[3] != "YEK") {
 				if (splitter[ww1].sect[4] == "-") {
 					if (splitter[ww1].sect[2] == "+") {
 						temp_res = temp_res | func_inputs[input_iter].in_val;
 					}
 					else if (splitter[ww1].sect[2] == "*") {
 						temp_res = temp_res & func_inputs[input_iter].in_val;
 					}
 				}
 				else if (splitter[ww1].sect[4] == "!") {
 					if (splitter[ww1].sect[2] == "+") {
 						temp_res = temp_res | !func_inputs[input_iter].in_val;
 					}
 					else if (splitter[ww1].sect[2] == "*") {
 						temp_res = temp_res & !func_inputs[input_iter].in_val;
 					}
 				}
 				if (input_iter+1 < func_inputs.size()) {input_iter++;}
 			}
 			else if (splitter[ww1].sect[3] == "YEK") {
 				if (splitter[ww1].sect[2] == "*") {
 					temp_res = temp_res & 1;
 				}
 				else {
 					cerr << "ERROR!: In wire initialization.";
 				}
 			}

 			if (splitter[ww1].sign == "-") {
 				splitter[ww1].value = temp_res;
 			}
 			else if (splitter[ww1].sign == "!") {
 				splitter[ww1].value = !temp_res;
 			}

 		}

 		// ******************************************************************************************************************


 		// ********************* Calculating the "final_result" which is the result of whole function ***********************

 		for (deque<split>::size_type yy = 0; yy < splitter.size(); yy++) {
 			vect_results.push_back(splitter[yy].value);
 		}

 		for (deque<oprt_type>::size_type hh1 = operate.size()-1; (hh1 >= 0) && (vect_results.size() != 1); hh1--) {
 			if (operate[hh1].oprt == "+") {
 				final_result = vect_results[vect_results.size()-1] | vect_results[vect_results.size()-2];
 				if (operate[hh1].sign == "!") {
 					final_result = !final_result;
 				}
 			}
 			else if (operate[hh1].oprt == "*") {
 				final_result = vect_results[vect_results.size()-1] & vect_results[vect_results.size()-2];
 				if (operate[hh1].sign == "!") {
 					final_result = !final_result;
 				}
 			}
 			vect_results.pop_back();
 			vect_results.pop_back();
 			vect_results.push_back(final_result);
 		}

 		if (vect_results.size() != 1) {
 			cerr << "ERROR! : In calculation of parse_calc's result.";
 		}

 		else if (vect_results.size() == 1) {
 			final_result = vect_results[0];
 		}

 		// ******************************************************************************************************************


 		return final_result;

  }






 // ***************** TRUTH TABLE Start *******************

 vector< vector<unsigned int> > encoder::TT_gen (unsigned int n) {

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


 // ************************************** Generating Vector of Control Values **************************************

 std::vector<double> encoder::control_function (deque<string> FUNCTION) {

	 	/* vector<double> cont_vals;

	 	 unsigned long long int conflict_count = 0;

	 	 bool temp_value = 0;

	 	 vector<bool> res0_vect, res1_vect;

	 	 double temp_cont = 0.0;

	 	 double tmp_size = 0.0;*/

	 	 func_in init;

	 	 //deque<func_in> FUNC_INS;

	 	 srand (time(NULL));

	 	 //vector<std::vector<unsigned int> > table;

	 	 unsigned int rand_index[12];

	 	 deque<func_in> rand_inputs;

	 	 bool skip_cond = 0;

	 	 vector<unsigned long long int> rem_index;

	 	 rem_index.clear();

	 	 table.clear();

	 	 FUNC_INS.clear();

	 	 cont_vals.clear();

	 	 rand_inputs.clear();

	 	 init.in_name = "0";
	 	 init.in_val = 0;

	 	 deque<func_in>::size_type in_count = 0;


	 	// ***********  Finding Inputs *************

	 		in_count = 0;
	 		for (deque<string>::size_type i2 = 0; i2 < FUNCTION.size(); i2++) {
	 			if (FUNCTION [i2] != "+" && FUNCTION [i2] != "#" && FUNCTION [i2] != "*"
	 					&& FUNCTION [i2] != "-" && FUNCTION [i2] != "!") {
	 				FUNC_INS.push_back(init);
	 				FUNC_INS[in_count].in_name = FUNCTION[i2];
	 				in_count++;
	 			}
	 		}

	 	// ******************************************


	 	// ***********  Body of The Code *************

	 			if (FUNC_INS.size() <= 12) {

	 				table = TT_gen (FUNC_INS.size()-1);

	 			}

	 			else if (FUNC_INS.size() > 12) {

	 				table = TT_gen (11);

	 				rem_index.clear();
	 				for (unsigned int inp_num = 0; inp_num <= 11; inp_num++) {
	 					rand_index[inp_num] = rand() % (FUNC_INS.size());
	 				}

	 				for (unsigned long long int rem_num = 0; rem_num < FUNC_INS.size(); rem_num++) {
	 					skip_cond = 0;
	 					for (unsigned int cx1 = 0; cx1 <= 11; cx1++) {
	 						if (rem_num == rand_index[cx1]) {
	 							skip_cond = 1;
	 						}
	 					}
	 					if (skip_cond == 0) {
	 						rem_index.push_back(rem_num);
	 					}
	 				}

	 				for (unsigned int r1 = 0; r1 <= 11; r1++) {
	 					rand_inputs.push_back(FUNC_INS[rand_index[r1]]);
	 				}

	 				for (vector<unsigned long long int>::size_type lx = 0; lx < rem_index.size(); lx++) {
	 					FUNC_INS[rem_index[lx]].in_val = rand() % 2;
	 					rand_inputs.push_back(FUNC_INS[rem_index[lx]]);
	 				}

	 				FUNC_INS.clear();
	 				FUNC_INS = rand_inputs;

	 			}

	 	// ******************************************







	 	 for (deque<string>::size_type ptr = 0; ptr < FUNC_INS.size(); ptr++) {

	 		if (FUNC_INS[ptr].in_name == "YEK") {
	 			continue;
	 		}
	 		res0_vect.clear();
	 		res1_vect.clear();
	 		conflict_count = 0;
	 		temp_cont = 0.0;
	 		tmp_size = 0.0;

	 		FUNC_INS[ptr].in_val = 0;
	 		for (unsigned long long tab0_indx = 0; tab0_indx < table[0].size(); tab0_indx++) {
	 			temp_value = 0;
	 			if (ptr == 0) {
	 				for(unsigned long long kk0 = 0; kk0 < table.size(); kk0++) {
	 					FUNC_INS[kk0+1].in_val = table[kk0][tab0_indx];
	 				}
	 			}
	 			else if (ptr > 0) {
	 				for(unsigned long long yy0 = 0; yy0 < ptr; yy0++) {
	 					FUNC_INS[yy0].in_val = table[yy0][tab0_indx];
	 				}
	 				if (ptr < table.size() && ptr+1 < FUNC_INS.size()) {
	 					FUNC_INS[ptr+1].in_val = table[ptr][tab0_indx];
	 				}
	 				if (ptr+1 < table.size() && ptr+2 < FUNC_INS.size()) {
	 					for(unsigned long long zz0 = ptr+1; zz0 < table.size(); zz0++) {
	 						FUNC_INS[zz0+1].in_val = table[zz0][tab0_indx];
	 					}
	 				}
	 			}
	 			temp_value = parse_calc (FUNCTION, FUNC_INS);;
	 			res0_vect.push_back(temp_value);
	 		}

	 		FUNC_INS[ptr].in_val = 1;
	 		for (unsigned long long tab1_indx = 0; tab1_indx < table[0].size(); tab1_indx++) {
	 			 temp_value = 0;
	 			 if (ptr == 0) {
	 			 	for(unsigned long long kk1 = 0; kk1 < table.size(); kk1++) {
	 			 		FUNC_INS[kk1+1].in_val = table[kk1][tab1_indx];
	 			 	}
	 			 }
	 			 else if (ptr > 0) {
	 			 	for(unsigned long long yy1 = 0; yy1 < ptr; yy1++) {
	 			 		FUNC_INS[yy1].in_val = table[yy1][tab1_indx];
	 			 	}
	 			 	if (ptr < table.size() && ptr+1 < FUNC_INS.size()) {
	 			 		FUNC_INS[ptr+1].in_val = table[ptr][tab1_indx];
	 			 	}
	 			 	if (ptr+1 < table.size() && ptr+2 < FUNC_INS.size()) {
	 			 		for(unsigned long long zz0 = ptr+1; zz0 < table.size(); zz0++) {
	 			 			FUNC_INS[zz0+1].in_val = table[zz0][tab1_indx];
	 			 		}
	 			 	}
	 			 }
	 			 temp_value = parse_calc (FUNCTION, FUNC_INS);;
	 			 res1_vect.push_back(temp_value);
	 		}

	 		conflict_count = 0;
	 		for (vector<bool>::size_type dd1 = 0; dd1 < res0_vect.size(); dd1++) {
	 			if (res0_vect[dd1] != res1_vect[dd1]) {
	 				conflict_count++;
	 			}
	 		}

	 		tmp_size = table.size();
	 		temp_cont = conflict_count / pow (2.0, tmp_size);
	 		cont_vals.push_back(temp_cont);

		}

	 	return cont_vals;

 }

 // **************************************************************************************************



 int main()
 {


	 	 // ************* PARSE and FUNCTION Verification *************


	 	 deque<string> test_func; 					// The Function

	 	 //deque<func_in> test_ins;					// The Inputs

	 	 test_func.clear();

	 	 //test_ins.clear();

	 	 func_in init;
	 	 init.in_name = "0";
	 	 init.in_val = 0;

	 	 //bool test_result;

	 	 test_func.push_back("D");test_func.push_back("-");test_func.push_back("*");test_func.push_back("H");test_func.push_back("-");
	 	 test_func.push_back("#");test_func.push_back("-");test_func.push_back("+");test_func.push_back("Y");test_func.push_back("!");
	 	 test_func.push_back("+");test_func.push_back("Z");test_func.push_back("-");test_func.push_back("#");test_func.push_back("-");
	 	 test_func.push_back("*");test_func.push_back("G");test_func.push_back("!");test_func.push_back("*");test_func.push_back("YEK");
	 	 test_func.push_back("-");test_func.push_back("#");test_func.push_back("-");test_func.push_back("#");test_func.push_back("!");
	 	 test_func.push_back("#");test_func.push_back("-");


	 // **************** Encoder Verification : control_function ****************


	// The function : test_func

	// Function's Inputs : test_ins

	//srand (time(NULL));

	vector<double> control_values;		// Vector of Control Values

	/*vector<std::vector<unsigned int> > truth_table;

	unsigned int rand_index[12];

	deque<func_in> rand_inputs;

	control_values.clear();

	truth_table.clear();

	init.in_name = "0";
	init.in_val = 0;

	deque<func_in>::size_type in_count = 0;


	// ***********  Finding Inputs *************

	in_count = 0;
	for (deque<string>::size_type i2 = 0; i2 < test_func.size(); i2++) {
		if (test_func [i2] != "+" && test_func [i2] != "#" && test_func [i2] != "*"
				&& test_func [i2] != "-" && test_func [i2] != "!") {
			test_ins.push_back(init);
			test_ins[in_count].in_name = test_func[i2];
			in_count++;
		}
	}

	// ******************************************


	// ***********  Body of The Code *************

		if (test_ins.size() <= 12) {

			truth_table = TT_gen (test_ins.size()-1);

			control_values = encoder::control_function (test_func, test_ins, truth_table);

		}

		else if (test_ins.size() > 12) {

			truth_table = TT_gen (11);

			for (unsigned int inp_num = 0; inp_num <= 11; inp_num++) {
				rand_index[inp_num] = rand() % (test_ins.size());
			}

			for (unsigned int r1 = 0; r1 <= 11; r1++) {
				rand_inputs.push_back(test_ins[rand_index[r1]]);
			}

			control_values = encoder::control_function (test_func, rand_inputs, truth_table);

		}

	// ******************************************

*/


	control_values = encoder::control_function (test_func);


	// test_result = parse_calc (test_func, test_ins);


	// OUTPUT Function:

	for (deque<string>::size_type i1 = 0; i1 < FUNC_INS.size(); i1++) {
		cout << FUNC_INS[i1].in_name << "-----";
	}

	cout << endl;

	//cout << table[0].size() << endl;

	for (vector<double>::size_type jj1 = 0; jj1 < control_values.size(); jj1++) {
		cout << control_values[jj1] << "---";
	}

	//for (vector<double>::size_type eex1 = 0; eex1 < res1_vect.size(); eex1++) {
	//	cout << res1_vect[eex1] << "---";
	//}



	return 0;

 }

