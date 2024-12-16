#include "Advent2024.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void day1(ifstream& inputFile, bool partB)
{
	int answer = 0;
	vector<int> leftList, rightList;
	size_t spacePos;
	for (string line; getline(inputFile, line);) {
		if ((spacePos = line.find(' ')) != string::npos) {
			leftList.push_back(atoi(line.substr(0, spacePos).c_str()));
			rightList.push_back(atoi(line.substr(spacePos).c_str()));
		}
	}
	sort(leftList.begin(), leftList.end());
	sort(rightList.begin(), rightList.end());

	if (partB) {
		for_each(leftList.cbegin(), leftList.cend(), [&](int a) {
			auto matches = std::equal_range(rightList.cbegin(), rightList.cend(), a);
			answer += a * static_cast<int>(std::distance(matches.first, matches.second));
			});

	}
	else {
		for (size_t i = 0; i < leftList.size(); ++i) {
			answer += abs(leftList[i] - rightList[i]);
		}

	}
	cout << answer << endl;
}