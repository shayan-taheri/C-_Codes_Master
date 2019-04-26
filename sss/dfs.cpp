/*
 * dfs.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: shayantaheri
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int numVectors = 10;
const int numPI = 36;

int main()
{

 // create a holder for each value generated
 short testVectors[numVectors][numPI];

 // seed random number generator
 srand (time(NULL));

 // generate a value of 0 or 1
 for (int i = 0; i < numVectors; i++)
	for (int j = 0; j < numPI; j++)
	{
		testVectors[i][j] = rand() % 2;
	}

 // print out vector to screen
 for (int i = 0; i < numVectors; i++)
 {
	printf("\nTest Vector %d:\t", i);
	for (int j = 0; j < numPI; j++)
	{
		printf("%d", testVectors[i][j]);
	}
 }

 printf("\n\n");

 return 0;
}



