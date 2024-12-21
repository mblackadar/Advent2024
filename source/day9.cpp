#include "Advent2024.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void day9(std::ifstream& inputFile, bool partB) {
	std::string origDiskMap;
	std::vector<int> blocks; //-1 is free
	int64_t checksum = 0;
	for (std::string line; std::getline(inputFile, line);) {
		origDiskMap = line;
		break;
	}
	bool fileBlock = true;
	const int freeID = -1;
	int fileID = 0;
	for (auto blockSize : origDiskMap) {
		int nextBlock = blockSize - '0';
		if (fileBlock) {
			blocks.insert(blocks.end(), nextBlock, fileID);
			fileID++;
			fileBlock = false;
		}
		else {
			blocks.insert(blocks.end(), nextBlock, freeID);
			fileBlock = true;
		}
	}

	//for part B, move the largest ID file first, and we only try once. Then calculate the sum like usual later.

	if (partB) {
		auto fileStart = blocks.rbegin();
		while (fileStart != blocks.rend()) {
			if (*fileStart == freeID) {
				++fileStart;
				continue;
			}
			auto endFile = std::find_if(fileStart, blocks.rend(), [&](int a) {
				return a != *fileStart;
				});
			int64_t numFile = std::distance(fileStart, endFile);

			auto freeStart = blocks.begin();
			while (freeStart != blocks.end() && *freeStart != *fileStart) {
				if (*freeStart != freeID) {
					++freeStart;
					continue;
				}
				auto endFree = std::find_if(freeStart, blocks.end(), [&](int a) {
					return a != freeID;
					});
				int64_t numFree = std::distance(freeStart, endFree);
				if (numFree >= numFile) {
					while (fileStart != endFile) {
						std::iter_swap(fileStart, freeStart);
						++fileStart;
						++freeStart;
					}
					//file copied
					break;
				}
				else { // free block too small, continue search
					freeStart += numFree;
				}
			}
			fileStart = endFile;
		}
	}

	int curOffset = 0;
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		if (*it == freeID) {

			for (auto fileIt = blocks.rbegin(); fileIt != std::make_reverse_iterator(it); ++fileIt) {
				if (*fileIt == freeID) continue;
				if (!partB) {
					std::iter_swap(it, fileIt);
					checksum += curOffset * *it;
					break;
				}
			}
		}
		else {
			checksum += curOffset * *it;
		}
		curOffset++;
	}
	cout << checksum << endl;
}