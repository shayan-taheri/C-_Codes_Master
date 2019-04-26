/*
 * wedsac.cpp
 *
 *  Created on: May 7, 2014
 *      Author: shayantaheri
 */

#include <iostream>
#include <vector>
using namespace std;

std::vector<std::vector<unsigned int> > TT_gen (unsigned int n) {

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

int main()
{

	vector<std::vector<unsigned int> > table;
	table = TT_gen (4);
	cout << table[1].size() << endl;
    for(unsigned x = 0; x < table[0].size(); ++x)
    {
        for(unsigned y = 0; y < table.size(); ++y)
        {
            std::cout << table[y][x] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}



