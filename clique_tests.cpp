#include "clique.h"
#include "gtest/gtest.h"

TEST(Clique, Constructors) {
  const int kMaxN = 100;

  for (int n = 1; n <= kMaxN; n++) {
    Clique graph(n);
    ASSERT_EQ(graph.GetSize(), n);

    std::vector<std::vector<AbstractGraph::Edge>> new_graph;

    for (int i = 0; i < n; i++) {
      int pointer = 0;
      const std::vector<AbstractGraph::Edge>& edges = graph.GetEdges(i);
      new_graph.push_back(edges);

      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }

        ASSERT_EQ(edges[pointer].to, j);
        ASSERT_EQ(edges[pointer].length, 1);
        pointer++;
      }
    }

    Clique graph_from_other_constructor(new_graph);

    for (int i = 0; i < n; i++) {
      int pointer = 0;
      const std::vector<AbstractGraph::Edge>& edges =
          graph_from_other_constructor.GetEdges(i);

      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }

        ASSERT_EQ(edges[pointer].to, j);
        ASSERT_EQ(edges[pointer].length, 1);
        pointer++;
      }
    }
  }
}

TEST(Clique, GetPath) {
  const int kMaxN = 100;

  for (int n = 1; n <= kMaxN; n++) {
    Clique graph(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        std::vector<AbstractGraph::Edge> any_path = graph.GetAnyPath(i, j);
        std::vector<AbstractGraph::Edge>
            shortest_path = graph.GetShortestPath(i, j);
        std::vector<AbstractGraph::Edge> for_check;
        if (i != j) {
          for_check.emplace_back(j, 1);
        }
        ASSERT_EQ(any_path.size(), for_check.size());
        ASSERT_EQ(shortest_path.size(), for_check.size());
        if (!for_check.empty()) {
          ASSERT_EQ(any_path[0].to, for_check[0].to);
          ASSERT_EQ(any_path[0].length, for_check[0].length);
          ASSERT_EQ(shortest_path[0].to, for_check[0].to);
          ASSERT_EQ(shortest_path[0].length, for_check[0].length);
        }
      }
  }
}
