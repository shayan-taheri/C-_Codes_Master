/*
 * fourth.hpp
 *
 *  Created on: May 10, 2014
 *      Author: shayantaheri
 */

#ifndef FOURTH_HPP_
#define FOURTH_HPP_

#include "third.hpp"

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

 std::vector<double> control_function (deque<string> FUNCTION, deque<func_in> & FUNC_INS, vector<std::vector<unsigned int> > & table) {

	 	 vector<double> cont_vals;

	 	 bool res1 = 0, res2 = 0;

	 	 long unsigned int conflict_count = 0;

	 	 double temp_cont = 0.0;

	 	 cont_vals.clear();

	 	 double temp_double_size = 0.00;

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

						res1 = parse_calc (FUNCTION,FUNC_INS);

						FUNC_INS[ptr].in_val = 1;

						res2 = parse_calc (FUNCTION,FUNC_INS);

						if (res1 != res2) {
								conflict_count++;}

					}
					 temp_double_size = FUNC_INS.size()-1;
					 temp_cont = conflict_count / pow (2.00, temp_double_size);
					 cont_vals.push_back(temp_cont);

		}

	 	return cont_vals;

 }

 // **************************************************************************************************


#endif /* FOURTH_HPP_ */
