#ifndef ABSTRACT_GRAPH_H
#define ABSTRACT_GRAPH_H
#include <vector>
class AbstractGraph {
 public:
  struct Edge {
    int to;
    int length;
    Edge() : to(-1), length(-1) {}
    Edge(int new_to, int new_length)
        : to(new_to), length(new_length) {}
  };
  [[nodiscard]] int GetSize() const {
    return n_;
  }
  [[nodiscard]] virtual int GetEdgeLength(int from, int to) const = 0;
  [[nodiscard]] virtual std::vector<Edge> GetEdges(int from) const = 0;
  [[nodiscard]] virtual std::vector<Edge> GetAnyPath(int from, int to) const = 0;
  [[nodiscard]] virtual std::vector<Edge> GetShortestPath(int from, int to) const = 0;
  [[nodiscard]] virtual std::vector<std::vector<Edge>> GetShortestPaths(int from) const = 0;
 protected:
  int n_{};
};
#endif //ABSTRACT_GRAPH_H
