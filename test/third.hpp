/*
 * third.hpp
 *
 *  Created on: May 10, 2014
 *      Author: shayantaheri
 */

#ifndef THIRD_HPP_
#define THIRD_HPP_

#include "second.hpp"

class split;

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



#endif /* THIRD_HPP_ */
