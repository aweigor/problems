#pragma once

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void print_vector(std::vector<int> vec) {
  for (auto &it: vec) {
    std::cout << it << ",";
  }
  std::cout << "\n";
}

int sumVector(std::vector<int> vec) 
{
  int result = 0;
  for (auto &i: vec) {
    result += i*i;
  }
  return result;
}

/* Decompose target number's square into possible unique integer squares
 * Finding path problem, where edges are the field of integers
 * The final state is the path with edges with sum equals to target's value
 * */
void decompose_recursive(int target, int current, std::vector<int> &path, std::vector<std::vector<int>> &result) 
{
  int currentSum = sumVector(path);
  if (currentSum == target * target) {
    result.push_back(path);
    return;
  }
  if (currentSum > target * target) {
    return;
  }
  while (current < target) {
    path.push_back(current);
    decompose_recursive(target, current + 1, path, result);
    path.pop_back();
    current += 1;
  }
}


/* Same as decompose_recursive, but returns first(!) discovered sequence from end
 *
 * */
void decompose_recursive_first_from_end(int target, int current, std::vector<int> &path, std::vector<std::vector<int>> &result) {
  if (!result.empty()) {
    return;
  }
  int currentSum = sumVector(path);
  if (currentSum == target * target) {
    result.push_back(path);
    return;
  }
  if (currentSum > target * target) {
    return;
  }
  while (current > 0) {
    path.push_back(current);
    decompose_recursive_first_from_end(target, current - 1, path, result);
    path.pop_back();
    current -= 1;
  }
}

static void decompose_iterative_first_from_end(int target, std::vector<std::vector<int>> &result) {
    struct State {
        int current;
        std::vector<int> path;
    };
    
    std::stack<State> stack;
    stack.push({target - 1, {}});
    
    while (!stack.empty()) {
        State state = stack.top();
        stack.pop();
        
        int current = state.current;
        std::vector<int> path = state.path;

        print_vector(path);
        
        int currentSum = sumVector(path);
        
        if (currentSum == target * target) {
            result.push_back(path);
            return;
        }
        if (currentSum > target * target) {
            continue;
        }
        
        for (int i = 1; i <= current; i++) {
            std::vector<int> new_path = path;
            new_path.push_back(i);
            stack.push({i - 1, new_path});
        }
    }
}

std::vector<int> decompose(int n) {
  std::vector<std::vector<int>> result;
  //decompose_recursive(n, 1, path, result);
  //decompose_recursive_first_from_end(n, n-1, path, result);
  decompose_iterative_first_from_end(n, result);


  for (auto & seq: result) {
    print_vector(seq);
  }

  std::vector<int> output{};
  if (!result.empty()) {
    output = result.at(0);
  }

  std::reverse(output.begin(), output.end());
  return output;
}
