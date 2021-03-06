#include "algorithms/graph.hpp"

#include <algorithm>

namespace sge {

static void topologicialSortRec(std::vector<std::vector<u32>>& graph, u32 v,
                                std::vector<bool>& visited,
                                std::vector<u32>& stack) {
  visited[v] = true;
  for (u32 e : graph[v]) {
    if (!visited[e]) {
      topologicialSortRec(graph, e, visited, stack);
    }
  }
  stack.push_back(v);
}

std::vector<u32> topologicialSort(std::vector<std::vector<u32>>& graph) {
  u32 n = graph.size();
  for (std::vector<u32>& vec : graph) {
    for (u32 v : vec) {
      n = v > n ? v : n;
    }
  }
  graph.resize(n);  // ensure adj list are avaiable in the graph
  std::vector<bool> visited(n);
  std::vector<u32> stack(0);
  for (u32 v = 0; v < n; v++) {
    if (!visited[v]) {
      topologicialSortRec(graph, v, visited, stack);
    }
  }
  std::reverse(stack.begin(), stack.end());
  return stack;
}

std::vector<u32> selectiveReverseTopoligicalSort(
    std::vector<std::vector<u32>>& graph, std::vector<u32>& startNodes) {
  u32 n = graph.size();
  for (std::vector<u32>& vec : graph) {
    for (u32 v : vec) {
      n = v > n ? v : n;
    }
  }
  graph.resize(n);  // ensure adj list are avaiable in the graph
  std::vector<bool> visited(n);
  std::vector<u32> stack(0);
  for (u32 s : startNodes) {
    if (!visited[s]) {
      topologicialSortRec(graph, s, visited, stack);
    }
  }
  return stack;
}

std::vector<u32> selectiveTopoligicalSort(std::vector<std::vector<u32>>& graph,
                                          std::vector<u32>& startNodes) {
  // unnecessary copy!
  std::vector<u32> res = selectiveReverseTopoligicalSort(graph, startNodes);
  res.reserve(res.size());
  return res;
}

}  // namespace sge
