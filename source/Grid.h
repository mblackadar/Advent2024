#pragma once

#include <vector>
#include <cassert>
#include <fstream>
#include <string>

template<typename T>
class Grid {
public:

	void initialize(int w, int h, T def = {}) {
		width = w;
		height = h;
		cells.resize(w * h, def);
	}

	bool isValid(int x, int y) const {
		return x >= 0 && x < width && y >= 0 && y < height;
	}
	bool isValid(std::pair<int, int> pos) const {
		return isValid(pos.first, pos.second);
	}

	T& getCell(int x, int y) {
		assert(isValid(x, y));
		return cells[y * width + x];
	}
	const T& getCell(int x, int y) const {
		assert(isValid(x, y));
		return cells[y * width + x];
	}
	T& getCell(std::pair<int, int> pos) {
		return getCell(pos.first, pos.second);
	}
	const T& getCell(std::pair<int, int> pos) const {
		return getCell(pos.first, pos.second);
	}

	void initFromFile(std::ifstream& inputFile) {
		int maxWidth = 0;
		std::vector<std::string> lines;
		for (std::string line; std::getline(inputFile, line);) {
			int rowWidth = static_cast<int>(line.size());
			if (rowWidth > maxWidth) {
				maxWidth = rowWidth;
			}
			lines.push_back(line);
		}
		initialize(maxWidth, static_cast<int>(lines.size()));

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				getCell(x, y) = lines[y][x];
			}
		}
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	int width = 0;
	int height = 0;
	std::vector<T> cells;
};