// Daily 200 Intermediate CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

struct Tile
{
	char tileChar;
	int x, y, width = 1, heigth = 1;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	os << tile.width << " by " << tile.heigth << " tile of character '" << tile.tileChar << "' located at (" << tile.x << ", " << tile.y << ")";
	return os;
}

int width, height;

std::vector<Tile *> tileCollection;

inline int index(int row, int column) {
	return row * width + column;
}

Tile* handleRead(char c, Tile* left, Tile* above, int row, int column) {
	Tile* current = nullptr;

	bool leftAvailable = left != nullptr;
	bool leftSame = leftAvailable && left->tileChar == c;

	bool aboveAvailable = above != nullptr;
	bool aboveSame = aboveAvailable && above->tileChar == c;

	if (leftSame)
	{
		current = left;
		current->width = (column - current->x) + 1;
	}

	if (aboveSame)
	{
		current = above;
		current->heigth = (row - current->y) + 1;
	}

	if (!(leftSame || aboveSame))
	{
		current = new Tile();
		current->tileChar = c;
		current->x = column;
		current->y = row;
		tileCollection.push_back(current);
	}

	return current;
}

int main() {
	std::cin >> width >> height;
	Tile **tiles = new Tile*[width * height];

	char c;
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			std::cin >> c;
			if (c != '.')
			{
				if (row == 0 && column == 0)
				{
					Tile t;
					t.x = 0;
					t.y = 0;
					t.tileChar = c;

					tiles[index(row, column)] = &t;
					tileCollection.push_back(&t);

				}
				else
				{
					tiles[index(row, column)] = handleRead(c, (column == 0) ? nullptr : tiles[index(row, column - 1)], (row == 0) ? nullptr : tiles[index(row - 1, column)], row, column);
				}
			}
			else
			{
				tiles[index(row, column)] = nullptr;
			}
		}
	}

	for (auto tile : tileCollection)
	{
		std::cout << *tile << std::endl;
	}

	return 0;
}