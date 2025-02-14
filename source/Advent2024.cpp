﻿#include "Advent2024.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Please run with arguments: day_number part_AB input_filename" << endl;
		return 0;
	}

	int dayNum = atoi(argv[1]);
	string part(argv[2]);
	string inputFilename(argv[3]);

	bool partB = (part.starts_with('B') || part.starts_with('b'));

	ifstream inputFile(inputFilename);
	if (!inputFile)
	{
		std::cout << "Error opening input file" << std::endl;
		return 0;
	}

	if (dayNum == 1) day1(inputFile, partB);
	else if (dayNum == 2) day2(inputFile, partB);
	else if (dayNum == 3) day3(inputFile, partB);
	else if (dayNum == 4) day4(inputFile, partB);
	else if (dayNum == 5) day5(inputFile, partB);
	else if (dayNum == 6) day6(inputFile, partB);
	else if (dayNum == 7) day7(inputFile, partB);
	else if (dayNum == 8) day8(inputFile, partB);
	else if (dayNum == 9) day9(inputFile, partB);
	else if (dayNum == 10) day10(inputFile, partB);
	else if (dayNum == 11) day11(inputFile, partB);
	else if (dayNum == 12) day12(inputFile, partB);


	return 0;
}
