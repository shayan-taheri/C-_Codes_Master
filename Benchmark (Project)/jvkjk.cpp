/*
 * jvkjk.cpp
 *
 *  Created on: May 12, 2014
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

 class wire {								// Class (Type) for Wires
 public:
 	string w_name;							// Name of Wire
 	bool value;								// Value of Wire
 	vector<double> cont_val;				// Control Values of Wire
 	deque<string> w_func;};					// Functionality of Wire


 class gate {								// Class (Type) for Gates
 public:
 	string g_name;							// Name of Gate
 	vector <wire> inputs;					// Inputs of Gate
 	vector <wire> outputs;};				// Outputs of Gate


 class index_type {							// Class (Type) for Obtaining Sort Indices
 public:
	 vector<gate>::size_type old_index;		// Old Index
	 vector<gate>::size_type new_index;		// New Index
 };


 bool compare_func (index_type S1, index_type S2) {			// Function for Sorting Gates based on New Indices
	 return S1.new_index < S2.new_index;
 }


 // ******************* Function for Reading the Input File and Building Gates , Inputs , and Outputs containers **********************

 void benchmark_parse (ifstream& fp, vector<gate>& gates) {		// vector <gate> gates: All of the Gates in the Circuit.
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	    // ifstream& fp: Input File Stream

	 string temp_line;													// Temporary Fetched Line.
	 unsigned long long int i = 0, j = 0, k = 0;
	 unsigned long long int name = 0, senc = 0, inp = 0, oup = 0;
	 wire winit;
	 gate ginit;
	 winit.w_name = "0";
	 winit.value = 0;
	 ginit.g_name = "0";
	 ginit.inputs.push_back(winit);
	 ginit.outputs.push_back(winit);
	 string::size_type gx, kx;
	 bool build_func = 0;
	 vector <gate>::size_type current_index = 0, max_index = 0;
	 vector <gate>::iterator insert_iter, erase_iter;
	 vector<string> outputs_name;
	 vector<index_type> Indices;
	 index_type index_init;
	 vector<gate> temp_gates;
	 bool check_again = 0;
	 outputs_name.clear();

	 if (fp.is_open())
	 {
	     while (getline (fp, temp_line))
	     {
	         // ****** Building Gates (Names) ******

	         gates.push_back(ginit);
	         gx = 0;
	         for (gx = 0; temp_line[gx] == ' ';) {
	             gx++;}

	         name = 0;
	         for (; temp_line[gx] != ' '; gx++) {
	             if (name >= 1) {
	                 gates[i].g_name.push_back(temp_line[gx]);}
	             else gates[i].g_name = temp_line[gx];
	                 name++;
	         }

	         // ************************************

	         // ********* Building Inputs **********

	         senc = 0;
	         j = 0;
	         gx = 0;
	         kx = 0;
	         for (;temp_line[senc] != ';';) {
	             for (; temp_line[gx] != '.';) {
	                 gx++;}

	             kx = gx + 1;

	             if (temp_line[kx] == 'A') {
	                 if (j >= 1) {
	                     gates[i].inputs.push_back(winit);}
	                 gx = gx + 3;
	                 inp = 0;
	                 for (; temp_line[gx] != ')'; gx++) {
	                     if (inp >= 1) {
	                         gates[i].inputs[j].w_name.push_back(temp_line[gx]);}
	                     else gates[i].inputs[j].w_name = temp_line[gx];
	                         inp++;
	                 }
	                 j++;
	             }

	             if (temp_line[senc] != ';') {senc++;}
	         }

	         // ************************************

	         // ********* Building Outputs *********


	         senc = 0;
	         k = 0;
	         gx = 0;
	         kx = 0;
	         for (;temp_line[senc] != ';';) {
	             for (; temp_line[gx] != '.';) {
	                 gx++;}

	             if (temp_line[gx+1] == 'A') {gx++;}

	             kx = gx + 1;

	             if (temp_line[kx] == 'Z') {
	                 if (k >= 1) {
	                     gates[i].outputs.push_back(winit);}
	                 gx = gx + 3;
	                 oup = 0;
	                 for (; temp_line[gx] != ')'; gx++) {
	                     if (oup >= 1) {
	                         gates[i].outputs[k].w_name.push_back(temp_line[gx]);}
	                     else gates[i].outputs[k].w_name = temp_line[gx];
	                         oup++;
	                 }
	                 k++;
	             }

	             if (temp_line[senc] != ';') {senc++;}
	         }

	         // ************************************

	         i++;
	     }
	 }

	 // **********************************************************************************************************************


	 // ******************* Initializing and Formatting Inputs (Values and Functionalities) **********************

	 for (vector<gate>::size_type ss1 = 0; ss1 < gates.size(); ss1++) {
		 for (vector<wire>::size_type ss2 = 0; ss2 < gates[ss1].outputs.size(); ss2++) {
			 outputs_name.push_back(gates[ss1].outputs[ss2].w_name);
		 }
	 }

	 for (vector<gate>::size_type uu1 = 0; uu1 < gates.size(); uu1++) {
	     for (vector<wire>::size_type uu2 = 0; uu2 < gates[uu1].inputs.size(); uu2++) {
	         build_func = 0;
	    	 for (vector<string>:: size_type uu3 = 0; uu3 < outputs_name.size(); uu3++) {
	        	 if (gates[uu1].inputs[uu2].w_name == outputs_name[uu3]) {
	        		 build_func = 1;
	        		 break;
	        	 }
	         }
	         if (build_func == 0) {
	        	 gates[uu1].inputs[uu2].w_func.push_back(gates[uu1].inputs[uu2].w_name);
	        	 gates[uu1].inputs[uu2].w_func.push_back("-");
	        	 gates[uu1].inputs[uu2].w_func.push_back("*");
	        	 gates[uu1].inputs[uu2].w_func.push_back("ONE");
	        	 gates[uu1].inputs[uu2].w_func.push_back("-");
	        	 gates[uu1].inputs[uu2].w_func.push_back("#");
	        	 gates[uu1].inputs[uu2].w_func.push_back("-");
	         }
	     }
	 }

	 // **********************************************************************************************************


	 // ******************************** Sorting Gates based on the Outputs **************************************

	 check_again = 1;
	 while (check_again == 1) {
		 Indices.clear();
		 for (vector<gate>::size_type pp1 = 0; pp1 < gates.size(); pp1++) {
		 current_index = pp1;
		 max_index = pp1;
		 Indices.push_back(index_init);

		 for (vector<wire>::size_type pp2 = 0; pp2 < gates[pp1].inputs.size(); pp2++) {
			for (vector<gate>::size_type ggx = 0; ggx < gates.size(); ggx++) {
				for (vector<string>::size_type pp3 = 0; pp3 < gates[ggx].outputs.size(); pp3++) {
					 if (gates[pp1].inputs[pp2].w_name == gates[ggx].outputs[pp3].w_name) {
						 if (ggx > max_index) {
							 max_index = ggx;
						 }
					 }
				 }
			 }
		 }

		 if (current_index < max_index) {
			 Indices[pp1].new_index = max_index+1;
		 }
		 else if (current_index >= max_index) {
			 Indices[pp1].new_index = current_index;
		 }

		 Indices[pp1].old_index = current_index;
		 }

		 check_again = 0;
		 for (vector<index_type>::size_type ff1 = 0; ff1 < Indices.size(); ff1++) {
			 if (Indices[ff1].new_index != Indices[ff1].old_index) {
				 check_again = 1;
			 }
		 }

		 sort (Indices.begin(), Indices.end(), compare_func);

		 temp_gates.clear();
		 for (vector<gate>::size_type zz1 = 0; zz1 < gates.size();  zz1++) {
			 temp_gates.push_back(gates[Indices[zz1].old_index]);
		 }

		 gates = temp_gates;

	 }


	 // **********************************************************************************************************

 }


int main()
	{

			ifstream file_input ("input_file.txt");
			vector<gate> circuit_gates;

			benchmark_parse (file_input, circuit_gates);

			// *** Testing the Code ***

			//cout << "INPUTS Functionality:" << endl << circuit_gates.size() << endl;

			//for (vector <index_type>::size_type ww1 = 0; ww1 < Indices.size(); ww1++) {
			//	cout << Indices[ww1].new_index << "---" << Indices[ww1].old_index << endl;
			//}

			/*for (vector<gate>::size_type yy1 = 0; yy1 < circuit_gates.size(); yy1++) {
				for (vector<wire>::size_type yy2 = 0; yy2 < circuit_gates[yy1].inputs.size(); yy2++) {
					if (circuit_gates[yy1].inputs[yy2].w_func.size() != 0) {
						for(deque<string>::size_type yy3 = 0; yy3 < circuit_gates[yy1].inputs[yy2].w_func.size(); yy3++) {
							cout << circuit_gates[yy1].inputs[yy2].w_func[yy3];
						}
						cout << "   ";
					}
					else cout << "prob" << "   ";
				}
				cout << endl;
			}*/

			//cout << "Gates:" << '\n';
			//for (unsigned long int yx = 0; yx < circuit_gates.size(); yx++) {
			//	cout << circuit_gates[yx].g_name << '\n';
			//}

			// *************************

			return 0;

		}
