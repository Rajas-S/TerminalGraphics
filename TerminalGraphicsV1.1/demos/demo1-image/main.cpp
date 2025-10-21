#include <iostream>
#include <fstream>
#include "TGL1.h"
#include <vector>
#include <string>
#include <sstream>

using namespace tgl;

int main() {
	TerminalGraphics tgl;
	tgl.setWindow(400, 400);
	tgl.setTileset(" `'.,-~_:;^+=*<>iv!lI?/|()1t{}[]rjfxnuczmwqpdbkhao#MW&8%B@$02345679ACDEFGHJKLNOPQRSTUVXYZegsy");
	std::ifstream infile("imageArray.txt");
	std::vector<std::vector < int >> array;
	std::string line;
	while (std::getline(infile, line)) {
		std::vector<int> row;
		std::istringstream iss(line);
		int value;
		while (iss >> value) {
			row.push_back(value);
		}
		array.push_back(row);
	}

	for (int j = 0; j < array.size();j++) {
		for (int i = 0; i < array[0].size();i++) {
			tgl.grid[i][j] = array[j][i];
		}
	}

	tgl.render();

	return 0;
}
