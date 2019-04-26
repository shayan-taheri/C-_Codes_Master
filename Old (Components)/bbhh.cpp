/*
 * bbhh.cpp
 *
 *  Created on: Mar 12, 2014
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

 class comp_gates
 {
 	public:
 		void XOR2 (bool& IN1, bool& IN2, bool& OUT);

 	private:
 		void AND_Base (bool& A, bool& B, bool& C);
 		void OR_Base (bool& A, bool& B, bool& C);
 };

 void comp_gates::AND_Base(bool& A, bool& B, bool& C) {
 	C = A & B;
 }

 void comp_gates::OR_Base(bool& A, bool& B, bool& C) {
 	C = A | B;
 }

 void comp_gates::XOR2(bool& IN1, bool& IN2, bool& OUT) {
 	bool temp_IN1 = !IN1;
 	bool temp_IN2 = !IN2;
 	bool o1, o2;
 	AND_Base(temp_IN1, IN2, o1);
 	AND_Base(IN1, temp_IN2, o2);
 	OR_Base(o1, o2, OUT);
 }

int main()
{

	comp_gates object;
	bool x = 0, y = 0;
	bool z;
	object.XOR2(x, y, z);

	cout << z;


	return 0;

}




