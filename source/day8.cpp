#include "Advent2024.h"
#include "Grid.h"

#include <iostream>
using namespace std;

void day8(std::ifstream& inputFile, bool partB) {
	int64_t answer = 0;
	Grid<char> city, marked;
	city.initFromFile(inputFile);
	int height = city.getHeight();
	int width = city.getWidth();
	marked.initialize(width, height);

	char curChar, nextChar;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			curChar = city.getCell(x, y);
			if (!std::isalnum(curChar)) continue;

			for (int nextY = 0; nextY < height; nextY++) {
				for (int nextX = 0; nextX < width; nextX++) {
					if (nextX == x && nextY == y) continue;

					nextChar = city.getCell(nextX, nextY);
					if (nextChar != curChar) continue;

					int diffX = nextX - x;
					int diffY = nextY - y;

					if (partB) {
						if (!(marked.getCell(x, y) == '#')) {
							marked.getCell(x, y) = '#';
							answer++;
						}
						if (!(marked.getCell(nextX, nextY) == '#')) {
							marked.getCell(nextX, nextY) = '#';
							answer++;
						}

						int testX = nextX + diffX;
						int testY = nextY + diffY;
						while (city.isValid(testX, testY)) {
							if (!(marked.getCell(testX, testY) == '#')) {
								marked.getCell(testX, testY) = '#';
								answer++;
							}
							testX += diffX;
							testY += diffY;
						}
						testX = x - diffX;
						testY = y - diffY;

						while (city.isValid(testX, testY)) {
							if (!(marked.getCell(testX, testY) == '#')) {
								marked.getCell(testX, testY) = '#';
								answer++;
							}
							testX -= diffX;
							testY -= diffY;
						}
					}
					else {
						if (city.isValid(nextX + diffX, nextY + diffY)) {
							if (!(marked.getCell(nextX + diffX, nextY + diffY) == '#')) {
								marked.getCell(nextX + diffX, nextY + diffY) = '#';
								answer++;
							}
						}
						if (city.isValid(x - diffX, y - diffY)) {
							if (!(marked.getCell(x - diffX, y - diffY) == '#')) {
								marked.getCell(x - diffX, y - diffY) = '#';
								answer++;
							}
						}
					}
				}
			}
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			char markedChar = marked.getCell(x, y);
			cout << (markedChar ? markedChar : '.');
		}
		cout << endl;
	}

	cout << answer << endl;
}