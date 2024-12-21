#include "Advent2024.h"

#include <iostream>
#include <string>
#include <ranges>
#include <unordered_map>
using namespace std;

void day5(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	unordered_multimap<int, int> ruleMap;

	for (string line; getline(inputFile, line);) {

		auto ruleRange = views::split(line, string("|"));

		if (!ruleRange.empty() && ++ruleRange.begin() != ruleRange.end()) {
			int ruleA = atoi(ruleRange.front().data());
			int ruleB = atoi((*(++ruleRange.begin())).data());

			ruleMap.insert({ ruleA, ruleB });
			continue;
		}

		auto updateRange = views::split(line, string(","));
		if (updateRange.empty()) continue;

		vector<int> updateList;
		bool validList = true;
		for (auto update : updateRange) {
			int updateVal = atoi(update.data());

			if (updateList.empty()) {
				updateList.push_back(updateVal);
				continue;
			}

			//check if this page update is valid based on earlier pages
			auto insertPos = updateList.end();
			auto afterPages = ruleMap.equal_range(updateVal);
			for (; afterPages.first != afterPages.second; ++afterPages.first) {
				int afterPage = afterPages.first->second;

				auto foundItem = find(updateList.begin(), updateList.end(), afterPage);
				
				if (foundItem != updateList.end()) {
					validList = false;
					//our item must be before this one. But only use this position if it is earlier than all others
					if (partB && foundItem < insertPos) {
						insertPos = foundItem;
					}
				}
			}
			updateList.insert(insertPos, updateVal);

		}

		int middlePage = updateList[updateList.size() / 2];
		if (validList)
		{
			//cout << line << " Valid, middle page: " << middlePage << endl;
			if (!partB) {
				answer += middlePage;
			}
		}
		else {
			//cout << line << " not valid." << endl;
			if (partB) {
				//cout << " swapped, middle page: " << middlePage << endl;
				answer += middlePage;
			}
		}

	}

	cout << answer << endl;
}