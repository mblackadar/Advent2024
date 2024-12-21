#include "Advent2024.h"
#include "Grid.h"

#include <iostream>
#include <set>
using namespace std;

using Pos = pair<int, int>;
using ObstacleDir = pair<Pos, Pos>; //Obstacle position, direction travelling

bool simulate(Grid<char>& labGrid, set<Pos>& visited, Pos startPos) {
	constexpr int maxSteps = 1000000;
	constexpr Pos northDir = { 0, -1 };
	constexpr Pos southDir = { 0, 1 };
	constexpr Pos eastDir = { 1, 0 };
	constexpr Pos westDir = { -1, 0 };
	Pos curDir = northDir;
	Pos curPos = startPos;
	set<ObstacleDir> hitObstacle;

	//each step is moving forward or turning. We set a max to prevent infinite loop, but this shouldn't happen since we detect getting stuck
	for (int steps = 0; steps < maxSteps; ++steps) {

		if (!visited.contains(curPos)) {
			visited.insert(curPos);
		}
		auto nextPos = make_pair(curPos.first + curDir.first, curPos.second + curDir.second);

		if (labGrid.isValid(nextPos)) {
			char nextChar = labGrid.getCell(nextPos);
			if (nextChar == '#') { //obstacle, try turning

				if (hitObstacle.contains(make_pair(nextPos, curDir))) {
					cout << "Stuck in lab: hit same obstacle at (" << nextPos.first << ", " << nextPos.second << "). Travelling ";

					if (curDir == northDir) cout << "N" << endl;
					else if (curDir == eastDir) cout << "E" << endl;
					else if (curDir == southDir) cout << "S" << endl;
					else if (curDir == westDir) cout << "W" << endl;
					return false;
				}
				else {
					hitObstacle.insert(make_pair(nextPos, curDir));
				}

				if (curDir == northDir) curDir = eastDir;
				else if (curDir == eastDir) curDir = southDir;
				else if (curDir == southDir) curDir = westDir;
				else if (curDir == westDir) curDir = northDir;
			}
			else { //go ahead and move forward
				curPos = nextPos;
			}
		}
		else {
			cout << "Path found after " << steps << " steps." << endl;
			return true; //path found
		}
	}
	cout << "Stuck in lab - run out of steps" << endl;
	return false; //stuck in lab, no path out.
}

void day6(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	Grid<char> labGrid;

	labGrid.initFromFile(inputFile);
	int height = labGrid.getHeight();
	int width = labGrid.getWidth();

	Pos startPos = { 0, 0 };
	set<Pos> visited;

	//find start tile
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			char curChar = labGrid.getCell(x, y);
			if (curChar == '^') {
				startPos = { x, y };
			}
		}
	}

	simulate(labGrid, visited, startPos);

	if (partB) {
		//for each part of the original path, try putting an obstacle there and see what occurs

		for (auto pathPos : visited) {
			if (pathPos == startPos) continue;
			labGrid.getCell(pathPos) = '#';
			set<Pos> newVisited;
			if (!simulate(labGrid, newVisited, startPos)) { //got stuck
				++answer;
			}
			labGrid.getCell(pathPos) = '.'; //set grid back to original and try next obstacle
		}
	}
	else {
		answer = visited.size();
	}
	cout << answer << endl;
}