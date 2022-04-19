#ifndef GIT_FIRST_LAB_GRAPH_H
#define GIT_FIRST_LAB_GRAPH_H

#include "abstract_graph.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>

class Graph : public AbstractGraph {
 public:

  Graph();
  explicit Graph(const std::vector<std::vector<Edge>>& from);
  explicit Graph(int size);

  [[nodiscard]] int GetEdgeLength(int from, int to) const override;
  [[nodiscard]] std::vector<Edge> GetEdges(int from) const override;

  [[nodiscard]] std::vector<Edge> GetAnyPath(int from, int to) const override;
  [[nodiscard]] std::vector<Edge> GetShortestPath(int from, int to) const override;
  [[nodiscard]] std::vector<std::vector<Edge>> GetShortestPaths(int from) const override;

 private:
  struct Path {
    long long length;
    int to;

    Path();
    Path(long long len, int new_to);

    bool operator>(const Path& rhs) const;
  };
  std::vector<std::vector<Edge>> connections_;
};

#endif //GIT_FIRST_LAB_GRAPH_H
