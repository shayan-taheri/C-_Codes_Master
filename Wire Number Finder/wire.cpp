/*
 * wire.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: shayantaheri
 */

 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <vector>
 #include <sstream>
 using namespace std;

 int main () {

 vector <int> wire_vectors;
 string temp_line;
 int temp_int = 0;
 int exc = 0;
 stringstream stream;

 ifstream fp ("input_file.txt");

 if (fp.is_open()) {
	 	 while ( getline (fp, temp_line) ) {
	 			stream << temp_line;
	 			stream >> temp_int;
	 			exc = 0;
	 			for (vector<int>::size_type j = 0; j < wire_vectors.size(); j++) {
	 				if (wire_vectors[j] == temp_int) {
	 									exc++;
	 				}
	 			}
	 			if (exc == 0) {
	 				wire_vectors.push_back(temp_int);}
	 			stream.str("");
	 			stream.clear();
 		}

 	}

 for (vector<int>::size_type i = 0; i < wire_vectors.size(); i++) {

 	cout << "N" << wire_vectors[i] << ", ";}

 return 0;

 }
