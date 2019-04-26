/*
 * gfg.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: shayantaheri
 */

/*
 * gates.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: shayantaheri
 */

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

int main()
{

			vector <string> gates;
			unsigned long long int i = 0, name = 0;
			string temp_line;
			string ginit = "0";
			string::size_type gx;
			int cont = 0;
			int repeat = 0;


			// Reading the input file and assigning its content to the equivalent arrays :

			ifstream fp ("input_file.txt");
			if (fp.is_open())
			{
				while (getline (fp, temp_line))
				{

					gates.push_back(ginit);
					gx = 0;
					cont = 0;
					for (gx = 0; temp_line[gx] != '(';) {
						gx++;
						if (gx >= 60) {
							cont = 1;
							break;
						}
					}

					if (cont != 0) {
						gates.pop_back();
						continue;
					}

					gx++;
					name = 0;
					for (; temp_line[gx] != ')'; gx++) {
						if (name >= 1) {
							gates[i].push_back(temp_line[gx]);}
						else gates[i] = temp_line[gx];
						name++;
					}

					//repeat = 0;
					//for (unsigned long long int ww = 0; ww < i; ww++) {
					//	if (gates[i] == gates[ww]) {
					//		repeat++;
					//	}
					//}
					//if (repeat != 0) {
					//	i--;
					//	gates.pop_back();
					//}

					if (gates[i] == "in" || gates[i] == "out" || gates[i] == "FU0" || (gates[i][0] == 'C' && gates[i][1] == 'o' && gates[i][2] == 'm' && gates[i][3] == 'p')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'C' && gates[i][1] == 't' && gates[i][2] == 'r' && gates[i][3] == 'l') || (gates[i][0] == 'B' && gates[i][1] == 'T' && gates[i][2] == 'B')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'D' && gates[i][1] == 'e' && gates[i][2] == 'c' && gates[i][3] == 'o') || (gates[i][0] == 'A' && gates[i][1] == 'c' && gates[i][2] == 't' && gates[i][3] == 'i')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'P' && gates[i][1] == 'r' && gates[i][2] == 'e' && gates[i][3] == 'D')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'A' && gates[i][1] == 'G' && gates[i][2] == 'E' && gates[i][3] == 'N')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'S' && gates[i][1] == 'i' && gates[i][2] == 'm' && gates[i][3] == 'p')) {
						i--;
						gates.pop_back();
					}

					else if ((gates[i][0] == 'S' && gates[i][1] == 'i' && gates[i][2] == 'm' && gates[i][3] == 'p')) {
						i--;
						gates.pop_back();
						}

					i++;

			}
		}



			cout << "Gates on Critical Path:" << '\n' << '\n';
			for (unsigned long int yx = 0; yx < gates.size(); yx++) {
					cout << gates[yx] << '\n';
			}



			return 0;


}







