/*
 * rand_vec.cpp
 *
 *  Created on: Mar 31, 2014
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
 using namespace std;

int main () {

	const int random_num = 10;

	const int ATPG_num = 8;

	const int pins_num = 5;

	int random_vectors [random_num][pins_num];					// Column = Number of Input Pins ------- Row = Number of Random Vectors

	int ATPG_vectors [ATPG_num][pins_num];							// Column = Number of Input Pins ------- Row = Number of ATPG Vectors

	int match = 0;

	int repeat = 0;

	 srand (time(NULL));

	ifstream fp ("input_file.txt");

	if (fp.is_open()) {
		while ( !fp.eof() ) {
			for (int zz = 0; zz < ATPG_num; zz++) {
				for (int rr = 0; rr < pins_num; rr++) {
					fp >> ATPG_vectors [zz][rr];}}
		}
	}



		for (int i = 0; i < random_num; i++) {

			for (int j = 0; j < pins_num; j++) {

				random_vectors [i][j] = rand() % 2;

			}

			for (int vv = 0; vv < ATPG_num; vv++) {
				match = 0;
				for (int mm = 0; mm < pins_num; mm++) {
					if (random_vectors[i][mm] == ATPG_vectors[vv][mm]) {
						match++;
					}
				}
				if (match == pins_num) {
					i--;
					break;
				}
			}

			for (int ww = 0; ww < i; ww++) {
				repeat = 0;
				for (int ee = 0; ee < pins_num; ee++) {
					if (random_vectors[i][ee] == random_vectors[ww][ee]) {
						repeat++;
					}
				}
				if (repeat == pins_num) {
					i--;
					break;
				}
			}
		}



		for (int ii = 0; ii < random_num; ii++) {

			//cout << "Random Test Vector " << ii << ": ";

			for (int jj = 0; jj < pins_num; jj++) {

				cout << random_vectors [ii][jj];

			}

				cout << '\n';

		}


		cout << '\n' << '\n';


		for (int j = 0; j < ATPG_num; j++) {

					cout << "ATPG Vector " << j << ": ";

					for (int i = 0; i < pins_num; i++) {

						cout << ATPG_vectors [j][i] << ' ';

					}

						cout << '\n';

				}

	return 0;
}
