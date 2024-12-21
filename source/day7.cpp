#include "Advent2024.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int64_t> runningTotal(vector<int64_t>::const_reverse_iterator curIt, const vector<int64_t>& tokens, bool concatActive) {
	vector<int64_t> result;
	auto nextIt = curIt + 1;
	if (nextIt == tokens.rend())
	{
		result.push_back(*curIt);
		return result;
	}

	auto nextResult = runningTotal(nextIt, tokens, concatActive);

	for (auto nextEl : nextResult) {
		result.push_back(*curIt + nextEl);
		result.push_back(*curIt * nextEl);
		if (concatActive)
		{
			auto concatStr = std::to_string(nextEl) + std::to_string(*curIt);
			result.push_back(atoll(concatStr.c_str()));
		}
	}
	return result;
}

int64_t calculate(const vector<int64_t>& tokens, int64_t total, bool concatActive) {
	//returns 0 if there is no combination of operators that will result in the required total
	//must start at right and move left for recursion to work properly
	auto calcVec = runningTotal(tokens.crbegin(), tokens, concatActive);

	auto found = std::find(calcVec.begin(), calcVec.end(), total);

	if (found == calcVec.end()) return 0;
	else return *found;

}

void day7(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;

	size_t curPos, lastPos;

	for (string line; getline(inputFile, line);) {
		vector<int64_t> tokens;
		int64_t reqTotal = 0;

		if ((curPos = line.find(':')) != string::npos) {
			reqTotal = atoll(line.substr(0, curPos).c_str());

			for (lastPos = curPos + 2; (curPos = line.find(' ', lastPos)) != string::npos;) {
				tokens.push_back(atoll(line.substr(lastPos, curPos).c_str()));
				lastPos = curPos + 1;
			}
			//add the token after the last space
			tokens.push_back(atoll(line.substr(lastPos).c_str()));
			answer += calculate(tokens, reqTotal, partB);
		}
	}
	cout << answer << endl;
}