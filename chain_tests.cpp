#include "chain.h"
#include "gtest/gtest.h"

TEST(Chain, Constructors) {
  const int kMaxN = 100;

  for (int n = 1; n <= kMaxN; n++) {
    Chain graph(n);
    ASSERT_EQ(graph.GetSize(), n);

    for (int i = 0; i < n; i++) {
      int pointer = 0;
      const std::vector<AbstractGraph::Edge>& edges = graph.GetEdges(i);
      if (i == n - 1) {
        ASSERT_EQ(edges.size(), 0);
      } else {
        ASSERT_EQ(edges.size(), 1);
        ASSERT_EQ(edges[0].to, i + 1);
        ASSERT_EQ(edges[0].length, 1);
      }
    }
  }
}

TEST(Chain, GetPath) {
  const int kMaxN = 100;

  for (int n = 1; n <= kMaxN; n++) {
    Chain graph(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        std::vector<AbstractGraph::Edge> any_path = graph.GetAnyPath(i, j);
        std::vector<AbstractGraph::Edge>
            shortest_path = graph.GetShortestPath(i, j);
        std::vector<AbstractGraph::Edge> for_check;
        if (j >= i) {
          ASSERT_EQ(any_path.size(), j - i);
          ASSERT_EQ(shortest_path.size(), j - i);
          for (int k = i + 1; k <= j; k++) {
            ASSERT_EQ(any_path[k - i - 1].to, k);
            ASSERT_EQ(any_path[k - i - 1].length, 1);
            ASSERT_EQ(shortest_path[k - i - 1].to, k);
            ASSERT_EQ(shortest_path[k - i - 1].length, 1);
          }
        } else {
          ASSERT_EQ(any_path.size(), 0);
          ASSERT_EQ(shortest_path.size(), 0);
        }
      }
  }
}
