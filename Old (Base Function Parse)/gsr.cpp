/*
 * gsr.cpp
 *
 *  Created on: May 9, 2014
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

 class func_in {					// Type for parsing inputs of the gate.
 	public:
 		string in_name;				// Input Name
 		bool in_val;				// Input Value
 	};

 class split {
 	 public:
	 	 deque<string> sect;
	 	 string sign;
	 	 bool value;
 };

 class oprt_type {
 	 public:
	 	 string oprt;
	 	 string sign;
 };


 int main()
 {

	deque<string> function; // input of this Function

	function.push_back("D");
	function.push_back("-");
	function.push_back("+");
	function.push_back("X");
	function.push_back("!");
	function.push_back("#");
	function.push_back("-");
	function.push_back("+");
	function.push_back("Y");
	function.push_back("!");
	function.push_back("+");
	function.push_back("Z");
	function.push_back("-");
	function.push_back("#");
	function.push_back("-");
	function.push_back("*");
	function.push_back("K");
	function.push_back("!");
	function.push_back("*");
	function.push_back("N");
	function.push_back("-");
	function.push_back("#");
	function.push_back("-");
	function.push_back("#");
	function.push_back("!");
	function.push_back("#");
	function.push_back("-");

	for (deque<string>::size_type xx = 0; xx < function.size(); xx++) {
		cout << function[xx];
	}


	deque<func_in> func_inputs;

	func_in init;
	init.in_name = "0";
	init.in_val = 0;

	func_inputs.push_back(init);
	func_inputs[0].in_name = "D";
	func_inputs[0].in_val = 0;

	func_inputs.push_back(init);
	func_inputs[1].in_name = "X";
	func_inputs[1].in_val = 1;

	func_inputs.push_back(init);
	func_inputs[2].in_name = "Y";
	func_inputs[2].in_val = 0;

	func_inputs.push_back(init);
	func_inputs[3].in_name = "Z";
	func_inputs[3].in_val = 0;

	func_inputs.push_back(init);
	func_inputs[4].in_name = "K";
	func_inputs[4].in_val = 1;

	func_inputs.push_back(init);
	func_inputs[5].in_name = "N";
	func_inputs[5].in_val = 1;

	deque<string> temp_function;

	temp_function.clear();

	deque<split> splitter;

	splitter.clear();

	split split_init;

	split_init.sect.clear();

	split_init.sign = "0";

	split_init.value = 0;

	deque<oprt_type> operate;

	operate.clear();

	oprt_type oprt_init;

	oprt_init.oprt = "0";

	oprt_init.sign = "0";

	string temp_oprt_signs;

	temp_oprt_signs.clear();

	vector<bool> vect_results;

	vect_results.clear();

	deque<oprt_type> operate_mani;

	operate_mani.clear();

	bool final_result = 0;

	unsigned long long input_iter = 0;

	bool temp_res = 0;

	unsigned long long int mm = 0;

	unsigned long long int pp = 0;

	unsigned int add_sect = 0;

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
				cerr << "ERROR!";
			}
		}

		if (splitter[ww1].sign == "-") {
			splitter[ww1].value = temp_res;
		}
		else if (splitter[ww1].sign == "!") {
			splitter[ww1].value = !temp_res;
		}

	}

	for (deque<split>::size_type yy = 0; yy < splitter.size(); yy++) {
		vect_results.push_back(splitter[yy].value);
	}

	operate_mani = operate;

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






	// *********************** Testing Outcomes ***************************

	cout << endl;

	for (unsigned int qq = 0; qq < splitter.size(); qq++) {
		for (unsigned int qqx = 0; qqx < splitter[qq].sect.size(); qqx++) {
			cout << splitter[qq].sect[qqx];
		}
		cout << " " << splitter[qq].sign << " " << splitter[qq].value << endl;
	}

	for (unsigned int qq = 0; qq < operate.size(); qq++) {
		cout << operate[qq].oprt << " " << operate[qq].sign << endl;
	}

	cout << final_result;

	// ********************************************************************


	return 0;

}
