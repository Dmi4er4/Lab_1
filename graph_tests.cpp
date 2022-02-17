//
// Created by andrew on 13.02.22.
//

#include "graph.h"
#include "gtest/gtest.h"

TEST(Edge, Constructors) {
  const int kMaxN = 100;

  Graph::Edge empty_edge;
  ASSERT_EQ(empty_edge.length, -1);
  ASSERT_EQ(empty_edge.to, -1);

  for (int length = 1; length <= kMaxN; length++) {
    for (int to = 0; to < kMaxN; to++) {
      Graph::Edge edge(to, length);
      ASSERT_EQ(edge.length, length);
      ASSERT_EQ(edge.to, to);
    }
  }
}

TEST(Graph, Constructors) {
  const int kMaxN = 100;

  for (int n = 1; n <= kMaxN; n++) {
    Graph graph(n);
    ASSERT_EQ(graph.GetSize(), n);

    std::vector<std::vector<Graph::Edge>> new_graph;

    for (int i = 0; i < n; i++) {
      int pointer = 0;
      const std::vector<Graph::Edge>& edges = graph.GetEdges(i);
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

    Graph graph_from_other_constructor(new_graph);

    for (int i = 0; i < n; i++) {
      int pointer = 0;
      const std::vector<Graph::Edge>& edges =
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

TEST(Edge, GetAnyPath) {
  const int kMaxN = 50;

  for (int n = 1; n <= kMaxN; n++) {
    std::vector<std::vector<Graph::Edge>> edges(n);
    for (int i = 1; i < n; i++) {
      edges[i - 1].push_back(Graph::Edge(i - 0, 1));
      edges[i - 0].push_back(Graph::Edge(i - 1, 1));
    }

    Graph graph(edges);

    for (int from = 0; from < n; from++) {
      for (int to = 0; to < n; to++) {
        const std::vector<Graph::Edge>& any_path =
            graph.GetAnyPath(from, to);

        if (from == to) {
          ASSERT_EQ(any_path.size(), 0);
        } else if (from > to) {
          int vertex = from - 1;
          for (int i = 0; i < any_path.size(); i++) {
            ASSERT_EQ(any_path[i].to, vertex);
            ASSERT_EQ(any_path[i].length, 1);

            vertex--;
          }

          ASSERT_EQ(vertex, to - 1);
        } else {
          int vertex = from + 1;
          for (int i = 0; i < any_path.size(); i++) {
            ASSERT_EQ(any_path[i].to, vertex);
            ASSERT_EQ(any_path[i].length, 1);

            vertex++;
          }

          ASSERT_EQ(vertex, to + 1);
        }
      }
    }
  }
}

TEST(Edge, GetShortestPaths) {
  const int kMaxN = 50;

  for (int n = 1; n <= kMaxN; n++) {
    std::vector<std::vector<Graph::Edge>> edges(n);
    for (int i = 1; i < n; i++) {
      edges[i - 1].push_back(Graph::Edge(i - 0, i));
      edges[i - 0].push_back(Graph::Edge(i - 1, i));
    }

    Graph graph(edges);

    for (int from = 0; from < n; from++) {
      std::vector<std::vector<Graph::Edge>> paths =
          graph.GetShortestPaths(from);

      for (int to = 0; to < n; to++) {
        const std::vector<Graph::Edge>& any_path = paths[to];

        if (from == to) {
          ASSERT_EQ(any_path.size(), 0);
        } else if (from > to) {
          int vertex = from - 1;
          for (int i = 0; i < any_path.size(); i++) {
            ASSERT_EQ(any_path[i].to, vertex);
            ASSERT_EQ(any_path[i].length, vertex + 1);

            vertex--;
          }

          ASSERT_EQ(vertex, to - 1);
        } else {
          int vertex = from + 1;
          for (int i = 0; i < any_path.size(); i++) {
            ASSERT_EQ(any_path[i].to, vertex);
            ASSERT_EQ(any_path[i].length, vertex);

            vertex++;
          }

          ASSERT_EQ(vertex, to + 1);
        }
      }
    }
  }
}
