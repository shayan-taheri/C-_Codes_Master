/*
 * kjhd.cpp
 *
 *  Created on: Apr 19, 2014
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

int main()
{

			vector <string> gates;
			string temp_line;
			string temp_gate;
			bool old_gate;
			string::size_type iter = 0;

			ifstream fp ("input_file.txt");
			if (fp.is_open())
			{
				while (getline (fp, temp_line))
				{

					old_gate = false;

					iter = 0;

					temp_gate.clear();

					for (; temp_line[iter] != '	'; iter++) {
						temp_gate.push_back(temp_line[iter]);
					}

					if (gates.size() == 0) {
						gates.push_back(temp_gate);
					}

					for (vector<string>::size_type i = 0; i < gates.size(); i++) {
						if (temp_gate == gates[i]) {
						old_gate = true;
						break;
						}
					}

					if (old_gate == false) {
						gates.push_back(temp_gate);
					}

				}
			}


			cout << "Reduced Gates:" << '\n';
			for (unsigned long int yx = 0; yx < gates.size(); yx++) {
					cout << gates[yx] << '\n';
			}

			return 0;

}




