#ifndef CHAIN_H
#define CHAIN_H
#include "abstract_graph.h"

class Chain : public AbstractGraph{
 public:

  Chain();
  explicit Chain(int size);
  explicit Chain(const std::vector<std::vector<Edge>>& from);

  [[nodiscard]] int GetEdgeLength(int from, int to) const override;
  [[nodiscard]] std::vector<Edge> GetEdges(int from) const override;

  [[nodiscard]] std::vector<Edge> GetAnyPath(int from, int to) const override;
  [[nodiscard]] std::vector<Edge> GetShortestPath(int from, int to) const override;
  [[nodiscard]] std::vector<std::vector<Edge>> GetShortestPaths(int from) const override;

 private:
  std::vector<Edge> connections_;
};
#endif //CHAIN_H
