#include "chain.h"
#include <cassert>

Chain::Chain() {
  n_ = 0;
}
Chain::Chain(int size) {
  n_ = size;
  connections_.resize(size);
  for (int i = 0; i < size; i++) {
    if (i == size - 1) {
      connections_[i] = {-1, 1};
    } else {
      connections_[i] = {i + 1, 1};
    }
  }
}
Chain::Chain(const std::vector<std::vector<Edge>>& from) {
  n_ = from.size();
  for (int i = 0; i < n_; i++) {
    assert(from[i].size() <= 1);
    connections_[i] = from[i].empty() ? Edge(-1, 1) : from[i][0];
  }
}
int Chain::GetEdgeLength(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);
  return connections_[from].to == to ? connections_[from].length : 0;
}
std::vector<AbstractGraph::Edge> Chain::GetEdges(int from) const {
  assert(from >= 0 && from < n_);
  std::vector<AbstractGraph::Edge> result;
  if (connections_[from].to != -1) {
    result.push_back(connections_[from]);
  }
  return result;
}
std::vector<AbstractGraph::Edge> Chain::GetAnyPath(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);
  std::vector<AbstractGraph::Edge> result;
  while (from != to && from != -1) {
    result.push_back(connections_[from]);
    from = connections_[from].to;
  }
  return from == to ? result : std::vector<AbstractGraph::Edge>();
}
std::vector<AbstractGraph::Edge> Chain::GetShortestPath(int from,
                                                        int to) const {
  return GetAnyPath(from, to);
}
std::vector<std::vector<AbstractGraph::Edge>> Chain::GetShortestPaths(int from) const {
  std::vector<std::vector<AbstractGraph::Edge>> result(n_);
  for (int i = 0; i < n_; i++) {
    result[i] = GetShortestPath(from, i);
  }
  return result;
}
