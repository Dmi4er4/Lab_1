#include "clique.h"
#include <cassert>
#include <limits>
#include <queue>
#include <algorithm>

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
Clique::Path::Path() : length(-1), to(-1) {}

Clique::Path::Path(long long len, int new_to) : length(len), to(new_to) {}

bool Clique::Path::operator>(const Path& rhs) const {
  return (length > rhs.length);
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
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);

  const long long kInfinity = std::numeric_limits<long long>::max();
  std::vector<long long> distance(n_, kInfinity);
  std::vector<Edge> previous(n_);

  distance[from] = 0;
  std::priority_queue<Clique::Path, std::vector<Path>, std::greater<>>
      sorted_paths;
  sorted_paths.push(Path(distance[from], from));

  while (!sorted_paths.empty()) {
    Path current_path = sorted_paths.top();
    sorted_paths.pop();
    int vertex = current_path.to;

    if (distance[vertex] != current_path.length) {
      continue;
    }

    if (vertex == to) {
      std::vector<Edge> result;
      int current_location = to;

      while (current_location != from) {
        result.emplace_back(current_location,
                            previous[current_location].length);
        current_location = previous[current_location].to;
      }

      std::reverse(result.begin(), result.end());
      return result;
    }
    for (int i = 0; i < n_; i++) {
      if (i == vertex) {
        continue;
      }
      if (distance[i] > distance[vertex] + connection_matrix_[vertex][i]) {
        distance[i] = distance[vertex] + connection_matrix_[vertex][i];
        previous[i] = Edge(vertex, connection_matrix_[vertex][i]);
        sorted_paths.push(Path(distance[i], i));
      }
    }
  }

  return {};
}
std::vector<std::vector<AbstractGraph::Edge>> Clique::GetShortestPaths(int from) const {
  assert(from >= 0 && from < n_);

  std::vector<std::vector<Edge>> result;

  const long long kInfinity = std::numeric_limits<long long>::max();
  std::vector<long long> distance(n_, kInfinity);
  std::vector<Edge> previous(n_);

  distance[from] = 0;
  std::priority_queue<Path, std::vector<Path>, std::greater<>> sorted_paths;
  sorted_paths.push(Path(distance[from], from));

  while (!sorted_paths.empty()) {
    Path current_path = sorted_paths.top();
    sorted_paths.pop();
    int vertex = current_path.to;

    if (distance[vertex] != current_path.length) {
      continue;
    }
    for (int i = 0; i < n_; i++) {
      if (i == vertex) {
        continue;
      }
      if (distance[i] > distance[vertex] + connection_matrix_[vertex][i]) {
        distance[i] = distance[vertex] + connection_matrix_[vertex][i];
        previous[i] = Edge(vertex, connection_matrix_[vertex][i]);
        sorted_paths.push(Path(distance[i], i));
      }
    }
  }

  for (int to = 0; to < n_; to++) {
    std::vector<Edge> to_result;
    int current_location = to;

    while (current_location != from) {
      to_result.emplace_back(current_location,
                             previous[current_location].length);
      current_location = previous[current_location].to;
    }

    std::reverse(to_result.begin(), to_result.end());
    result.push_back(to_result);
  }
  return result;
}
