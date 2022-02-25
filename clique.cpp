#include "clique.h"
#include <cassert>

Clique::Clique() {
  n_ = 0;
}
Clique::Clique(int size) {
  n_ = size;
  connection_matrix_.resize(size);
  for (int i = 0; i < size; i++) {
    connection_matrix_[i].resize(size, 1);
  }
}
Clique::Clique(const std::vector<std::vector<Edge>>& from) {
  n_ = from.size();
  connection_matrix_.resize(n_);
  for (int i = 0; i < n_; i++) {
    connection_matrix_[i].resize(n_, 0);
  }
  for (int i = 0; i < n_; i++) {
    assert(from[i].size() == n_ - 1);
    for (int j = 0; j < from[i].size(); j++) {
      connection_matrix_[i][from[i][j].to] = from[i][j].length;
    }
  }
}
int Clique::GetEdgeLength(int from, int to) const {
  assert(from >= 0 && from < n_);
  return connection_matrix_[from][to];
}
std::vector<AbstractGraph::Edge> Clique::GetEdges(int from) const {
  assert(from >= 0 && from < n_);
  std::vector<AbstractGraph::Edge> result;
  for (int i = 0; i < n_; i++) {
    if (i != from) {
      result.emplace_back(i, connection_matrix_[from][i]);
    }
  }
  return result;
}
std::vector<AbstractGraph::Edge> Clique::GetAnyPath(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);
  std::vector<AbstractGraph::Edge> result;
  if (from != to) {
    result.emplace_back(to, connection_matrix_[from][to]);
  }
  return result;
}
std::vector<AbstractGraph::Edge> Clique::GetShortestPath(int from,
                                                         int to) const {
  return GetAnyPath(from, to);
}
std::vector<std::vector<AbstractGraph::Edge>> Clique::GetShortestPaths(int from) const {
  std::vector<std::vector<AbstractGraph::Edge>> result(n_);
  for (int i = 0; i < n_; i++) {
    result[i] = GetShortestPath(from, i);
  }
  return result;
}
