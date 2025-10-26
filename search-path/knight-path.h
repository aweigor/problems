#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <limits>

struct node {
    int score;
    int x;
    int y;
    bool visited;
    bool valid() {
        return x < 8 && x >= 0 && y < 8 && y >= 0;
    };
};

node* getNearest(std::vector<node> &graph) {
    if (!graph.size()) {
        return nullptr;
    }
    node *nearest = nullptr;
    for (auto &node: graph) {
        if (!node.visited && node.valid() && (nearest == nullptr || nearest->score > node.score)) {
            nearest = &node;
        }
    }
    return nearest;
};

node& findOrCreateNode(std::vector<node> &graph, int x, int y) {
    for (auto& n : graph) {
        if (n.x == x && n.y == y)
            return n;
    }
    node newNode{MAX, x, y, false};
    graph.push_back(newNode);
    return graph.back();
};

const int MAX = std::numeric_limits<int>::max();

int knight_part_hard(std::string start, std::string finish) {
    
    if (start.size() < 2 || finish.size() < 2)
        return -1;
    
    node startNode{0, start.at(0) - 'a', start.at(1) - '1', false};
    node finishNode{MAX, finish.at(0) - 'a', finish.at(1) - '1', false};
    node *currentNode;
    std::vector<node> graph{startNode, finishNode};
    
    while (true) {
        currentNode = getNearest(graph);
        if (getNearest(graph) == nullptr)
            return 0;
        
        int x = currentNode->x;
        int y = currentNode->y;
        int score = currentNode->score;
        
        std::pair<int, int> adjacent[] = {
            std::pair<int, int>(x + 1, y + 2),
            std::pair<int, int>(x + 2, y + 1),
            std::pair<int, int>(x + 1, y - 2),
            std::pair<int, int>(x + 2, y - 1),
            std::pair<int, int>(x - 1, y + 2),
            std::pair<int, int>(x - 2, y + 1),
            std::pair<int, int>(x - 1, y - 2),
            std::pair<int, int>(x - 2, y - 1)
        };
        
        for(std::pair<int, int> &coord : adjacent) {
            node& n = findOrCreateNode(graph, coord.first, coord.second);
            if (n.valid() && !n.visited) {
                if (n.score > score + 1)
                    n.score = score + 1;
            }
        }
        
        if (finishNode.x == x && finishNode.y == y) {
            return score;
        }
        
        currentNode->visited = true;
    }
    
    return -1;
}




int knight_path_simple(std::string start, std::string finish) {
  static char xx[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
  static char yy[8] = {2, 2, 1, -1, -2, -2, -1, 1};
  std::queue<std::pair<std::string,int>> q;
  q.push(std::pair<std::string,int>(start,0));
  int t;
  while (t=q.size())
    while (t--) {
        std::pair<std::string,int> p = q.front(); q.pop();
    printf("%s\n", p.first.c_str());
        if (p.first == finish)
            return p.second;
        for (int i=0; i < 8; ++i) {
            std::string now = p.first;
            now[0] += xx[i];
            now[1] += yy[i];
            if (now[0] < 'a' || now[0] > 'h' || now[1] < '1' || now[1] > '8') continue;
            q.push(std::pair<std::string,int>(now, p.second+1));
        }
    }
  return 0;
}

/**
 * 8by8 matrix holds the number of RELATIVE moves to get to the cell of interest
 * from the cell with value 0. The matrix is just a quarter part of centre-symmetrical
 * (around point (0,0)) matrix. And if you start at the corner you should make 2 additional
 * moves to get to the destination point: see for ex. point (1.1) - if you are in the corner
 * you have to make 4 not 2 moves. But if you are not in the corner you first step
 * to imaginary (-1,2) point and then to (1,1) point. Hope I was helpful.
 */
int knight_path_table(std::string start, std::string finish) {
  const int moves[8][8]
  {{0,3,2,3,2,3,4,5},
   {3,2,1,2,3,4,3,4},
   {2,1,4,3,2,3,4,5},
   {3,2,3,2,3,4,3,4},
   {2,3,2,3,4,3,4,5},
   {3,4,3,4,3,4,5,4},
   {4,3,4,3,4,5,4,5},
   {5,4,5,4,5,4,5,6}};
  
  size_t idx = abs(finish[0]-start[0]);
  size_t idy = abs(finish[1]-start[1]);
  size_t corner = 0;
  
  if (idx*idy==1){ //Corner cases
  if ((start=="a1")||(finish=="a1")||(start=="h1")||(finish=="h1")||
      (start=="a8")||(finish=="a8")||(start=="h8")||(finish=="h8"))
    corner = 2;
  }
  
  return moves[idy][idx]+corner;
}
