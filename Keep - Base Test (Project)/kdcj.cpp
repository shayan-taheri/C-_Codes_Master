/*
 * kdcj.cpp
 *
 *  Created on: May 11, 2014
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


class wire {								// Class (Type) for Wires
public:
 	string w_name;							// Name of Wire
 	bool value;								// Value of Wire
 	vector<double> cont_val;				// Control Values of Wire
 	deque<string> w_func;};					// Functionality of Wire


class gate {								// Class (Type) for Gates
public:
 	string g_name;							// Name of Gate
 	vector <wire> inputs;					// Inputs of Gate
 	vector <wire> outputs;};				// Outputs of Gate


class func_in {						// Class for the inputs of the function.
public:
    string in_name;					// Input Name
    bool in_val;					// Input Value
};


class split {							// Class for the splitter which places the function of each 2-Input gate in a section.
public:
    deque<string> sect;			// The function of 2-Input gate = A section.
    string sign;					// The sign for the section.
    bool value;					// The result of each section "with considering the Sign".
};


class oprt_type {						// Class for major operators of the whole function.
public:
    string oprt;					// Major operator
    string sign;					// Associated sign with major operator.
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
 	AND_Base (temp_IN1, IN2, o1);
 	AND_Base (IN1, temp_IN2, o2);
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
 	wire o1 = w_ini, o2 = w_ini, o3 = w_ini, o4 = w_ini, o5 = w_ini;
 	AND_Base (temp_IN1, IN2, o1);
 	AND_Base (IN1, temp_IN2, o2);
 	OR_Base (o1, o2, o3);
 	NOT_Base (o3, temp_o3);
 	AND_Base (o3, IN3, o4);
 	AND_Base (temp_o3, temp_IN3, o5);
 	OR_Base (o4, o5, OUT);

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
    wire o1 = w_ini;
    OR_Base (X1, X2, o1);
    AND_Base (o1, Y, OUT);

}

void comp_gates::OA22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    OR_Base (X1, X2, o1);
    OR_Base (Y1, Y2, o2);
    AND_Base (o1, o2, OUT);

}

void comp_gates::OA221 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& K, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
    OR_Base (X1, X2, o1);
    OR_Base (Y1, Y2, o2);
    AND_Base (o1, o2, o3);
    AND_Base (o3, K, OUT);

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

}

void comp_gates::OAI21 (wire& X1, wire& X2, wire& Y, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini;
    OR_Base (X1, X2, o1);
    AND_Base (o1, Y, o2);
    NOT_Base (o2, OUT);

}

void comp_gates::OAI22 (wire& X1, wire& X2, wire& Y1, wire& Y2, wire& OUT) {
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, o3 = w_ini;
    OR_Base (X1, X2, o1);
    OR_Base (Y1, Y2, o2);
    AND_Base (o1, o2, o3);
    NOT_Base (o3, OUT);

}

void comp_gates::BUFF (wire& IN, wire& OUT) {
    OUT.value = IN.value;
    OUT.w_func = IN.w_func;

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
    wire w_ini;
    w_ini.value = 0;
    wire o1 = w_ini, o2 = w_ini, CLK_not = w_ini;
    NOT_Base (CLK, CLK_not);
    AND_Base (D, CLK_not, o1);
    AND_Base (OUT, CLK, o2);
    OR_Base (o1, o2, OUT);

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

    // ******************* Initializing and Formatting Inputs (Values and Functionalities) **********************

    for (vector<gate>::size_type uu1 = 0; uu1 < gates.size(); uu1++) {
        for (vector<wire>::size_type uu2 = 0; uu2 < gates[uu1].inputs.size(); uu2++) {
            gates[uu1].inputs[uu2].w_func.push_back(gates[uu1].inputs[uu2].w_name);
            gates[uu1].inputs[uu2].w_func.push_back("-");
            gates[uu1].inputs[uu2].w_func.push_back("*");
            gates[uu1].inputs[uu2].w_func.push_back("ONE");
            gates[uu1].inputs[uu2].w_func.push_back("-");
            gates[uu1].inputs[uu2].w_func.push_back("#");
            gates[uu1].inputs[uu2].w_func.push_back("-");
        }
    }

    // **********************************************************************************************************

}


bool parse_calc (deque<string> function, deque<func_in> func_inputs) {

    deque<split> splitter;							// For splitting the function based on the result of each 2-input gate.

    splitter.clear();

    split split_init;

    split_init.sect.clear();

    split_init.sign = "0";

    split_init.value = 0;

    deque<oprt_type> operate;						// Container for major operators (AND or OR) of the function.

    operate.clear();

    oprt_type oprt_init;

    oprt_init.oprt = "0";

    oprt_init.sign = "0";

    string temp_oprt_signs;							// The signs for major operators.

    temp_oprt_signs.clear();

    vector<bool> vect_results;						// Container for the result of each section in "Splitter".

    vect_results.clear();

    bool final_result = 0;

    unsigned long long input_iter = 0;				// Input iterator for the "func_inputs" container.

    bool temp_res = 0;								// Raw result of the "parse_calc" function.

    unsigned long long int mm = 0;					// Index for "splitter" container.

    unsigned long long int pp = 0;					// Index for "operate" container.

    bool add_sect = 0;								// Condition for adding section to "Splitter" container.



    // *************************** Building the "Splitter" and "Major Operator" containers ********************************

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
        operate[ss].sign = temp_oprt_signs[operate.size()-1-ss];
    }

    // **********************************************************************************************************************



    // *************************** Calculating the Result of each Section in Splitter ********************************

    input_iter = 0;
    for (deque<split>::size_type ww1 = 0; ww1 < splitter.size(); ww1++) {
        temp_res = 0;

        if (splitter[ww1].sect[0] != "YEK") {
            if (splitter[ww1].sect[1] == "-") {
                temp_res = func_inputs[input_iter].in_val;
            }
            else if (splitter[ww1].sect[1] == "!") {
                temp_res = !func_inputs[input_iter].in_val;
            }
            if (input_iter+1 < func_inputs.size()) {input_iter++;}
        }
        else if (splitter[ww1].sect[0] == "YEK") {
            temp_res = 1;
        }

        if (splitter[ww1].sect[3] != "YEK") {
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
            if (input_iter+1 < func_inputs.size()) {input_iter++;}
        }
        else if (splitter[ww1].sect[3] == "YEK") {
            if (splitter[ww1].sect[2] == "*") {
                temp_res = temp_res & 1;
            }
            else {
                cerr << "ERROR!: In wire initialization.";
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

    for (deque<split>::size_type yy = 0; yy < splitter.size(); yy++) {
        vect_results.push_back(splitter[yy].value);
    }

    for (deque<oprt_type>::size_type hh1 = operate.size()-1; (hh1 >= 0) && (vect_results.size() != 1); hh1--) {
        if (operate[hh1].oprt == "+") {
            final_result = vect_results[vect_results.size()-1] | vect_results[vect_results.size()-2];
            if (operate[hh1].sign == "!") {
                final_result = !final_result;
            }
        }
        else if (operate[hh1].oprt == "*") {
            final_result = vect_results[vect_results.size()-1] & vect_results[vect_results.size()-2];
            if (operate[hh1].sign == "!") {
                final_result = !final_result;
            }
        }
        vect_results.pop_back();
        vect_results.pop_back();
        vect_results.push_back(final_result);
    }

    if (vect_results.size() != 1) {
        cerr << "ERROR! : In calculation of parse_calc's result.";
    }

    // ******************************************************************************************************************


    return final_result;

}




// ***************** TRUTH TABLE Start *******************

static std::vector<std::vector<unsigned int> > TT_gen (unsigned int n) {

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

std::vector<double> control_function (deque<func_in> & FUNC_INS, vector<std::vector<unsigned int> > & table) {

    vector<double> cont_vals;

    bool res1 = 0, res2 = 0;

    long unsigned int conflict_count = 0;

    double temp_cont = 0.0;

    cont_vals.clear();

    srand (time(NULL));

    for (deque<string>::size_type ptr = 0; ptr < FUNC_INS.size(); ptr++) {

        for(unsigned x = 0; x < table[0].size(); x++)
        {

            FUNC_INS[ptr].in_val = 0;

            if (ptr > 0) {

                for(unsigned yy = 0; yy < ptr; yy++) {
                    FUNC_INS[yy].in_val = table[yy][x];}

                for(unsigned zz = ptr+1; zz < table.size(); zz++) {
                    FUNC_INS[zz].in_val = table[zz][x];}

            }

            else if (ptr == 0) {

                for(unsigned kk = 1; kk < table.size(); kk++) {
                    FUNC_INS[kk].in_val = table[kk][x];}

            }

            // res1 = parse_calc (FUNCTION,FUNC_INS)

            FUNC_INS[ptr].in_val = 1;

            // res2 = parse_calc (FUNCTION,FUNC_INS)

            // if (res1 != res2) {
            //		conflict_count++;}

        }

        // temp_cont = conflict_count / pow (2.0, FUNC_INS.size()-1);
        // cont_vals.push_back(temp_cont);

    }

    return cont_vals;

}

// **************************************************************************************************


int main () {

    ifstream file_input ("input_file.txt");
    vector<gate> circuit_gates;

    benchmark_parse (file_input, circuit_gates);


    // the result = parse_calc (component function, component inputs);


    // component function (deque<string> function) ?


    // component inputs (deque<func_in> func_inputs) ?


    // component control values (vector<double> control_values) ?


    /* Finding Inputs of the Component's Function

     deque<func_in>::size_type in_count = 0;

     func_in init;
     init.in_name = "0";
     init.in_val = 0;

     in_count = 0;
     for (deque<string>::size_type i2 = 0; i2 < function.size(); i2++) {
     if (function [i2] != "+" && function [i2] != "#" && function [i2] != "*") {
     func_inputs.push_back(init);
     func_inputs[in_count].in_name = function[i2];
     in_count++;
     }
     }

    */

    /* Calculating Control Values of the Component

     vector<std::vector<unsigned int> > truth_table;

     unsigned int rand_index[12];

     if (func_inputs.size() <= 12) {

     truth_table = TT_gen (func_inputs.size()-1);

     control_values = control_function (func_inputs, truth_table);

     }

     else if (func_inputs.size() > 12) {

     truth_table = TT_gen (11);

     for (unsigned int inp_num = 0; inp_num <= 11; inp_num++) {
     rand_index[inp_num] = rand() % (func_inputs.size());
     }

     for (unsigned int r1 = 0; r1 <= 11; r1++) {
     rand_inputs.push_back(func_inputs[rand_index[r1]]);
     }

     control_values = control_function (rand_inputs, truth_table);

     }

     */


    return 0;

}

