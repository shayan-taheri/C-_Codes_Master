/*
 * agn.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: shayantaheri
 */

 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 #include <math.h>
 using namespace std;

 class gate_type {
 	 public:
	 	 string name;
	 	 double delay;
	 	 double activity;
 };

 int main () {

	 /********************************* Specifying Desired Values ***************************************/

	 unsigned int N = 27;														// Number of Gates (?)
	 double Temp = 321.64;														// Temperature (?)
	 double Dckt = 49.4798 * pow (10.00, -9);									// Circuit Delay (?)
	 double comb_activity = 0.85;												// Combinational Switching Activity (Average)
	 double seq_activity = 0.7;													// Sequential Switching Activity (Average)
	 double tox = 2.15 * pow (10.00, -9);										// Oxide Thickness (?)
	 double mob = 0.00711;														// Mobility (?)
	 double Vgs = 1.2;															// Gate-Source Voltage (?)
	 double Vth = 0.339;														// Threshold Voltage (?)
	 double t = 10.0 * 12.0 * 30.0 * 24.0 * 60.0 * 60.0;						// Duration Time (?)

	 /********************************************* END *************************************************/

	 gate_type gates[N];

	 ifstream fp ("input_file.txt");
	 if (fp.is_open())
	 {
	 		while ( !fp.eof() )
	 		{
	 			for (unsigned int inp = 0; inp < N; inp++) {
	 				fp >> gates[inp].name;
	 				fp >> gates[inp].delay;
	 				gates[inp].delay = gates[inp].delay * pow (10.00, -9);
	 			}
	 		}
	 }

	  double q = 1.602 * pow (10.00, -19);								// Electric Charge
	  double e0 = 8.85418782 * pow (10.00, -12);						// Permittivity of Free Space
	  double eox = 3.9 * e0;											// Permittivity of Gate Oxide
	  double Cox = eox/tox;												// Oxide Capacitance
	  double AF = pow (10.00, 11);										// Electric Field-Acceleration Factor
	  double Kb = 8.62 * pow (10.00, -5);								// Boltzmann Constant
	  double Dh = mob * Kb * Temp;										// Diffusion Coefficient
	  double ni = 1.45 * pow (10.00, 4);								// Maximum Available Si Density
	  double an = 6 * pow (10.00, -21);									// Capture Cross Section Model - Electron (!)
	  double ap = 2 * pow (10.00, -20);									// Capture Cross Section Model - Hole (!)
	  double a0 = sqrt (an * ap);										// Capture Cross Section Model - Geometric Mean
	  double Eox = (Vgs - Vth) / tox;									// Electric Field Across the Oxide Field
	  double Ea = 1.1;													// Activation Energy for NBTI Effect (0.8eV - 1.2eV)
	  double alph = 0.9 * pow (10.00, -10);								// in Alpha-Power Law Model (!)
	  double B [N];														// Bond Dissociation Coefficient
	  double diff_delay = 0.0;											// Difference between Future Delay and Design Delay
	  double f0 [N];													// Frequency Factor (in recovery phase)
	  double Kr [N];													// Hydrogen Annealing Rate
	  double X [N];
	  double Ac [N];
	  double sect = 0.0;
	  double result = 0.0;
	  bool comb_des = false;
	  bool seq_des = false;

	  string comb [43] = {"NOR2X0", "NAND3X0", "INVX0", "NAND2X1", "OA21X1", "AND2X1", "NBUFFX2", "XOR2X1", "NOR3X0", "NAND4X0",
			  	  	   "NOR4X0", "AO22X1", "OR2X1", "AO221X1", "AOI22X1", "XNOR2X1", "FADDX1", "OR3X1", "OR4X1", "INVX2", "AND3X1", "OAI21X1",
			  	  	   "NAND2X0", "MUX21X1", "AO21X1", "OA22X1", "AOI21X1", "MUX41X1", "AO222X1", "NAND3X1", "AND2X2", "AND2X4", "FADDX2",
			  	  	   "DELLN1X2", "SRAM(1R1W)", "OA221X1", "AOI222X1", "AND4X1", "SRAM(4R4W)", "AOI221X1", "NBUFFX4", "OAI22X1", "SRAM(4R4W_AMT)"};

	  string seq[4] = {"DFFX1", "LATCHX1", "DFFX2", "LARX1"};

	  for (unsigned int ry = 0; ry < N; ry++) {

		  comb_des = false;
		  seq_des = false;

		  for (unsigned int wq = 0; wq < 43; wq++) {
			  if (gates[ry].name == comb[wq]) {
				  comb_des = true;
			  }
		  }

		  for (unsigned int wq = 0; wq < 4; wq++) {
			  if (gates[ry].name == seq[wq]) {
		  		  seq_des = true;
		  	  }
		  }

		  if (comb_des == true && seq_des == false) {
			  gates[ry].activity = comb_activity;
		  }

		  else if (comb_des == false && seq_des == true) {
			  gates[ry].activity = seq_activity;
		  }

		  else {
			  cerr << "ERROR!";
		  }

	  }

	  for (unsigned int ix = 0; ix < N; ix++) {

		 B [ix] = exp (-(Ea - (alph * Eox)) / (Kb * Temp));
		 f0[ix] = 1 / (t - (gates[ix].activity * t));
		 Kr[ix] = f0[ix] * exp (-Ea / (Kb * Temp));
		 X[ix] = sqrt ((1 / Kr[ix]) * B[ix] * a0 * ni) * pow (Dh, 0.35);
		 Ac[ix] = (q * X[ix] * sqrt ((Eox * exp (Eox / AF)))) / Cox;
		 sect = sect + (alph * Ac[ix] * pow (gates[ix].activity, 0.35) * gates[ix].delay) / (Dckt * (Vgs - Vth));
	  }

	  result = log10 (t) + 0.35 * log10 (sect);

	  diff_delay = Dckt * pow (10.00, (result)) * pow (10.00, 9);

	  cout << diff_delay;

 return 0;

 }
