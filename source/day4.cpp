#include "Advent2024.h"
#include "Grid.h"
#include <iostream>
using namespace std;

using Pos = pair<int, int>;

int wordFound(Grid<char>& wordSearch, const string& wordToFind, int offset, Pos curPos, Pos dirPos) {
	int recurseFound = 0;
	//move forward in the search direction.
	curPos = make_pair(curPos.first + dirPos.first, curPos.second + dirPos.second);

	if (!wordSearch.isValid(curPos)) return 0;

	char curChar = wordSearch.getCell(curPos);
	if (curChar != wordToFind[offset]) return 0;

	//last letter found
	if (offset == wordToFind.size() - 1) return 1;
	offset++;

	if (dirPos.first == 0 && dirPos.second == 0) {//recurse in all directions
		recurseFound = wordFound(wordSearch, wordToFind, offset, curPos, make_pair(0, -1)) //N
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(1, -1)) //NE
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(1, 0)) //E
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(1, 1)) //SE
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(0, 1)) //S
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(-1, 1)) //SW
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(-1, 0)) //W
			+ wordFound(wordSearch, wordToFind, offset, curPos, make_pair(-1, -1)); //NW
	}
	else { //recurse only in the one direction
		recurseFound = wordFound(wordSearch, wordToFind, offset, curPos, dirPos);
	}

	return recurseFound;
}



void day4(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	Grid<char> wordSearch;
	string reqWord("XMAS");
	
	wordSearch.initFromFile(inputFile);
	int height = wordSearch.getHeight();
	int width = wordSearch.getWidth();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			
			if (partB) {
				char curChar = wordSearch.getCell(x, y);
				if (curChar != 'A') continue;

				string corners;
				if (!wordSearch.isValid(x + 1, y - 1)) continue;
				corners += wordSearch.getCell(x + 1, y - 1);

				if (!wordSearch.isValid(x + 1, y + 1)) continue;
				corners += wordSearch.getCell(x + 1, y + 1);

				if (!wordSearch.isValid(x - 1, y + 1)) continue;
				corners += wordSearch.getCell(x - 1, y + 1);

				if (!wordSearch.isValid(x - 1, y - 1)) continue;
				corners += wordSearch.getCell(x - 1, y - 1);

				if (corners == "SSMM" || corners == "SMMS" || corners == "MMSS" || corners == "MSSM") {
					++answer;
				}
			}
			else {
				int found = wordFound(wordSearch, reqWord, 0, make_pair(x, y), make_pair(0, 0));
				if (found) {
					//cout << "found " << found << " at: " << x << "," << y << endl;
					answer += found;
				}
			}
		}
	}
	cout << answer << endl;
}