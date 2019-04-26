/*
 * jcs.cpp
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

int main()
	{

			vector <gate> gates;												// All of the Gates in the Circuit.
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


			// ******************* Reading the Input File and Building Gates , Inputs , and Outputs containers **********************


			ifstream fp ("input_file.txt");
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

			for (vector<gate>::size_type uu1 = 0; uu1 < gates.size(); uu1++) {
				for (vector<wire>::size_type uu2 = 0; uu2 < gates[uu1].inputs.size(); uu2++) {
					gates[uu1].inputs[uu2].w_func.push_back(gates[uu1].inputs[uu2].w_name);
					gates[uu1].inputs[uu2].w_func.push_back("-");
					gates[uu1].inputs[uu2].w_func.push_back("*");
					gates[uu1].inputs[uu2].w_func.push_back("ONE");
					gates[uu1].inputs[uu2].w_func.push_back("-");
					gates[uu1].inputs[uu2].w_func.push_back("#");
					gates[uu1].inputs[uu2].w_func.push_back("-");
				}
			}

			// **********************************************************************************************************






			// *** Testing the Code ***

			/*cout << "INPUTS Functionality:" << endl << gates.size() << endl;

			for (vector<gate>::size_type yy1 = 0; yy1 < gates.size(); yy1++) {
				for (vector<wire>::size_type yy2 = 0; yy2 < gates[yy1].inputs.size(); yy2++) {
					for(deque<string>::size_type yy3 = 0; yy3 < gates[yy1].inputs[yy2].w_func.size(); yy3++) {
						cout << gates[yy1].inputs[yy2].w_func[yy3];
					}
					cout << "   ";
				}
				cout << endl;
			}*/

			cout << "Gates:" << '\n';
			for (unsigned long int yx = 0; yx < gates.size(); yx++) {
				cout << gates[yx].g_name << '\n';
			}

			// *************************

			return 0;

		}
