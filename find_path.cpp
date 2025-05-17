//
//  find_path.cpp
//  algorithms
//
//  Created by Igor on 17.05.2025.
//

#include <string>
#include <vector>
#include <iostream>

#include "find_path.hpp"

typedef std::vector<std::vector<int>> grid_t;

grid_t makeGrid(std::string maze) {
    grid_t grid{{}};
    int i = 0;
    for (auto &c: maze) {
        if (c == '\n') {
            i++;
            grid.push_back({});
            continue;
        }
        grid[i].push_back(c == '.');
    }
    return grid;
}

bool isNotWall(grid_t grid, int row, int col)
{
    return grid[row][col] == 1;
}

bool isInGrid(int row, int col, grid_t grid)
{
    return grid.size() > row && grid[row].size() > col;
}

bool path_finder(std::string maze) {
    std::vector<std::vector<int>> grid = makeGrid(maze);
    int i = 0, j = 0;
    
    return false;
}
