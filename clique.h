#ifndef CLIQUE_H
#define CLIQUE_H
#include "abstract_graph.h"

class Clique : public AbstractGraph {
 public:

  Clique();
  explicit Clique(int size);
  explicit Clique(const std::vector<std::vector<Edge>>& from);

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
  std::vector<std::vector<int>> connection_matrix_;
};

#endif //CLIQUE_H
