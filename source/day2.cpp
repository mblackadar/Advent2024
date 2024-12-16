#include "Advent2024.h"

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <algorithm>
using namespace std;

bool reportValid(const vector<int>& report) {
	int lastLevel = 0;
	char reportType = ' ';

	for (auto curLevel : report) {
		if (lastLevel != 0) {
			int diff = curLevel - lastLevel;
			if (reportType == 'I' && diff < 0) return false;
			if (reportType == 'D' && diff > 0) return false;

			if (abs(diff) > 3 || abs(diff) == 0) return false;

			//this report is fine so far.
			if (reportType == ' ')
			{
				reportType = (curLevel > lastLevel ? 'I' : 'D');
			}
		}
		lastLevel = curLevel;
	}

	return true;
}

void day2(std::ifstream& inputFile, bool partB)
{
	int64_t answer = 0;
	string delim(" ");

	for (string line; getline(inputFile, line);) {
		std::vector<int> report;
		auto levelStr = views::split(line, delim);

		for (auto s : levelStr) {
			report.push_back(atoi(s.data()));
		}
		if (reportValid(report)) {
			++answer;
		}
		else if (partB) {

			vector<int> potentialFix = report;
			for (size_t index = 0; index != report.size(); ++index) {
				potentialFix.erase(potentialFix.begin() + index);
				if (reportValid(potentialFix)) {
					++answer;
					break;
				}
				potentialFix = report;
			}
		}
	}

	cout << answer << endl;
}