/*
 * dx.cpp
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

 class wire {
 public:
 	string w_name;
 	bool value;
 	vector<double> cont_val;
 	deque<string> w_func;};

 class gate {
 public:
 	string g_name;
 	vector <wire> inputs;
 	vector <wire> outputs;};



 // ********************* GATES and COMPONENTS **********************

 class comp_gates
 {
 	public:
	 	static void AND2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void OR2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void INV (wire& IN, wire& OUT);
	 	static void XOR2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void AND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void AND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT);
	 	static void OR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void OR4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT);
	 	static void NAND2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void NAND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void NAND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT);
	 	static void NOR2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void NOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void XOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void XNOR2 (wire& IN1, wire& IN2, wire& OUT);
	 	static void XNOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT);
	 	static void AO21 (wire& X1, wire& X2, wire& Y, wire& OUT);
	 	static void AO22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT);
	 	static void AO221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT);
	 	static void AO222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT);
	 	static void AOI21 (wire& X1, wire& X2, wire& Y, wire& OUT);
	 	static void AOI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT);
	 	static void AOI221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT);
	 	static void AOI222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT);
	 	static void OA21 (wire& X1, wire& X2, wire& Y, wire& OUT);
	 	static void OA22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT);
	 	static void OA221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT);
	 	static void OA222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT);
	 	static void OAI21 (wire& X1, wire& X2, wire& Y, wire& OUT);
	 	static void OAI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT);
	 	static void BUFF (wire& IN, wire& OUT);
	 	static void MUX21 (wire& X, wire& Y, wire& S, wire& OUT);
	 	static void DFFN (wire& CLK, wire& D, wire& OUT);
	 	static void SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q);
	 	static void SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q, wire& QN);
	 	static void LSDNEN (wire& D, wire& ENB, wire& OUT);
	 	static void ISOLAND (wire& D, wire& ISO, wire& OUT);



 	private:
 		static void AND_Base (wire& A, wire& B, wire& C);
 		static void OR_Base (wire& A, wire& B, wire& C);
 		static void NOT_Base (wire& I, wire& Z);
 };

 // *****************************************************************


 // ************************** Implementation of Gates and Components *********************************

 void comp_gates::AND_Base (wire& A, wire& B, wire& C) {


	// ****** Calculating the Value of "C" --> C.value ******

	C.value = A.value & B.value;

	// *********************************************************



 	// ****** Making the Functionality of "C" --> C.w_func ******

	for (deque<string>::size_type bb1 = 0; bb1 < A.w_func.size(); bb1++) {
		C.w_func.push_back (A.w_func[bb1]);
	}

	C.w_func.push_back("*");

	for (deque<string>::size_type bb2 = 0; bb2 < B.w_func.size(); bb2++) {
		C.w_func.push_back (B.w_func[bb2]);
	}

	C.w_func.push_back("#");
	C.w_func.push_back("-");

	// **********************************************************

 }

 void comp_gates::OR_Base (wire& A, wire& B, wire& C) {


	// ****** Calculating the Value of "C" --> C.value ******

	C.value = A.value | B.value;

	// ******************************************************



	// ****** Making the Functionality of "C" --> C.w_func ******

 	for (deque<string>::size_type xx1 = 0; xx1 < A.w_func.size(); xx1++) {
 		C.w_func.push_back (A.w_func[xx1]);
 	}

 	C.w_func.push_back("+");

 	for (deque<string>::size_type xx2 = 0; xx2 < B.w_func.size(); xx2++) {
 		C.w_func.push_back (B.w_func[xx2]);
 	}

 	C.w_func.push_back("#");
 	C.w_func.push_back("-");

 	// **********************************************************

 }

 void comp_gates::NOT_Base (wire& I, wire& Z) {


	// ****** Calculating the Value of "Z" --> Z.value ******

	Z.value = !I.value;

	// ******************************************************



	// ****** Making the Functionality of "Z" --> Z.w_func ******

	Z.w_func = I.w_func;

	if (Z.w_func[Z.w_func.size()-1] == "-") {
		Z.w_func[Z.w_func.size()-1] = "!";
	}
	else if (Z.w_func[Z.w_func.size()-1] == "!") {
		Z.w_func[Z.w_func.size()-1] = "-";
	}

	// ***********************************************************

 }

 void comp_gates::AND2(wire& IN1, wire& IN2, wire& OUT) {
	 AND_Base (IN1, IN2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OR2(wire& IN1, wire& IN2, wire& OUT) {
	 OR_Base (IN1, IN2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::INV (wire& IN, wire& OUT) {
	 NOT_Base (IN, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::XOR2(wire& IN1, wire& IN2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini;
	NOT_Base (IN1, temp_IN1);
 	NOT_Base (IN2, temp_IN2);
 	wire o1 = w_ini, o2 = w_ini;
 	AND_Base (temp_IN1, IN2, o1);
 	AND_Base (IN1, temp_IN2, o2);
 	OR_Base (o1, o2, OUT);
 	// Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 AND_Base (IN1, IN2, o1);
	 AND_Base (o1, IN3, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini , o2 = w_ini;
	 AND_Base (IN1, IN2, o1);
	 AND_Base (IN3, IN4, o2);
	 AND_Base (o1, o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 OR_Base (IN1, IN2, o1);
	 OR_Base (o1, IN3, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OR4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini , o2 = w_ini;
	 OR_Base (IN1, IN2, o1);
	 OR_Base (IN3, IN4, o2);
	 OR_Base (o1, o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::NAND2(wire& IN1, wire& IN2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 AND_Base (IN1, IN2, o1);
	 NOT_Base (o1, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::NAND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 AND_Base (IN1, IN2, o1);
	 AND_Base (o1, IN3, o2);
	 NOT_Base (o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::NAND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini , o2 = w_ini, o3 = w_ini;
	 AND_Base (IN1, IN2, o1);
	 AND_Base (IN3, IN4, o2);
	 AND_Base (o1, o2, o3);
	 NOT_Base (o3, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::NOR2(wire& IN1, wire& IN2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 OR_Base (IN1, IN2, o1);
	 NOT_Base (o1, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::NOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 OR_Base (IN1, IN2, o1);
	 OR_Base (o1, IN3, o2);
	 NOT_Base (o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::XOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini, temp_IN3 = w_ini, temp_o3 = w_ini;
	NOT_Base (IN1, temp_IN1);
 	NOT_Base (IN2, temp_IN2);
 	NOT_Base (IN3, temp_IN3);
 	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini;
 	AND_Base (temp_IN1, IN2, o1);
 	AND_Base (IN1, temp_IN2, o2);
 	OR_Base (o1, o2, o3);
 	NOT_Base (o3, temp_o3);
 	AND_Base (temp_o3, IN3, o4);
 	AND_Base (o3, temp_IN3, o5);
 	OR_Base (o4, o5, OUT);
 	// Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::XNOR2(wire& IN1, wire& IN2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini;
	NOT_Base (IN1, temp_IN1);
 	NOT_Base (IN2, temp_IN2);
 	wire o1 = w_ini, o2 = w_ini;
 	AND_Base (IN1, IN2, o1);
 	AND_Base (temp_IN1, temp_IN2, o2);
 	OR_Base (o1, o2, OUT);
 	// Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::XNOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini, temp_IN3 = w_ini, temp_o3 = w_ini;
	NOT_Base (IN1, temp_IN1);
 	NOT_Base (IN2, temp_IN2);
 	NOT_Base (IN3, temp_IN3);
 	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini;
 	AND_Base (temp_IN1, IN2, o1);
 	AND_Base (IN1, temp_IN2, o2);
 	OR_Base (o1, o2, o3);
 	NOT_Base (o3, temp_o3);
 	AND_Base (o3, IN3, o4);
 	AND_Base (temp_o3, temp_IN3, o5);
 	OR_Base (o4, o5, OUT);
 	// Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AO21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 AND_Base (X1, X2, o1);
	 OR_Base (o1, Y, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AO22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 OR_Base (o1, o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AO221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 OR_Base (o1, o2, o3);
	 OR_Base (o3, K, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AO222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 AND_Base (K1, K2, o3);
	 OR_Base (o1, o2, o4);
	 OR_Base (o3, o4, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AOI21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 AND_Base (X1, X2, o1);
	 OR_Base (o1, Y, o2);
	 NOT_Base (o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AOI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 OR_Base (o1, o2, o3);
	 NOT_Base (o3, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AOI221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 OR_Base (o1, o2, o3);
	 OR_Base (o3, K, o4);
	 NOT_Base (o4, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::AOI222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini;
	 AND_Base (X1, X2, o1);
	 AND_Base (Y1, Y2, o2);
	 AND_Base (K1, K2, o3);
	 OR_Base (o1, o2, o4);
	 OR_Base (o3, o4, o5);
	 NOT_Base (o5, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OA21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini;
	 OR_Base (X1, X2, o1);
	 AND_Base (o1, Y, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OA22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 OR_Base (X1, X2, o1);
	 OR_Base (Y1, Y2, o2);
	 AND_Base (o1, o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OA221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
	 OR_Base (X1, X2, o1);
	 OR_Base (Y1, Y2, o2);
	 AND_Base (o1, o2, o3);
	 AND_Base (o3, K, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OA222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini;
	 OR_Base (X1, X2, o1);
	 OR_Base (Y1, Y2, o2);
	 OR_Base (K1, K2, o3);
	 AND_Base (o1, o2, o4);
	 AND_Base (o3, o4, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OAI21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini;
	 OR_Base (X1, X2, o1);
	 AND_Base (o1, Y, o2);
	 NOT_Base (o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::OAI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
	 OR_Base (X1, X2, o1);
	 OR_Base (Y1, Y2, o2);
	 AND_Base (o1, o2, o3);
	 NOT_Base (o3, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::BUFF (wire& IN, wire& OUT) {
	 OUT.value = IN.value;
	 OUT.w_func = IN.w_func;
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::MUX21 (wire& X, wire& Y, wire& S, wire& OUT) {
	 wire w_ini;
	 w_ini.value = 0;
	 wire o1 = w_ini, o2 = w_ini, S_not = w_ini;
	 NOT_Base (S, S_not);
	 AND_Base (X, S_not, o1);
	 AND_Base (Y, S, o2);
	 OR_Base (o1, o2, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::DFFN (wire& CLK, wire& D, wire& OUT) {
 	 wire w_ini;
 	 w_ini.value = 0;
 	 wire o1 = w_ini, o2 = w_ini, CLK_not = w_ini;
 	 NOT_Base (CLK, CLK_not);
 	 AND_Base (D, CLK_not, o1);
 	 AND_Base (OUT, CLK, o2);
 	 OR_Base (o1, o2, OUT);
 	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
  }

 void comp_gates::SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q) {
 	 wire w_ini;
 	 w_ini.value = 0;
 	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini, CLK_not = w_ini;
 	 NOT_Base (CLK, CLK_not);
 	 AND_Base (SI, SE, o1);
 	 NOT_Base (SE, o2);
 	 AND_Base (D, o2, o3);
 	 OR_Base (o1, o3, o4);
	 AND_Base (o4, CLK_not, o5);
 	 AND_Base (Q, CLK, o6);
 	 OR_Base (o5, o6, Q);
 	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
  }

 void comp_gates::SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q, wire& QN) {
 	 wire w_ini;
 	 w_ini.value = 0;
 	 wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini, CLK_not = w_ini;
 	 NOT_Base (CLK, CLK_not);
 	 AND_Base (SI, SE, o1);
 	 NOT_Base (SE, o2);
 	 AND_Base (D, o2, o3);
 	 OR_Base (o1, o3, o4);
 	 AND_Base (o4, CLK_not, o5);
 	 AND_Base (Q, CLK, o6);
 	 OR_Base (o5, o6, Q);
 	 NOT_Base (Q, QN);
 	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
  }

 void comp_gates::LSDNEN (wire& D, wire& ENB, wire& OUT) {
	 OR_Base (D, ENB, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 void comp_gates::ISOLAND (wire& D, wire& ISO, wire& OUT) {
	 AND_Base (D, ISO, OUT);
	 // Calling the Encoder to Get Control Values for "OUT.cont_val"
 }

 // ***********************************************************************************************************



int main()
{

	wire x , y , z , out;
	x.value = 1;
	x.w_func.push_back("x");
	x.w_func.push_back("-");
	y.value = 0;
	y.w_func.push_back("y");
	y.w_func.push_back("-");
	z.value = 1;
	z.w_func.push_back("z");
	z.w_func.push_back("-");
	comp_gates::XOR3(x,y,z,out);

	for (deque<string>::size_type jj1 = 0; jj1 < out.w_func.size(); jj1++) {
		cout << out.w_func[jj1];
	}

	/*y.w_func.push_back("-");
	y.w_func.push_back("*");
	y.w_func.push_back("ONE");
	y.w_func.push_back("-");
	y.w_func.push_back("#");
	y.w_func.push_back("-");*/

	return 0;

}




