#include "Advent2024.h"

#include <iostream>
#include <string>
#include <ranges>
#include <string_view>
#include <chrono>
#include <map>
using namespace std;

struct SplitAnswer {
	int64_t first = 0;
	int64_t second = 0;
	bool split = false;
};

SplitAnswer oneBlink(int64_t value) {
	SplitAnswer answer;
	int numDigits = static_cast<int>(log10(value)) + 1;
	if (value == 0) {
		answer.first = 1;
	}
	else if (numDigits % 2 == 0) {
		answer.split = true;
		int splitVal = static_cast<int>(pow(10, numDigits / 2));
		answer.first = value / splitVal;
		answer.second = value % splitVal;
	}
	else {
		answer.first = value * 2024;
	}

	return answer;
}

int64_t calculate(int64_t value, int blinks) {

	static map<pair<int64_t, int>, int64_t> history;

	auto foundHistory = history.find(make_pair(value, blinks));
	if (foundHistory != history.end()) {
		return foundHistory->second;
	}


	auto oneResult = oneBlink(value);
	int64_t length = 0;

	if (blinks > 1) {
		length = calculate(oneResult.first, blinks - 1);

		if (oneResult.split)
		{
			length += calculate(oneResult.second, blinks - 1);
		}
	}
	else {
		length = 1;
		if (oneResult.split) {
			length = 2;
		}
	}

	history.insert(make_pair(make_pair(value, blinks), length));
	return length;
}

void day11(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	string input;

	for (std::string line; std::getline(inputFile, line);) {
		input = line;
		break;
	}
	int numBlinks = (partB ? 75 : 25);

	auto splitRange = views::split(input, ' ');
	for (const auto& elem : splitRange) {
		string_view text(elem.begin(), elem.end());

		answer += calculate(atoll(text.data()), numBlinks);
	}

	cout << "Answer: " << answer << endl;
}