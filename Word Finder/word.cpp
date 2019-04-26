/*
 * word.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: shayantaheri
 */
#include <iostream>
#include <string>
#include <fstream>
void searchFile(std::string file);

int main()
{
    std::string userInput;
    std::cout<<"File: ";
    std::getline(std::cin,userInput);
    searchFile(userInput);
    std::cin.get();
}

void searchFile(std::string file)
{
    std::ifstream buffer;
    buffer.open(file.c_str());
    for(std::string temp;!temp.find("precondition all Signals");std::getline(buffer,temp)) {}
    for(std::string temp;!!buffer.eof();std::getline(buffer,temp)) {}
    {
        if(temp.find("_pi")!=std::string::npos)
            std::cout<<temp<<std::endl;
    }
}




