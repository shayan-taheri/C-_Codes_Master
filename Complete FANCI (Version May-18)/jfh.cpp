/*
 * jfh.cpp
 *
 *  Created on: May 14, 2014
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
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class wire {											// Class (Type) for Wires
public:
 	string w_name;										// Name of Wire
 	bool value;											// Value of Wire
 	vector<double> cont_val;							// Control Values of Wire
 	deque<string> w_func;};								// Functionality of Wire


class gate {											// Class (Type) for Gates
public:
 	string g_name;										// Name of Gate
 	vector <wire> inputs;								// Inputs of Gate
 	vector <wire> outputs;};							// Outputs of Gate


class index_type {										// Class (Type) for Obtaining Sort Indices
public:
    vector<gate>::size_type old_index;					// Old Index
    vector<gate>::size_type new_index;					// New Index
};


class func_in {						// Class for the inputs of the function.
public:
    string in_name;					// Input Name
    bool in_val;					// Input Value
};


class split {							// Class for the splitter which places the function of each 2-Input gate in a section.
public:
    deque<string> sect;					// The function of 2-Input gate = A section.
    string sign;						// The sign for the section.
    bool value;							// The result of each section "with considering the Sign".
};


class oprt_type {						// Class for major operators of the whole function.
public:
    string oprt;						// Major operator
    string sign;						// Associated sign with major operator.
};


class controls_type {		// Class (Type) for final control value of the output wires (based on the condition, average, median, or ...)
public:
	string wire_name;		// Wire Name
	double final_cont;		// Final Control Value
};


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
    static void NOR4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT);
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

	// ****** Providing the control values of "Z" --> Z.cont_val ******

	Z.cont_val = I.cont_val;

	// ****************************************************************


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

// ***********************************************************************************************************

// ************************** Formatting Gates and Components Based on "Min-Term" (Term1 + Term2 + ...) *********************************

// HINT: First Implementing AND Gates (and NOTs), then Implementing OR Gates.

void comp_gates::AND2(wire& IN1, wire& IN2, wire& OUT) {
    AND_Base (IN1, IN2, OUT);

}

void comp_gates::OR2(wire& IN1, wire& IN2, wire& OUT) {
    OR_Base (IN1, IN2, OUT);

}

void comp_gates::INV (wire& IN, wire& OUT) {
    NOT_Base (IN, OUT);

}

void comp_gates::XOR2(wire& IN1, wire& IN2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini;
	NOT_Base (IN1, temp_IN1);
 	NOT_Base (IN2, temp_IN2);
 	wire o1 = w_ini, o2 = w_ini;
 	AND_Base (IN1, temp_IN2, o1);
 	AND_Base (temp_IN1, IN2, o2);
 	OR_Base (o1, o2, OUT);

}

void comp_gates::AND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini;
    AND_Base (IN1, IN2, o1);
    AND_Base (o1, IN3, OUT);

}

void comp_gates::AND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini , o2 = w_ini;
    AND_Base (IN1, IN2, o1);
    AND_Base (IN3, IN4, o2);
    AND_Base (o1, o2, OUT);

}

void comp_gates::OR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini;
    OR_Base (IN1, IN2, o1);
    OR_Base (o1, IN3, OUT);

}

void comp_gates::OR4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini , o2 = w_ini;
    OR_Base (IN1, IN2, o1);
    OR_Base (IN3, IN4, o2);
    OR_Base (o1, o2, OUT);

}

void comp_gates::NAND2(wire& IN1, wire& IN2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini;
    AND_Base (IN1, IN2, o1);
    NOT_Base (o1, OUT);

}

void comp_gates::NAND3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    AND_Base (IN1, IN2, o1);
    AND_Base (o1, IN3, o2);
    NOT_Base (o2, OUT);

}

void comp_gates::NAND4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini , o2 = w_ini, o3 = w_ini;
    AND_Base (IN1, IN2, o1);
    AND_Base (IN3, IN4, o2);
    AND_Base (o1, o2, o3);
    NOT_Base (o3, OUT);

}

void comp_gates::NOR2(wire& IN1, wire& IN2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini;
    OR_Base (IN1, IN2, o1);
    NOT_Base (o1, OUT);

}

void comp_gates::NOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    OR_Base (IN1, IN2, o1);
    OR_Base (o1, IN3, o2);
    NOT_Base (o2, OUT);

}

void comp_gates::NOR4 (wire& IN1, wire& IN2, wire& IN3, wire& IN4, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini , o2 = w_ini, o3 = w_ini;
    OR_Base (IN1, IN2, o1);
    OR_Base (IN3, IN4, o2);
    OR_Base (o1, o2, o3);
    NOT_Base (o3, OUT);

}

void comp_gates::XOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini, temp_IN3 = w_ini, temp_o3 = w_ini;
	NOT_Base (IN1, temp_IN1);
	NOT_Base (IN2, temp_IN2);
	NOT_Base (IN3, temp_IN3);
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	wire o7 = w_ini, o8 = w_ini, o9 = w_ini, o10 = w_ini;
	AND_Base (IN1, IN2, o1);
	AND_Base (o1, IN3, o2);
	AND_Base (IN1, temp_IN2, o3);
	AND_Base (o3, temp_IN3, o4);
	AND_Base (temp_IN1, IN2, o5);
	AND_Base (o5, temp_IN3, o6);
	AND_Base (temp_IN1, temp_IN2, o7);
	AND_Base (o7, IN3, o8);
	OR_Base (o2, o4, o9);
	OR_Base (o6, o8, o10);
	OR_Base (o9, o10, OUT);

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

}

void comp_gates::XNOR3 (wire& IN1, wire& IN2, wire& IN3, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire temp_IN1 = w_ini, temp_IN2 = w_ini, temp_IN3 = w_ini, temp_o3 = w_ini;
	NOT_Base (IN1, temp_IN1);
	NOT_Base (IN2, temp_IN2);
	NOT_Base (IN3, temp_IN3);
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	wire o7 = w_ini, o8 = w_ini, o9 = w_ini, o10 = w_ini, o11 = w_ini;
	AND_Base (IN1, IN2, o1);
	AND_Base (o1, IN3, o2);
	AND_Base (IN1, temp_IN2, o3);
	AND_Base (o3, temp_IN3, o4);
	AND_Base (temp_IN1, IN2, o5);
	AND_Base (o5, temp_IN3, o6);
	AND_Base (temp_IN1, temp_IN2, o7);
	AND_Base (o7, IN3, o8);
	OR_Base (o2, o4, o9);
	OR_Base (o6, o8, o10);
	OR_Base (o9, o10, o11);
	NOT_Base (o11, OUT);

}

void comp_gates::AO21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini;
    AND_Base (X1, X2, o1);
    OR_Base (o1, Y, OUT);

}

void comp_gates::AO22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    AND_Base (X1, X2, o1);
    AND_Base (Y1, Y2, o2);
    OR_Base (o1, o2, OUT);

}

void comp_gates::AO221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
    AND_Base (X1, X2, o1);
    AND_Base (Y1, Y2, o2);
    OR_Base (o1, o2, o3);
    OR_Base (o3, K, OUT);

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

}

void comp_gates::AOI21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    AND_Base (X1, X2, o1);
    OR_Base (o1, Y, o2);
    NOT_Base (o2, OUT);

}

void comp_gates::AOI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
    AND_Base (X1, X2, o1);
    AND_Base (Y1, Y2, o2);
    OR_Base (o1, o2, o3);
    NOT_Base (o3, OUT);

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

}

void comp_gates::OA21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini;
	AND_Base (X1, Y, o1);
	AND_Base (X2, Y, o2);
	OR_Base (o1, o2, OUT);

}

void comp_gates::OA22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	AND_Base (X1, Y1, o1);
	AND_Base (X1, Y2, o2);
	AND_Base (X2, Y1, o3);
	AND_Base (X2, Y2, o4);
	OR_Base (o1, o2, o5);
	OR_Base (o3, o4, o6);
	OR_Base (o5, o6, OUT);

}

void comp_gates::OA221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	wire o7 = w_ini, o8 = w_ini, o9 = w_ini, o10 = w_ini;
	AND_Base (X1, Y1, o1);
	AND_Base (o1, K, o2);
	AND_Base (X1, Y2, o3);
	AND_Base (o3, K, o4);
	AND_Base (X2, Y1, o5);
	AND_Base (o5, K, o6);
	AND_Base (X2, Y2, o7);
	AND_Base (o7, K, o8);
	OR_Base (o2, o4, o9);
	OR_Base (o6, o8, o10);
	OR_Base (o9, o10, OUT);

}

void comp_gates::OA222 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K1, wire& K2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini, o7 = w_ini, o8 = w_ini, o9 = w_ini;
	wire o10 = w_ini, o11 = w_ini, o12 = w_ini, o13 = w_ini, o14 = w_ini, o15 = w_ini, o16 = w_ini, o17 = w_ini, o18 = w_ini;
	wire o19 = w_ini, o20 = w_ini, o21 = w_ini, o22 = w_ini;
	AND_Base (X1, Y1, o1);
	AND_Base (o1, K1, o2);
	AND_Base (X1, Y1, o3);
	AND_Base (o3, K2, o4);
	AND_Base (X1, Y2, o5);
	AND_Base (o5, K1, o6);
	AND_Base (X1, Y2, o7);
	AND_Base (o7, K2, o8);
	AND_Base (X2, Y1, o9);
	AND_Base (o9, K1, o10);
	AND_Base (X2, Y1, o11);
	AND_Base (o11, K2, o12);
	AND_Base (X2, Y2, o13);
	AND_Base (o13, K1, o14);
	AND_Base (X2, Y2, o15);
	AND_Base (o15, K2, o16);
	OR_Base (o2, o4, o17);
	OR_Base (o6, o8, o18);
	OR_Base (o10, o12, o19);
	OR_Base (o14, o16, o20);
	OR_Base (o17, o18, o21);
	OR_Base (o19, o20, o22);
	OR_Base (o21, o22, OUT);

}

void comp_gates::OAI21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
	AND_Base (X1, Y, o1);
	AND_Base (X2, Y, o2);
	OR_Base (o1, o2, o3);
	NOT_Base (o3, OUT);

}

void comp_gates::OAI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini, o7 = w_ini;
	AND_Base (X1, Y1, o1);
	AND_Base (X1, Y2, o2);
	AND_Base (X2, Y1, o3);
	AND_Base (X2, Y2, o4);
	OR_Base (o1, o2, o5);
	OR_Base (o3, o4, o6);
	OR_Base (o5, o6, o7);
	NOT_Base (o7, OUT);

}

void comp_gates::BUFF (wire& IN, wire& OUT) {
    OUT.value = IN.value;
    OUT.w_func = IN.w_func;
    OUT.cont_val = IN.cont_val;

}

void comp_gates::MUX21 (wire& X, wire& Y, wire& S, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, S_not = w_ini;
    NOT_Base (S, S_not);
    AND_Base (X, S_not, o1);
    AND_Base (Y, S, o2);
    OR_Base (o1, o2, OUT);

}

void comp_gates::DFFN (wire& CLK, wire& D, wire& OUT) {
	OUT.w_func.clear();
	OUT.w_func.push_back(OUT.w_name);
	OUT.w_func.push_back("-");
	OUT.w_func.push_back("*");
	OUT.w_func.push_back("YEK");
	OUT.w_func.push_back("-");
	OUT.w_func.push_back("#");
	OUT.w_func.push_back("-");
	wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, CLK_not = w_ini;
    NOT_Base (CLK, CLK_not);
    AND_Base (D, CLK_not, o1);
    AND_Base (OUT, CLK, o2);
    OR_Base (o1, o2, OUT);

}

void comp_gates::SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q) {
	Q.w_func.clear();
	Q.w_func.push_back(Q.w_name);
	Q.w_func.push_back("-");
	Q.w_func.push_back("*");
	Q.w_func.push_back("YEK");
	Q.w_func.push_back("-");
	Q.w_func.push_back("#");
	Q.w_func.push_back("-");
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	wire CLK_not = w_ini, SE_not = w_ini;
	NOT_Base (CLK, CLK_not);
	NOT_Base (SE, SE_not);
	AND_Base (D, SE_not, o1);
	AND_Base (o1, CLK_not, o2);
	AND_Base (SI, SE, o3);
	AND_Base (o3, CLK_not, o4);
	AND_Base (Q, CLK, o5);
	OR_Base (o2, o4, o6);
	OR_Base (o5, o6, Q);

}

void comp_gates::SDFF (wire& D, wire& SI, wire& SE, wire& CLK, wire& Q, wire& QN) {
	Q.w_func.clear();
	Q.w_func.push_back(Q.w_name);
	Q.w_func.push_back("-");
	Q.w_func.push_back("*");
	Q.w_func.push_back("YEK");
	Q.w_func.push_back("-");
	Q.w_func.push_back("#");
	Q.w_func.push_back("-");
	wire w_ini;
	w_ini.value = 0;
	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini, o6 = w_ini;
	wire CLK_not = w_ini, SE_not = w_ini;
	NOT_Base (CLK, CLK_not);
	NOT_Base (SE, SE_not);
	AND_Base (D, SE_not, o1);
	AND_Base (o1, CLK_not, o2);
	AND_Base (SI, SE, o3);
	AND_Base (o3, CLK_not, o4);
	AND_Base (Q, CLK, o5);
	OR_Base (o2, o4, o6);
	OR_Base (o5, o6, Q);
	NOT_Base (Q, QN);

}

void comp_gates::LSDNEN (wire& D, wire& ENB, wire& OUT) {
    OR_Base (D, ENB, OUT);

}

void comp_gates::ISOLAND (wire& D, wire& ISO, wire& OUT) {
    AND_Base (D, ISO, OUT);

}

// ***********************************************************************************************************



// ******************* Function for Reading the Input File and Building Gates , Inputs , and Outputs containers **********************

void benchmark_parse (ifstream& fp, vector<gate>& gates) {		// vector <gate> gates: All of the Gates in the Circuit.
    															// ifstream& fp: Input File Stream

    string temp_line;													// Temporary Fetched Line.
    unsigned long long int i = 0, j = 0, k = 0;
    unsigned long long int name = 0, senc = 0, inp = 0, oup = 0;
    wire winit;
    gate ginit;
    winit.w_name = "0";
    winit.value = 0;
    ginit.g_name = "0";
    ginit.inputs.push_back(winit);
    ginit.outputs.push_back(winit);
    string::size_type gx, kx;
    vector <gate>::iterator insert_iter, erase_iter;
    vector<string> outputs_name;
    vector<index_type> Indices;
    vector<gate> temp_gates;
    outputs_name.clear();

    if (fp.is_open())
    {
        while (getline (fp, temp_line))
        {
            // ****** Building Gates (Names) ******

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

            // ************************************

            // ********* Building Inputs **********

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
                    gates[i].inputs[j].cont_val.push_back(1.00);		// Initializing Control Values of Primary Inputs
                    j++;
                }

                if (temp_line[senc] != ';') {senc++;}
            }

            // ************************************

            // ********* Building Outputs *********


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

            // ************************************

            i++;
        }
    }

    // **********************************************************************************************************************

}





// ************ Class of Functions in Encoder ************

class encoder {
public:
    static std::vector<double> control_function (deque<string> FUNCTION);						// Calculating Control Values
private:
    static bool parse_calc (deque<string> function, deque<func_in> func_inputs);				// Parsing and Calculating Function
    static vector<std::vector<unsigned int> > TT_gen (unsigned int n);						// Truth Table Generator
};

// *******************************************************

bool encoder::parse_calc (deque<string> function, deque<func_in> func_inputs) {

    deque<split> splitter;							// For splitting the function based on the result of each 2-input gate.

    splitter.clear();

    deque<split>::size_type split_indx = 0;

    split split_init;

    split_init.sect.clear();

    split_init.sign = "0";

    split_init.value = 0;

    deque<oprt_type> operate;						// Container for major operators (AND or OR) of the function.

    deque<oprt_type> major_oprt;

    operate.clear();

    major_oprt.clear();

    oprt_type oprt_init;

    oprt_init.oprt = "0";

    oprt_init.sign = "0";

    string temp_oprt_signs;							// The signs for major operators.

    temp_oprt_signs.clear();

    deque < deque<bool> > clust_results;						// Container for the result of each section in "Splitter".

    deque<bool> clt_res;

    clust_results.clear();

    bool final_result = 0;

    unsigned long long input_iter = 0;				// Input iterator for the "func_inputs" container.

    bool temp_res = 0;								// Raw result of the "parse_calc" function.

    unsigned long long int mm = 0;					// Index for "splitter" container.

    unsigned long long int pp = 0;					// Index for "operate" container.

    bool add_sect = 0;								// Condition for adding section to "Splitter" container.

    deque < deque<oprt_type> > clust_oprt;

    deque < deque<oprt_type> >::size_type clust_indx = 0;

    deque<oprt_type> clust_init;

    unsigned long long int check_cluster = 0;

    deque<bool> deque_results;

    deque<oprt_type>::size_type oper_indx = 0;

    bool mix_cond = 0;

    deque<bool> clust_finals;


    // *************************** Building the "Splitter" and "Major Operator" containers ********************************


    splitter.clear();
    splitter.push_back(split_init);
    for (deque<string>::size_type ff = 0; ff < function.size(); ff++) {
        if (function[ff] != "#") {
            splitter[mm].sect.push_back(function[ff]);
        }
        else if (function[ff] == "#") {
            if (ff+1 < function.size()) {ff++;}
            splitter[mm].sign = function[ff];
            if (ff+1 < function.size()) {ff++;}
            add_sect = 0;
            for (deque<string>::size_type tt = ff; tt < function.size(); tt++) {
                if (function[tt] == "+" || function[tt] == "*") {
                    add_sect = 1;
                }
            }
            if (add_sect == 1) {
                mm++;
                splitter.push_back(split_init);
            }
            while (function[ff] == "#") {
                if (ff+1 < function.size()) {ff++;}
                temp_oprt_signs += function[ff];
                if (ff+1 < function.size()) {ff++;}
            }
            if (function[ff] == "*" || function[ff] == "+") {
                operate.push_back(oprt_init);
                operate[pp].oprt = function[ff];
                pp++;
            }
        }
    }

    for (deque<oprt_type>::size_type ss = 0; ss < operate.size(); ss++) {
        operate[ss].sign = temp_oprt_signs[ss];
    }

    mix_cond = 0;
    for (deque<oprt_type>::size_type mix1 = 0; mix1 < operate.size(); mix1++) {
    	if (operate[mix1].oprt == "*") {
    		mix_cond = 1;
    		break;
    	}
    }

    if (mix_cond == 1) {
    	clust_oprt.clear();
    	clust_indx = 0;
    	clust_oprt.push_back(clust_init);
    	major_oprt.clear();
    	for (deque<oprt_type>::size_type cl1 = 0; cl1 < operate.size(); cl1++) {
    	    if (operate[cl1].oprt == "*") {
    	    	clust_oprt[clust_indx].push_back(operate[cl1]);
    	    }
    	    else if (operate[cl1].oprt == "+") {
    	    	major_oprt.push_back(operate[cl1]);
    	    	if (cl1+1 < operate.size()) {
    	    		clust_indx++;
    	    		clust_oprt.push_back(clust_init);
    	    	}
    	    }
    	 }

    	 if ((major_oprt.size()+1) != clust_oprt.size()) { cerr << "ERROR!: Matching between number of clusters and major operators." << endl;}
    }
    else {
    	clust_oprt.clear();
    	major_oprt.clear();
    	major_oprt = operate;
    	for (deque<oprt_type>::size_type clnum = 0; clnum < (operate.size()+1); clnum++) {
    		clust_oprt.push_back(clust_init);
    	}
    }




    // **********************************************************************************************************************



    // *************************** Calculating the Result of each Section in Splitter ********************************

    input_iter = 0;
    for (deque<split>::size_type ww1 = 0; ww1 < splitter.size(); ww1++) {
        temp_res = 0;
        input_iter = 0;
        if (splitter[ww1].sect[0] != "YEK") {
            input_iter = 0;
            for (;input_iter < func_inputs.size();) {
                if (splitter[ww1].sect[0] == func_inputs[input_iter].in_name) {
                    break;
                }
                if (input_iter+1 < func_inputs.size()) {input_iter++;}
            }
            if (splitter[ww1].sect[1] == "-") {
                temp_res = func_inputs[input_iter].in_val;
            }
            else if (splitter[ww1].sect[1] == "!") {
                temp_res = !func_inputs[input_iter].in_val;
            }
        }
        else if (splitter[ww1].sect[0] == "YEK") {
            temp_res = 1;
        }
        input_iter = 0;
        if (splitter[ww1].sect[3] != "YEK") {
            input_iter = 0;
            for (;input_iter < func_inputs.size();) {
                if (splitter[ww1].sect[0] == func_inputs[input_iter].in_name) {
                    break;
                }
                if (input_iter+1 < func_inputs.size()) {input_iter++;}
            }
            if (splitter[ww1].sect[4] == "-") {
                if (splitter[ww1].sect[2] == "+") {
                    temp_res = temp_res | func_inputs[input_iter].in_val;
                }
                else if (splitter[ww1].sect[2] == "*") {
                    temp_res = temp_res & func_inputs[input_iter].in_val;
                }
            }
            else if (splitter[ww1].sect[4] == "!") {
                if (splitter[ww1].sect[2] == "+") {
                    temp_res = temp_res | !func_inputs[input_iter].in_val;
                }
                else if (splitter[ww1].sect[2] == "*") {
                    temp_res = temp_res & !func_inputs[input_iter].in_val;
                }
            }
        }
        else if (splitter[ww1].sect[3] == "YEK") {
            if (splitter[ww1].sect[2] == "*") {
                temp_res = temp_res & 1;
            }
            else {
                cerr << "ERROR!: In wire initialization." << endl;
            }
        }

        if (splitter[ww1].sign == "-") {
           splitter[ww1].value = temp_res;
        }
        else if (splitter[ww1].sign == "!") {
           splitter[ww1].value = !temp_res;
        }

    }

    // ******************************************************************************************************************


    // ********************* Calculating the "final_result" which is the result of whole function ***********************

    clust_results.clear();
    split_indx = 0;
    clust_results.push_back(clt_res);
    check_cluster = 0;
    for (deque < deque<oprt_type> >::size_type clst1 = 0; clst1 < clust_oprt.size(); clst1++) {
    	for (deque<oprt_type>::size_type clst2 = 0; clst2 < clust_oprt[clst1].size()+1; clst2++) {
    		clust_results[clst1].push_back(splitter[split_indx].value);
    		check_cluster++;
    		if ((split_indx+1) < splitter.size()) { split_indx++;}
    	}
    	if (clst1+1 < clust_oprt.size()) {
    		clust_results.push_back(clt_res);
    	}
    }

    if (check_cluster != splitter.size()) {
    	cerr << "ERROR!: Problem in Number and/or Size of Clusters." << endl;
    }


    if (mix_cond == 1) {
    	clust_finals.clear();
    	oper_indx = 0;
    	for (deque < deque<bool> >::size_type resc1 = 0; resc1 < clust_results.size(); resc1++) {
    		oper_indx = 0;
    	    final_result = 1;
    	    for (deque<bool>::size_type resc2 = 0; resc2 < clust_results[resc1].size(); resc2++) {
    	    	if ((resc2+1) < clust_results[resc1].size()) {
    	    		final_result = final_result & clust_results[resc1][resc2] & clust_results[resc1][resc2+1];
    	    	}
    	    	else {
    	    			final_result = final_result & clust_results[resc1][resc2];
    	    	}
    	    	if (oper_indx < clust_oprt[resc1].size()) {
    	    		if (clust_oprt[resc1][oper_indx].sign == "!") {
    	    			final_result = !final_result;
    	    		}
    	    	}
    	    	if (oper_indx+1 < clust_oprt[resc1].size()) {oper_indx++;}
    	    	if ((resc2+1) < clust_results[resc1].size()) {resc2++;}
    	    }
    	    clust_finals.push_back(final_result);
    	}
    }
    else {
    	clust_finals.clear();
    	for (deque< deque<bool> >::size_type resp1 = 0; resp1 < clust_results.size(); resp1++) {
    		clust_finals.push_back(clust_results[resp1][0]);
    	}
    }


    if (major_oprt.size() != 0) {
    	oper_indx = 0;
    	final_result = 0;
    	for (deque<bool>::size_type jam1 = 0; jam1 < clust_finals.size(); jam1++) {
    	    if (jam1+1 < clust_finals.size()) {
    	    	final_result = final_result | clust_finals[jam1] | clust_finals[jam1+1];
    	    }
    	    else {
    	    	final_result = final_result | clust_finals[jam1];
    	    }
    	    if (oper_indx < major_oprt.size()) {
    	    	if (major_oprt[oper_indx].sign == "!") {
    	    		final_result = !final_result;
    	    	}
    	    }
    	    if (oper_indx+1 < major_oprt.size()) {oper_indx++;}
    	    if (jam1+1 < clust_finals.size()) {jam1++;}
    	}
    }
    else if (major_oprt.size() == 0) {
    	final_result = clust_finals[0];
    }


    // ******************************************************************************************************************


    return final_result;

}


// ***************** TRUTH TABLE Start *******************

vector< vector<unsigned int> > encoder::TT_gen (unsigned int n) {

 	std::vector<std::vector<unsigned int> > output(n, std::vector<unsigned int>(1 << n));

    unsigned num_to_fill = 1U << (n - 1);
    for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
    {
        for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
        {
            std::fill_n(&output[col][row], num_to_fill, 1);
        }
    }

    return output;
}

// ******************* TRUTH TABLE End *********************


// ************************************** Generating Vector of Control Values **************************************

std::vector<double> encoder::control_function (deque<string> FUNCTION) {

    srand (time(NULL));

    vector<double> cont_vals;

    unsigned long long int conflict_count = 0;

    bool temp_value = 0;

    vector<bool> res0_vect, res1_vect;

    double temp_cont = 0.0;

    double tmp_size = 0.0;

    func_in init;

    deque<func_in> FUNC_INS;

    vector<std::vector<unsigned int> > table;

    unsigned int rand_index[12];

    deque<func_in> rand_inputs;

    bool skip_cond = 0;

    vector<unsigned long long int> rem_index;

    rem_index.clear();

    table.clear();

    FUNC_INS.clear();

    cont_vals.clear();

    rand_inputs.clear();

    init.in_name = "0";
    init.in_val = 0;

    bool new_input_cond = 0;

    deque<func_in>::size_type in_count = 0;


    // ***********  Finding Inputs *************

    in_count = 0;
    for (deque<string>::size_type i2 = 0; i2 < FUNCTION.size(); i2++) {
        if (FUNCTION [i2] != "+" && FUNCTION [i2] != "#" && FUNCTION [i2] != "*"
            && FUNCTION [i2] != "-" && FUNCTION [i2] != "!" && FUNCTION [i2] != "YEK") {
            new_input_cond = 0;
            for (deque<func_in>::size_type new_ini = 0; new_ini < FUNC_INS.size(); new_ini++) {
                if (FUNCTION[i2] == FUNC_INS[new_ini].in_name) {
                    new_input_cond = 1;
                }
            }
            if (new_input_cond == 0) {
                FUNC_INS.push_back(init);
                FUNC_INS[in_count].in_name = FUNCTION[i2];
                in_count++;
            }
        }
    }

    // ******************************************


    // ***********  Generating Truth Table and Formatting Inputs of Function *************

    if (FUNC_INS.size() <= 10) {

        table = TT_gen (FUNC_INS.size()-1);

    }

    else if (FUNC_INS.size() > 10) {

        table = TT_gen (10);

        rem_index.clear();
        for (unsigned int inp_num = 0; inp_num <= 10; inp_num++) {
            rand_index[inp_num] = rand() % (FUNC_INS.size());
        }

        for (unsigned long long int rem_num = 0; rem_num < FUNC_INS.size(); rem_num++) {
            skip_cond = 0;
            for (unsigned int cx1 = 0; cx1 <= 10; cx1++) {
                if (rem_num == rand_index[cx1]) {
                    skip_cond = 1;
                }
            }
            if (skip_cond == 0) {
                rem_index.push_back(rem_num);
            }
        }

        for (unsigned int r1 = 0; r1 <= 10; r1++) {
            rand_inputs.push_back(FUNC_INS[rand_index[r1]]);
        }

        for (vector<unsigned long long int>::size_type lx = 0; lx < rem_index.size(); lx++) {
            FUNC_INS[rem_index[lx]].in_val = rand() % 2;
            rand_inputs.push_back(FUNC_INS[rem_index[lx]]);
        }

        FUNC_INS.clear();
        FUNC_INS = rand_inputs;

    }

    // *******************************************************************************************

    // Initializing Inputs of Function, Obtaining Value of Function and Calculating Control Value

    for (deque<string>::size_type ptr = 0; ptr < FUNC_INS.size(); ptr++) {

        if (FUNC_INS[ptr].in_name == "YEK") {
            continue;
        }
        res0_vect.clear();
        res1_vect.clear();
        conflict_count = 0;
        temp_cont = 0.0;
        tmp_size = 0.0;

        FUNC_INS[ptr].in_val = 0;
        for (unsigned long long tab0_indx = 0; tab0_indx < table[0].size(); tab0_indx++) {
            temp_value = 0;
            if (ptr == 0) {
                for(unsigned long long kk0 = 0; kk0 < table.size(); kk0++) {
                    FUNC_INS[kk0+1].in_val = table[kk0][tab0_indx];
                }
            }
            else if (ptr > 0) {
                for(unsigned long long yy0 = 0; yy0 < ptr; yy0++) {
                    FUNC_INS[yy0].in_val = table[yy0][tab0_indx];
                }
                if (ptr < table.size() && ptr+1 < FUNC_INS.size()) {
                    FUNC_INS[ptr+1].in_val = table[ptr][tab0_indx];
                }
                if (ptr+1 < table.size() && ptr+2 < FUNC_INS.size()) {
                    for(unsigned long long zz0 = ptr+1; zz0 < table.size(); zz0++) {
                        FUNC_INS[zz0+1].in_val = table[zz0][tab0_indx];
                    }
                }
            }
            temp_value = parse_calc (FUNCTION, FUNC_INS);;
            res0_vect.push_back(temp_value);
        }

        FUNC_INS[ptr].in_val = 1;
        for (unsigned long long tab1_indx = 0; tab1_indx < table[0].size(); tab1_indx++) {
            temp_value = 0;
            if (ptr == 0) {
                for(unsigned long long kk1 = 0; kk1 < table.size(); kk1++) {
                    FUNC_INS[kk1+1].in_val = table[kk1][tab1_indx];
                }
            }
            else if (ptr > 0) {
                for(unsigned long long yy1 = 0; yy1 < ptr; yy1++) {
                    FUNC_INS[yy1].in_val = table[yy1][tab1_indx];
                }
                if (ptr < table.size() && ptr+1 < FUNC_INS.size()) {
                    FUNC_INS[ptr+1].in_val = table[ptr][tab1_indx];
                }
                if (ptr+1 < table.size() && ptr+2 < FUNC_INS.size()) {
                    for(unsigned long long zz0 = ptr+1; zz0 < table.size(); zz0++) {
                        FUNC_INS[zz0+1].in_val = table[zz0][tab1_indx];
                    }
                }
            }
            temp_value = parse_calc (FUNCTION, FUNC_INS);;
            res1_vect.push_back(temp_value);
        }

        conflict_count = 0;
        for (vector<bool>::size_type dd1 = 0; dd1 < res0_vect.size(); dd1++) {
            if (res0_vect[dd1] != res1_vect[dd1]) {
                conflict_count++;
            }
        }

        tmp_size = table.size();
        temp_cont = conflict_count / pow (2.0, tmp_size);
        cont_vals.push_back(temp_cont);

    }

    // *******************************************************************************************

    return cont_vals;

}

// **************************************************************************************************





int main () {


	ifstream file_input ("input_file.txt");								// The Text File to Read.

    vector<gate> circuit_gates;											// Container for Read Gates and Components

    circuit_gates.clear();

    vector<controls_type> average_controls;								// Container for Average Control Values

    average_controls.clear();

    vector<controls_type> median_controls;								// Container for Median Control Values

    median_controls.clear();

    benchmark_parse (file_input, circuit_gates);						// Reading and Parsing Benchmark

    double temp_final_conts = 0.00;										// Used in Calculating Average and Median Control Values

    controls_type cont_vinit;											// Pushing new element to "average_controls" container

    cont_vinit.final_cont = 0.00;

    vector<controls_type>::size_type ave_indx = 0;						// Index of "average_controls" container

    vector<controls_type>::size_type med_indx = 0;						// Index of "median_controls" container

    vector<controls_type> suspicious_wires;								// Container for Suspicious Wires

    suspicious_wires.clear();

    vector<double> temp_median;											// Used in Calculating Median Control Values

    temp_median.clear();

    vector<double>::size_type int_indx = 0;								// Index for converting double to integer (used in Median CVs)


    double epsilon = 2.00;												// ******** IMPORTANT: Threshold for Control Values ********

    bool check_ave = 1;													// ******** IMPORTANT: Condition of Average Procedure ********

    bool check_med = 0;													// ******** IMPORTANT: Condition of Median Procedure ********



    // ***************************** Obtaining Control Values of Read Gates and Components *****************************

    for (vector<gate>::size_type gi1 = 0; gi1 < circuit_gates.size(); gi1++) {

    	for (vector<wire>::size_type pre1 = 0; pre1 < circuit_gates[gi1].inputs.size(); pre1++) {
            circuit_gates[gi1].inputs[pre1].w_func.clear();
            circuit_gates[gi1].inputs[pre1].w_func.push_back(circuit_gates[gi1].inputs[pre1].w_name);
            circuit_gates[gi1].inputs[pre1].w_func.push_back("-");
            circuit_gates[gi1].inputs[pre1].w_func.push_back("*");
            circuit_gates[gi1].inputs[pre1].w_func.push_back("YEK");
            circuit_gates[gi1].inputs[pre1].w_func.push_back("-");
            circuit_gates[gi1].inputs[pre1].w_func.push_back("#");
            circuit_gates[gi1].inputs[pre1].w_func.push_back("-");
        }

        if  (circuit_gates[gi1].g_name == "LSDNENX1") {
    		comp_gates::LSDNEN (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "SDFFX1") {
    		if (circuit_gates[gi1].outputs.size() == 1) {
    			comp_gates::SDFF (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                                  circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    		}
    		else if (circuit_gates[gi1].outputs.size() == 2) {
    			comp_gates::SDFF (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                                  circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0], circuit_gates[gi1].outputs[1]);
    		}
    	}
    	else if (circuit_gates[gi1].g_name == "NAND2X0") {
    		comp_gates::NAND2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NAND3X0") {
    		comp_gates::NAND3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                               circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AO222X1") {
    		comp_gates::AO222 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].inputs[5], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AND4X1") {
    		comp_gates::AND4 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                              circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AND2X1" || circuit_gates[gi1].g_name == "AND2X2") {
    		comp_gates::AND2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NAND4X0" || circuit_gates[gi1].g_name == "NAND4X1") {
    		comp_gates::NAND4 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AOI222X1") {
    		comp_gates::AOI222 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                                circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].inputs[5], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "INVX0") {
    		comp_gates::INV (circuit_gates[gi1].inputs[0], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AO22X1") {
    		comp_gates::AO22 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                              circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AO221X1") {
    		comp_gates::AO221 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AOI22X1") {
    		comp_gates::AOI22 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OA22X1") {
    		comp_gates::OA22 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                              circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "ISOLANDX1") {
    		comp_gates::ISOLAND (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NOR2X0") {
    		comp_gates::NOR2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "XOR3X1") {
    		comp_gates::XOR3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                              circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "XNOR3X1") {
    		comp_gates::XNOR3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                               circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "XNOR2X1") {
    		comp_gates::XNOR2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NOR4X0") {
    		comp_gates::NOR4 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                              circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AO21X1") {
    		comp_gates::AO21 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                              circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AND3X1") {
    		comp_gates::AND3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                              circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "XOR2X1") {
    		comp_gates::XOR2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OA21X1") {
    		comp_gates::OA21 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                              circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OA221X1") {
    		comp_gates::OA221 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OR2X1") {
    		comp_gates::OR2 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NOR3X0") {
    		comp_gates::NOR3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                              circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "NBUFFX2") {
    		comp_gates::BUFF (circuit_gates[gi1].inputs[0], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OAI21X1") {
    		comp_gates::OAI21 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                               circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AOI221X1") {
    		comp_gates::AOI221 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                                circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OAI22X1") {
    		comp_gates::OAI22 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OR4X1") {
    		comp_gates::OR4 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                             circuit_gates[gi1].inputs[3], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "AOI21X1") {
    		comp_gates::AOI21 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                               circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OR3X1") {
    		comp_gates::OR3 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                             circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "OA222X1") {
    		comp_gates::OA222 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].inputs[2],
                               circuit_gates[gi1].inputs[3], circuit_gates[gi1].inputs[4], circuit_gates[gi1].inputs[5], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "DFFNX2") {
    		comp_gates::DFFN (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1], circuit_gates[gi1].outputs[0]);
    	}
    	else if (circuit_gates[gi1].g_name == "MUX21X2") {
    		comp_gates::MUX21 (circuit_gates[gi1].inputs[0], circuit_gates[gi1].inputs[1],
                               circuit_gates[gi1].inputs[2], circuit_gates[gi1].outputs[0]);
    	}
    	else {
    		cerr << "ERROR!: Undefined Component: " << circuit_gates[gi1].g_name << endl;
    	}

    	for (vector<wire>::size_type gi2 = 0; gi2 < circuit_gates[gi1].outputs.size(); gi2++) {
    		if (circuit_gates[gi1].g_name != "INVX0" && circuit_gates[gi1].g_name != "NBUFFX2") {
    			circuit_gates[gi1].outputs[gi2].cont_val = encoder::control_function (circuit_gates[gi1].outputs[gi2].w_func);
                circuit_gates[gi1].outputs[gi2].w_func.clear();
    		}
    		for (vector<gate>::size_type gi3 = gi1+1; gi3 < circuit_gates.size(); gi3++) {
    			for (vector<wire>::size_type gi4 = 0; gi4 < circuit_gates[gi3].inputs.size(); gi4++) {
    				if (circuit_gates[gi1].outputs[gi2].w_name == circuit_gates[gi3].inputs[gi4].w_name) {
    					circuit_gates[gi3].inputs[gi4] = circuit_gates[gi1].outputs[gi2];
    				}
    			}
    		}
    	}
    }

    // *****************************************************************************************************************


    if (check_ave == 1 && check_med == 0) {			// Starting Average Procedure


        // *************** Calculating Average Control Values ***************

        ave_indx = 0;
        average_controls.clear();
        for (vector<gate>::size_type av1 = 0; av1 < circuit_gates.size(); av1++) {
            for (vector<wire>::size_type av2 = 0; av2 < circuit_gates[av1].outputs.size(); av2++) {
                temp_final_conts = 0;
                if (circuit_gates[av1].outputs[av2].cont_val.size() == 0) {
                    cerr << "ERROR!: There isn't any control value for wire: " << circuit_gates[av1].outputs[av2].w_name << endl;
                }
                for (vector<double>::size_type av3 = 0; av3 < circuit_gates[av1].outputs[av2].cont_val.size(); av3++) {
                    temp_final_conts += circuit_gates[av1].outputs[av2].cont_val[av3];
                }
                average_controls.push_back(cont_vinit);
                average_controls[ave_indx].wire_name = circuit_gates[av1].outputs[av2].w_name;
                average_controls[ave_indx].final_cont = temp_final_conts / circuit_gates[av1].outputs[av2].cont_val.size();
                ave_indx++;
            }
        }

        // ******************************************************************


        // ********************* Obtaining Suspicious Wires based on Average Control Values *********************

        suspicious_wires.clear();
        for (vector<controls_type>::size_type sww1 = 0; sww1 < average_controls.size(); sww1++) {
            if (average_controls[sww1].final_cont < epsilon) {
                suspicious_wires.push_back(average_controls[sww1]);
            }
        }

        if (suspicious_wires.size() == 0) {
            cerr << "ERROR!: Please increase the threshold of control values." << endl;
        }
        else {
            cout << "Suspicious Wires and Control Values (Average Procedure):" << endl << endl;
        }

        // ******************************************************************************************************

    }


    else if (check_med == 1 && check_ave == 0) {			// Starting Median Procedure


        // ******************** Calculating Median Control Values ********************

        med_indx = 0;
        median_controls.clear();
        for (vector<gate>::size_type mc1 = 0; mc1 < circuit_gates.size(); mc1++) {
            for (vector<wire>::size_type mc2 = 0; mc2 < circuit_gates[mc1].outputs.size(); mc2++) {
                temp_median.clear();
                temp_final_conts = 0;
                temp_median = circuit_gates[mc1].outputs[mc2].cont_val;
                sort (temp_median.begin(), temp_median.end());
                int_indx = (temp_median.size() - 1) / 2;
                if (temp_median.size() == 0) {
                    cerr << "ERROR!: There isn't any control value for wire: " << circuit_gates[mc1].outputs[mc2].w_name << endl;
                }
                else if (temp_median.size() % 2 == 0) {
                    temp_final_conts = (temp_median[int_indx] + temp_median[int_indx+1]) / 2;
                }
                else if (temp_median.size() % 2 != 0) {
                    temp_final_conts = temp_median[int_indx];
                }
                median_controls.push_back(cont_vinit);
                median_controls[med_indx].wire_name = circuit_gates[mc1].outputs[mc2].w_name;
                median_controls[med_indx].final_cont = temp_final_conts;
                med_indx++;
            }
        }

        // ***************************************************************************


        // ********************* Obtaining Suspicious Wires based on Median Control Values *********************

        suspicious_wires.clear();
        for (vector<controls_type>::size_type sww2 = 0; sww2 < median_controls.size(); sww2++) {
            if (median_controls[sww2].final_cont < epsilon) {
                suspicious_wires.push_back(median_controls[sww2]);
            }
        }

        if (suspicious_wires.size() == 0) {
            cerr << "ERROR!: Please increase the threshold of control values." << endl;
        }

        else {
            cout << "Suspicious Wires and Control Values (Median Procedure):" << endl << endl;
        }

        // ******************************************************************************************************


    }



    // ********************* Outputting Suspicious Wires *********************

    for (vector<controls_type>::size_type oww1 = 0; oww1 < suspicious_wires.size(); oww1++) {
        cout << suspicious_wires[oww1].wire_name << " --- " << suspicious_wires[oww1].final_cont << endl;
    }

    // ***********************************************************************



    return 0;
}


