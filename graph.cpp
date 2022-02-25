#include "graph.h"

Graph::Graph() {
  n_ = 0;
}

Graph::Graph(const std::vector<std::vector<Edge>>& from) : connections_(from) {
  n_ = from.size();
}

Graph::Graph(int size){
  n_ = size;
  connections_.resize(n_);

  for (int i = 0; i < n_; i++) {
    for (int j = 0; j < n_; j++) {
      if (i == j) {
        continue;
      }

      connections_[i].push_back(Edge(j, 1));
    }
  }
}

int Graph::GetEdgeLength(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);

  for (Edge edge: connections_[from]) {
    if (edge.to == to) {
      return edge.length;
    }
  }
  return 0;
}

std::vector<Graph::Edge> Graph::GetEdges(int from) const {
  assert(from >= 0 && from < n_);
  return connections_[from];
}

std::vector<Graph::Edge> Graph::GetAnyPath(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);

  std::vector<bool> visited(n_, false);
  std::vector<Edge> previous(n_);

  visited[from] = true;
  std::queue<int> visited_list;

  visited_list.push(from);
  while (!visited_list.empty()) {
    int vertex = visited_list.front();
    visited_list.pop();

    for (Edge edge: connections_[vertex]) {
      if (!visited[edge.to]) {
        visited[edge.to] = true;
        previous[edge.to] = Edge(vertex, edge.length);
        visited_list.push(edge.to);

        if (edge.to == to) {
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
      }
    }
  }

  return {};
}

std::vector<Graph::Edge> Graph::GetShortestPath(int from, int to) const {
  assert(from >= 0 && from < n_);
  assert(to >= 0 && to < n_);

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

    for (Edge edge: connections_[vertex]) {
      if (distance[edge.to] > distance[vertex] + edge.length) {
        distance[edge.to] = distance[vertex] + edge.length;
        previous[edge.to] = Edge(vertex, edge.length);
        sorted_paths.push(Path(distance[edge.to], edge.to));
      }
    }
  }

  return {};
}

std::vector<std::vector<Graph::Edge>> Graph::GetShortestPaths(int from) const {
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

    for (Edge edge: connections_[vertex]) {
      if (distance[edge.to] > distance[vertex] + edge.length) {
        distance[edge.to] = distance[vertex] + edge.length;
        previous[edge.to] = Edge(vertex, edge.length);
        sorted_paths.push(Path(distance[edge.to], edge.to));
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

Graph::Path::Path() : length(-1), to(-1) {}

Graph::Path::Path(long long len, int new_to) : length(len), to(new_to) {}

bool Graph::Path::operator>(const Path& rhs) const {
  return (length > rhs.length);
}
