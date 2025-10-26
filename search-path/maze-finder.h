#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <limits>

typedef std::vector<std::vector<int>> grid_t;
typedef std::pair<int, int> cell_t;

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

bool isInBounds(grid_t grid, int row, int col)
{
    return grid.size() > row && grid[row].size() > col;
}

bool isNotVisited(cell_t cell, std::vector<cell_t> visited) {
    return std::find(visited.begin(), visited.end(), cell) == visited.end();
}


/**
 * TODO: define type
*/
bool maze_finder_knearest(std::string maze) {
    std::vector<std::vector<int>> grid = makeGrid(maze);
    size_t M = grid.size(), N = grid[M - 1].size(); // grid size
    
    cell_t start = { 0, 0 }; // left top
    cell_t dest = { M - 1, N - 1 }; // bottom right
    std::vector<cell_t> stack = { start };
    std::vector<cell_t> visited{ start };
    
    while (!stack.empty()) {
        cell_t test = stack.back();
        stack.pop_back();
        if (test == dest) {
            return true;
        }
        // south
        if (isInBounds(grid, test.first + 1, test.second) &&
            isNotWall(grid, test.first + 1, test.second) &&
            isNotVisited({ test.first + 1, test.second }, visited)) {
            stack.push_back({ test.first + 1, test.second });
            visited.push_back({ test.first + 1, test.second });
        }
        // east
        if (isInBounds(grid, test.first, test.second + 1) &&
            isNotWall(grid, test.first, test.second + 1) &&
            isNotVisited({ test.first, test.second + 1 }, visited)) {
            stack.push_back({ test.first, test.second + 1 });
            visited.push_back({ test.first, test.second + 1 });
        }
        // north
        if (isInBounds(grid, test.first - 1, test.second) &&
            isNotWall(grid, test.first - 1, test.second) &&
            isNotVisited({ test.first - 1, test.second }, visited)) {
            stack.push_back({ test.first - 1, test.second });
            visited.push_back({ test.first - 1, test.second });
        }
        // west
        if (isInBounds(grid, test.first, test.second - 1) &&
            isNotWall(grid, test.first, test.second - 1) &&
            isNotVisited({ test.first, test.second - 1 }, visited)) {
            stack.push_back({ test.first, test.second - 1 });
            visited.push_back({ test.first, test.second - 1 });
        }
    }
    
    return false;
}

bool maze_finder_minimal(std::string maze) {
    int size = 0;
    for(char c : maze)
        if( c == '\n') break;
        else size++;

    std::set<int> visited;
    visited.insert(0);
    std::vector<int> agenda;
    agenda.push_back(0);

    while( agenda.size() ){
        int current = agenda.back();
        agenda.pop_back();

        int up    = current - size - 1;
        int down  = current + size + 1;
        int left  = current - 1;
        int right = current + 1;

        int steps[] = {up, down, left, right};

        for(int step : steps) {
            if( step < 0) continue;
            if( step >= maze.size()) continue;
            if( visited.count(step)) continue;
            if( maze[step] != '.' )  continue;

            visited.insert(step);
            agenda.push_back(step);

            if(step == maze.size()-1 ) return true;
        }
    }
    return false;
}


bool maze_finder_smart(std::string& maze, int n, int row, int col){
  if(row == n-1 && col == n-1)
    return true;
  else if(row < 0 || col < 0 || row >= n || col >= n || maze[row*(n+1)+col]=='W')
    return false;
  else{
    maze[row*(n+1)+col] = 'W';
    return maze_finder_smart(maze, n, row-1, col) || maze_finder_smart(maze, n, row, col-1)
        || maze_finder_smart(maze, n, row+1, col) || maze_finder_smart(maze, n, row, col+1);
  }
}

bool maze_finder_smart(const std::string& maze) {
  std::string record{maze};
  return maze_finder_smart(record, (int)maze.find('\n'), 0, 0);
}