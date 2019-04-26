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


 class pathi {
 public:
 	string path;
 	string delay;
 };

int main()
{

			vector <pathi> paths;
			unsigned long long int i = 0, name = 0;
			string temp_line;
			pathi pinit;
			pinit.path = "0";
			pinit.delay = "0";
			string::size_type gx;


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


					i++;

			}
		}



			cout << "Paths and Delays:" << '\n' << '\n';
			for (unsigned long int yx = 0; yx < paths.size(); yx++) {
					cout << paths[yx].path << '\t' << '\t' << '\t' << '\t';
					cout << paths[yx].delay << '\n';
			}



			return 0;


}

