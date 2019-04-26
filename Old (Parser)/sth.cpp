/*
 * sth.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: shayantaheri
 */

 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 #include <vector>
 using namespace std;


 class wire {
 public:
 	string w_name;
 	bool value;
 	vector<double> cont_val;};

 class gate {
 public:
 	string g_name;
 	vector <wire> inputs;
 	vector <wire> outputs;};

int main()
	{

			vector <gate> gates;
			unsigned long long int i = 0, j = 0, k = 0, name = 0, senc = 0, inp = 0, oup = 0;
			string temp_line;
			wire winit;
			gate ginit;
			winit.w_name = "0";
			winit.cont_val.push_back(0);
			ginit.g_name = "0";
			ginit.inputs.push_back(winit);
			ginit.outputs.push_back(winit);
			string::size_type gx, kx;


			// Reading the input file and assigning its content to the equivalent arrays :

			ifstream fp ("input_file.txt");
			if (fp.is_open())
			{
				while (getline (fp, temp_line))
				{

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

					i++;
				}
			}



			cout << "INPUTS:" << '\n';
			for (unsigned long int yx = 0; yx < gates.size(); yx++)
			for (unsigned long int yw = 0; yw < gates[0].inputs.size(); yw++) {
							cout << gates[yx].inputs[yw].w_name << '\n';
						}

			//cout << "Gates:" << '\n';
			//for (unsigned long int yx = 0; yx < gates.size(); yx++) {
				//			cout << gates[yx].g_name << '\n';
					//	}



			return 0;

		}


