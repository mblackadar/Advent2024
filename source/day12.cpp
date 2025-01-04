#include "Advent2024.h"
#include "Grid.h"

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

using Pos = pair<int, int>;

struct Fence {
	Pos cell;
	char side; //NESW
};

struct Region {
	int regionID = 0;
	char plotChar = ' ';
	int area = 0;
	int perimeter = 0;
	vector<Pos> cells;
	vector<Fence> fences;
};


void day12(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	Grid<char> garden;
	Grid<int> regionGrid;
	vector<Region> regions;
	int curRegion = 0;

	garden.initFromFile(inputFile);
	int width = garden.getWidth();
	int height = garden.getHeight();
	regionGrid.initialize(width, height, -1);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			char plot = garden.getCell(x, y);
			int regionID = -1;

			int fenceSides = 0;
			Pos north(x, y - 1);
			Pos east(x + 1, y);
			Pos south(x, y + 1);
			Pos west(x - 1, y);

			vector<Fence> fenceList;
			//if north plot is the same, use its region ID
			if (garden.isValid(north) && garden.getCell(north) == plot) {
				regionID = regionGrid.getCell(north);
			}
			else {
				fenceSides++;
				fenceList.emplace_back(make_pair(x, y), 'N');
			}

			//if west plot is the same, use its region ID, if we didn't use north's
			if (garden.isValid(west) && garden.getCell(west) == plot) {
				if (regionID == -1) {
					regionID = regionGrid.getCell(west);
				}
				else if (regionID != regionGrid.getCell(west) ){ //two regions connected, merge west into north
					auto& wRegion = regions[regionGrid.getCell(west)];
					auto& nRegion = regions[regionGrid.getCell(north)];
		
					for (auto& cell : wRegion.cells) {
						nRegion.cells.push_back(cell);
						regionGrid.getCell(cell) = nRegion.regionID;
					}
					nRegion.fences.insert(nRegion.fences.end(), wRegion.fences.begin(), wRegion.fences.end());
					nRegion.area += wRegion.area;
					nRegion.perimeter += wRegion.perimeter;
					wRegion.area = 0;
					wRegion.perimeter = 0;
					wRegion.cells.clear();
					wRegion.fences.clear();
				}
			}
			else {
				fenceSides++;
				fenceList.emplace_back(make_pair(x, y), 'W');
			}
		
			//for south and eash plots, we won't use their regionID if there is a match
			if (!garden.isValid(south) || garden.getCell(south) != plot) {
				fenceSides++;
				fenceList.emplace_back(make_pair(x, y), 'S');
			}
			if (!garden.isValid(east) || garden.getCell(east) != plot) {
				fenceSides++;
				fenceList.emplace_back(make_pair(x, y), 'E');
			}
			if (regionID == -1) { //create new region
				regionID = curRegion++;
				regions.emplace_back(regionID, plot, 1, fenceSides);
				auto& newRegion = regions.back();
				newRegion.cells.push_back(make_pair(x, y));
				newRegion.fences = fenceList;


			} else { //update existing region
				auto& region = regions[regionID];
				++region.area;
				region.perimeter += fenceSides;
				region.cells.push_back(make_pair(x, y));
				region.fences.insert(region.fences.end(), fenceList.begin(), fenceList.end());
			}
			regionGrid.getCell(x, y) = regionID;

		//	cout << plot << " at (" << x << ", " << y << "): Fences " << fenceSides << ", Region " << regionID << '\n';
		}
	//	cout << "----\n";
	}
	if (partB) {
		Pos lastPos{ -1, -1 };
		for (auto& region : regions) {
			int fenceSides = 0;
			vector<Pos> northSides, eastSides, southSides, westSides;

			for (auto& fence : region.fences) {
				if (fence.side == 'N') northSides.emplace_back(fence.cell);
				else if (fence.side == 'E') eastSides.emplace_back(fence.cell);
				else if (fence.side == 'S') southSides.emplace_back(fence.cell);
				else if (fence.side == 'W') westSides.emplace_back(fence.cell);
			}

	/* We sort our list of fences. If we have two north walls that have different y values,
	they must belong to different sides. If they have the same y value, but the difference in x value
	is more than 1, there must have been a gap. So again, they are different sides.

	We have to repeat this for each direction. Sorting is different between vertical and horizontal fences.
	*/

			sort(northSides.begin(), northSides.end(), [](Pos a, Pos b) {
				return (a.second < b.second) || (a.second == b.second && a.first < b.first);
				});
			lastPos = make_pair(-1, -1);
			for (auto north : northSides) {
				if (north.second != lastPos.second || north.first - lastPos.first > 1) {
					fenceSides++;
				}
				lastPos = north;
			}

			sort(southSides.begin(), southSides.end(), [](Pos a, Pos b) {
				return (a.second < b.second || (a.second == b.second && a.first < b.first));
				});
			lastPos = make_pair(-1, -1);
			for (auto south : southSides) {
				if (south.second != lastPos.second || south.first - lastPos.first > 1) {
					fenceSides++;
				}
				lastPos = south;
			}

			sort(eastSides.begin(), eastSides.end(), [](Pos a, Pos b) {
				return (a.first < b.first) || (a.first == b.first && a.second < b.second);
				});
			lastPos = make_pair(-1, -1);
			for (auto east : eastSides) {
				if (east.first != lastPos.first || east.second - lastPos.second > 1) {
					fenceSides++;
				}
				lastPos = east;
			}
			sort(westSides.begin(), westSides.end(), [](Pos a, Pos b) {
				return (a.first < b.first) || (a.first == b.first && a.second < b.second);
				});
			lastPos = make_pair(-1, -1);
			for (auto west : westSides) {
				if (west.first != lastPos.first || west.second - lastPos.second > 1) {
					fenceSides++;
				}
				lastPos = west;
			}

			answer += region.area * fenceSides;
		}
	}
	else {
		for (auto& region : regions) {
			answer += region.area * region.perimeter;
		}
	}

	cout << "Answer: " << answer << endl;
}