#include "Advent2024.h"
#include "Grid.h"

#include <iostream>
#include <vector>
using namespace std;

using Pos = pair<int, int>;

vector<Pos> getValidNeighbours(const Grid<char>& terrain, Pos curPos) {
	vector<Pos> neighbours;

	int curLevel = terrain.getCell(curPos) - '0';
	Pos north = make_pair(curPos.first, curPos.second - 1);
	Pos east = make_pair(curPos.first + 1, curPos.second);
	Pos south = make_pair(curPos.first, curPos.second + 1);
	Pos west = make_pair(curPos.first - 1, curPos.second);

	if (terrain.isValid(north) && (terrain.getCell(north) - '0' == curLevel + 1)) neighbours.push_back(north);
	if (terrain.isValid(east) && (terrain.getCell(east) - '0' == curLevel + 1)) neighbours.push_back(east);
	if (terrain.isValid(south) && (terrain.getCell(south) - '0' == curLevel + 1)) neighbours.push_back(south);
	if (terrain.isValid(west) && (terrain.getCell(west) - '0' == curLevel + 1)) neighbours.push_back(west);

	return neighbours;
}

int analyzeTrailhead(const Grid<char>& terrain, Pos start, bool partB) {
	int trails = 0;

	vector<Pos> nextPos = getValidNeighbours(terrain, start);
	Grid<char> visited;
	visited.initialize(terrain.getWidth(), terrain.getHeight());
	visited.getCell(start) = '#';

	for (int curIndex = 0; curIndex < nextPos.size(); ++curIndex){
		Pos curPos = nextPos[curIndex];
		if (visited.getCell(curPos) == '#' && !partB) continue;
		visited.getCell(curPos) = '#';
		int curLevel = terrain.getCell(curPos) - '0';
		if (curLevel == 9) {
			++trails;
		}
		else {
			auto neighbours = getValidNeighbours(terrain, curPos);
			nextPos.insert(nextPos.end(), neighbours.begin(), neighbours.end());

		}
	}
	return trails;
}

void day10(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	Grid<char> terrain;
	terrain.initFromFile(inputFile);
	int height = terrain.getHeight();
	int width = terrain.getWidth();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (terrain.getCell(x, y) != '0') continue;
			answer += analyzeTrailhead(terrain, make_pair(x, y), partB);
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cout << terrain.getCell(x, y);
		}
		cout << endl;
	}
	cout << answer << endl;
}