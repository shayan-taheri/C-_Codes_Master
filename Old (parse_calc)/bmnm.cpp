/*
 * bmnm.cpp
 *
 *  Created on: May 10, 2014
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

 bool parse_calc (deque<string> function, deque<func_in> func_inputs) {

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

		// ******************************************************************************************************************


		return final_result;

 }


 int main()
 {

	 deque<string> test_func; // input of this test_func

	 deque<func_in> test_ins;

	 func_in init;
	 init.in_name = "0";
	 init.in_val = 0;

	 bool test_result;

	 test_func.push_back("D");
	 test_func.push_back("-");
	 test_func.push_back("+");
	 test_func.push_back("X");
	 test_func.push_back("!");
	 test_func.push_back("#");
	 test_func.push_back("-");
	 test_func.push_back("+");
	 test_func.push_back("Y");
	 test_func.push_back("!");
	 test_func.push_back("+");
	 test_func.push_back("Z");
	 test_func.push_back("-");
	 test_func.push_back("#");
	 test_func.push_back("-");
	 test_func.push_back("*");
	 test_func.push_back("K");
	 test_func.push_back("!");
	 test_func.push_back("*");
	 test_func.push_back("N");
	 test_func.push_back("-");
	 test_func.push_back("#");
	 test_func.push_back("-");
	 test_func.push_back("#");
	 test_func.push_back("!");
	 test_func.push_back("#");
	 test_func.push_back("-");

	 test_ins.push_back(init);
	 test_ins[0].in_name = "D";
	 test_ins[0].in_val = 0;

	 test_ins.push_back(init);
	 test_ins[1].in_name = "X";
	 test_ins[1].in_val = 1;

	 test_ins.push_back(init);
	 test_ins[2].in_name = "Y";
	 test_ins[2].in_val = 0;

	 test_ins.push_back(init);
	 test_ins[3].in_name = "Z";
	 test_ins[3].in_val = 0;

	 test_ins.push_back(init);
	 test_ins[4].in_name = "K";
	 test_ins[4].in_val = 1;

	 test_ins.push_back(init);
	 test_ins[5].in_name = "N";
	 test_ins[5].in_val = 1;

	 test_result = parse_calc (test_func, test_ins);

	 for (deque<string>::size_type xx = 0; xx < test_func.size(); xx++) {
	     cout << test_func[xx];
	 }

	 cout << endl << test_result;


	 return 0;

}




