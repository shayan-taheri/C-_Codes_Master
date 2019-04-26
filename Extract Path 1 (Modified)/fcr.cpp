/*
 * fcr.cpp
 *
 *  Created on: Apr 14, 2014
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


 class pathi {
 public:
 	string path;
 	string delay;
 	string gate;
 };

int main()
{

			vector <pathi> paths;
			unsigned long long int i = 0, name = 0, nact = 0;
			string temp_line;
			pathi pinit;
			pinit.path = "0";
			pinit.delay = "0";
			pinit.gate = "0";
			string::size_type gx, kx;
			string::iterator itrx;
			string::size_type mm = 0;
			int cont = 0;
			int evac = 0;


			// Reading the input file and assigning its content to the equivalent arrays :

			ifstream fp ("input_file.txt");
			if (fp.is_open())
			{
				while (getline (fp, temp_line))
				{

					paths.push_back(pinit);
					gx = 0;
					for (gx = 0; temp_line[gx] == ' ';) {
						gx++;}

					name = 0;
					for (; temp_line[gx] != ' '; gx++) {
						if (name >= 1) {
							paths[i].path.push_back(temp_line[gx]);}
						else paths[i].path = temp_line[gx];
						name++;
					}

					mm = paths[i].path.size() - 1;
					while (paths[i].path[mm] != '/') {
						itrx = paths[i].path.end();
						itrx--;
						paths[i].path.erase(itrx);
						mm = paths[i].path.size() - 1;
					}

					for (; temp_line[gx] == ' ';) {
						gx++;}

					for (; temp_line[gx] != ' ';) {
						gx++;}

					for (; temp_line[gx] == ' ';) {
						gx++;}

					name = 0;
					for (; temp_line[gx] != ' '; gx++) {
						if (name >= 1) {
							paths[i].delay.push_back(temp_line[gx]);}
						else paths[i].delay = temp_line[gx];
						name++;
					}

					kx = 0;
					cont = 0;
					for (kx = 0; temp_line[kx] != '(';) {
					    kx++;
					}

					kx++;
					nact = 0;
					for (; temp_line[kx] != ')'; kx++) {
					    if (nact >= 1) {
					        paths[i].gate.push_back(temp_line[kx]);}
					    else paths[i].gate = temp_line[kx];
					        nact++;
					}

					evac = 0;
					if ((i > 0) && (paths[i].gate == paths[i-1].gate) && (paths[i].path == paths[i-1].path)) {
						paths[i-1].delay = paths[i-1].delay + " + " + paths[i].delay;
						evac = 1;
					}

					else if (paths[i].gate == "FU0" || (paths[i].gate[0] == 'C' && paths[i].gate[1] == 'o' && paths[i].gate[2] == 'm' && paths[i].gate[3] == 'p')) {
						evac = 1;
					}

					else if ((paths[i].gate[0] == 'C' && paths[i].gate[1] == 't' && paths[i].gate[2] == 'r' && paths[i].gate[3] == 'l') || (paths[i].gate[0] == 'B' && paths[i].gate[1] == 'T' && paths[i].gate[2] == 'B')) {
						evac = 1;
					}

					else if ((paths[i].gate[0] == 'D' && paths[i].gate[1] == 'e' && paths[i].gate[2] == 'c' && paths[i].gate[3] == 'o') || (paths[i].gate[0] == 'A' && paths[i].gate[1] == 'c' && paths[i].gate[2] == 't' && paths[i].gate[3] == 'i')) {
						evac = 1;
					}

					else if ((paths[i].gate[0] == 'P' && paths[i].gate[1] == 'r' && paths[i].gate[2] == 'e' && paths[i].gate[3] == 'D')) {
						evac = 1;
					}

					else if ((paths[i].gate[0] == 'A' && paths[i].gate[1] == 'G' && paths[i].gate[2] == 'E' && paths[i].gate[3] == 'N')) {
						evac = 1;
					}

					else if ((paths[i].gate[0] == 'S' && paths[i].gate[1] == 'i' && paths[i].gate[2] == 'm' && paths[i].gate[3] == 'p')) {
						evac = 1;
					}

					if (evac == 1) {
						i--;
						paths.pop_back();
					}

					i++;

			}
		}


			cout << "Gates and Delays:" << '\n' << '\n';
			for (unsigned long int yx = 0; yx < paths.size(); yx++) {
					cout << paths[yx].gate << '\t' << '\t' << '\t' << '\t';
					cout << paths[yx].delay << '\n';
			}

			return 0;


}




