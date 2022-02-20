//
// Created by andrew on 13.02.22.
//

#ifndef GIT_FIRST_LAB_GRAPH_H
#define GIT_FIRST_LAB_GRAPH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
 public:
  struct Edge {
    int to;
    int length;

    Edge();
    Edge(int new_to, int new_length);
  };

  Graph();
  explicit Graph(std::vector<std::vector<Edge>> from);
  explicit Graph(int size);

  int GetEdgeLength(int from, int to);
  const std::vector<Edge>& GetEdges(int from);
  int GetSize();

  std::vector<Edge> GetAnyPath(int from, int to);
  std::vector<Edge> GetShortestPath(int from, int to);
  std::vector<std::vector<Edge>> GetShortestPaths(int from);

 private:
  struct Path {
    long long length;
    int to;

    Path();
    Path(long long len, int new_to);

    bool operator>(const Path& rhs) const;
  };

  int n_;
  std::vector<std::vector<Edge>> connections_;
};

#endif //GIT_FIRST_LAB_GRAPH_H
