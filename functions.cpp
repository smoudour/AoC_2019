#include "D:/c++/adventofcode/functions.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>


// -- DAY 1 --
//to calculate fuel
int fuelCalculator(int mass) {
	int fuel = floor(mass/3) - 2;
	return fuel;
}

//TEST FOR PRIME NUMBERS
//Simple method. Complexity O(num)
bool is_prime_simple(int num) {

	if (num==2 || num==3) {
		return true;
	}

	else if (num==1) {
		return false;
	}

	else {
		for (int i=2; i<num; ++i) {
			if (num%i == 0) {
				return false;
			}
		}

		return true;

	}

}

//Fermat Method



// -- DAY 2 --
//Vector Constructor
std::vector<int> vectorCreator(std::string input) {

	std::vector<int> program;
	std::stringstream ss(input);

	for (int i; ss >> i;) {
		program.push_back(i);

		if (ss.peek() == ',' || ss.peek() == ' ') {
			ss.ignore();
		}
	}

	return program;
}

//Code solver: 1 for addition, 2 for multipliation, 99 for halt
void intCode(std::vector<int> &code_vector) {

	for (int i=0; i<code_vector.size(); ++i) {
		if (code_vector[i] == 1) {
			code_vector[code_vector[i+3]] = code_vector[code_vector[i+1]] + code_vector[code_vector[i+2]];
			//set position of index to n-1, because it will be incremented in the rerun of the loop
			i = i+3;  //slide position to next quadruplet.

		}

		else if (code_vector[i] == 2) {
			code_vector[code_vector[i+3]] = code_vector[code_vector[i+1]] * code_vector[code_vector[i+2]];
			i = i+3;
		}

		else if (code_vector[i] == 99) {
			break;
		}

		else {
			std::cout << i << " - Oops... Something went wrong.\nInvalid value at opcode position... " << std::endl;
		}
	}
}

// -----

// -- DAY 3 --
//pass instructions to string array
std::vector<std::string> makeInstr (std::string &string) {

	std::string delim = "," ;
	size_t pos = 0;
	std::vector<std::string> instr;	//array to store instructions

	while ((pos = string.find(delim)) != std::string::npos) {
		instr.push_back(string.substr(0, pos));
		string.erase(0, pos + delim.length());
	}
	return instr;
}

//use string array to get sizes for matrix needed
int *getSize(std::vector<std::string> &input, std::string axis) {

	int threshold = 0;	//dynamic sum for both directions. If it becomes bigger than max
	// or smaller than min, it changes these corresponding values.
	char a,b;	//variables to hold the movements. char type because of comparison with char array element (?)
	int *results = new int[2];	//array to be returned - dynamic memory
	int max_=0, min_=0;	//max and min values to keep track of limits

	results[0] = 0;
	results[1] = 0;

	if (axis == "x") {
		a = 'R';
		b = 'L';
	}

	else if (axis == "y") {
		a = 'U';
		b = 'D';
	}

	for (int i=0; i<input.size(); ++i) {
		//assign every string element of vector to a temp string
		std::string token = input[i];

		if (token[0] == a) {
			//assign number of steps to walk on int
			int steps = stoi(token.substr(1));
			//add to threshold
			threshold += steps;
			//set max value
			if (threshold > max_) {
				max_ = threshold;
			}
			token.erase(0);
		}
		else if (token[0] == b) {
			//assign number of steps to walk on int
			int steps = stoi(token.substr(1));
			//subtract from threshold
			threshold -= steps;
			//set min value
			if (threshold < min_) {
				min_ = threshold;
			}

			token.erase(0);

		}
	}
	results[0] = abs(max_-min_);	//size of selected axis
	results[1] = abs(min_);	//point (0,0) for the new array, or where to start drawing
	return results;
}

//Draw cable on appropriate sized 2d vector
//changes the values of given empty vector to 1 for cable line, 2 for crossing.
//do this for each cable (?), or all at once (?)
void drawCable(std::vector<std::string> &instr, std::vector<std::vector<int> > &layout, int &x_pos, int &y_pos) {

  std::string token;
	unsigned int steps;

	//loop through all instructions
	for (unsigned int i=0; i<instr.size(); ++i) {
		token = instr[i];
		steps = stoi(token.substr(1));
		if (token[0] == 'R') {
			for (unsigned int j = 0; j<steps; ++j) {
				if (layout[y_pos][x_pos+j] == 0) {
					layout[y_pos][x_pos+j] = 1;
				}
				else if (layout[y_pos][x_pos+j] == 1) {
					layout[y_pos][x_pos+j] = 2;
				}
			}
			x_pos += steps;
		}
		else if (token[0] == 'L') {
			for (unsigned int j=0; j<steps; ++j) {
				if (layout[y_pos][x_pos-j] == 0) {
					layout[y_pos][x_pos-j] = 1;
				}
				else if (layout[y_pos][x_pos-j] == 1) {
					layout[y_pos][x_pos-j] = 2;
				}
			}
			x_pos -= steps;
		}
		else if (token[0] == 'U') {
			for (unsigned int j=0; j<steps; ++j) {
				if (layout[y_pos+j][x_pos] == 0) {
					layout[y_pos+j][x_pos] = 1;
				}
				else if (layout[y_pos+j][x_pos] == 1) {
					layout[y_pos+j][x_pos] = 2;
				}
			}
			y_pos += steps;
		}
		else if (token[0] == 'D') {
			for (unsigned int j=0; j<steps; ++j) {
				if (layout[y_pos-j][x_pos] == 0) {
					layout[y_pos-j][x_pos] = 1;
				}
				else if (layout[y_pos-j][x_pos] == 1) {
					layout[y_pos-j][x_pos] = 2;
				}
			}
			y_pos -= steps;
		}
		else {
			std::cout << "Unexpected instruction of: " << instr[i] << " at position " << i << std::endl;
			exit(0);
		}
	}

}

// -- DAY 4 --
//give count of compatible codes for range of nums (low - high)
int giveCount(unsigned int const &low, unsigned int const &high) {
	unsigned int count = 0;
	for (unsigned int i = low; i<high; ++i) {
		int cond1 = 1;	//test if digits are increasing
		bool cond2 = false;	//test for minimal pairs (duplets)
		std::vector<char> digits;	//vector holding values of duplicates

		std::stringstream ss;
		ss << i;
		std::string code = ss.str();

		for (int i=1; i<code.size(); ++i)
		{
			if (code[i-1] > code[i])
			{
				break;
			}
			else
			{
				++cond1;
				if (code[i-1] == code[i])
				{
					int duplet_num = 0;
					for (int j=1; j<code.size(); ++j)
					{
						if (code[j-1] == code[j])
						{
							++duplet_num;
						}
					}
					if (duplet_num==1)
					{
						cond2 = true;
					}
				}
			}
		}
		if (cond1 == code.size() && cond2 == true) {
				++count;
		}
	}
	return count;
}
