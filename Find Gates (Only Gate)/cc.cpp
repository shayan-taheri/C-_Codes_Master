/*
 * cc.cpp
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




int main()
{

			vector <string> gates;
			string temp_line;
			bool old_gate;

			ifstream fp ("input_file.txt");
			if (fp.is_open())
			{
				while (getline (fp, temp_line))
				{

					old_gate = false;

					if (gates.size() == 0) {
						gates.push_back(temp_line);
					}

					for (vector<string>::size_type i = 0; i < gates.size(); i++) {
						if (temp_line == gates[i]) {
						old_gate = true;
						break;
						}
					}

					if (old_gate == false) {
						gates.push_back(temp_line);
					}

				}
			}


			cout << "Reduced Gates:" << '\n';
			for (unsigned long int yx = 0; yx < gates.size(); yx++) {
							cout << gates[yx] << '\n';
						}



			return 0;

}








