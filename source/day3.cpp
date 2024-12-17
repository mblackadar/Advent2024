#include "Advent2024.h"

#include <iostream>
#include <regex>
#include <string>
using namespace std;

void day3(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	string input;
	regex mulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");

	//store the whole input into a string, keep newlines intact
	for (string line; getline(inputFile, line);) {
		input += line;
		input += '\n';
	}

	if (partB) {
		bool mulEnabled = true;
		regex combRegex(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
		for (smatch sm; regex_search(input, sm, combRegex);)
		{
			if (sm[0] == R"(do())") {
				mulEnabled = true;
			}
			else if (sm[0] == R"(don't())") {
				mulEnabled = false;
			}
			else if (sm.size() == 3 && mulEnabled) {
				int64_t val1 = stoll(sm[1]);
				int64_t val2 = stoll(sm[2]);
				answer += val1 * val2;
			}
			input = sm.suffix();
		}
	}
	else {
		for (smatch sm; regex_search(input, sm, mulRegex);)
		{
			if (sm.size() == 3) {
				int64_t val1 = stoll(sm[1]);
				int64_t val2 = stoll(sm[2]);
				answer += val1 * val2;
			}
			input = sm.suffix();
		}
	}

	cout << answer << endl;
}
