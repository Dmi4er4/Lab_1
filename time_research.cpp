#include <chrono>
#include <iostream>
#include <random>
#include "gtest/gtest.h"
#include "traffic_manager.h"
#include "graph.h"
#include "clique.h"
#include "chain.h"

const long long kTimeConstant = 1'000'000;
const int kIterations = 100'000;
const int kMaxValue = 1'000'000;
const int kMaxWeight = 1'000;
// const int kSizes = 5;
// const int graph_sizes[kSizes] = {10, 20, 50, 100, 200};
const int kSizes = 1;
const int graph_sizes[kSizes] = {500};

TEST(Time, FullyConnectedGraph) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    Graph graph(n);

    std::vector<int> ones(n, 1);
    TrafficManager manager(&graph, ones, ones, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      int count = (graph_random() % n) + 1;

      manager.Transport(from, to, count);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for graph with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}

TEST(Time, Clique) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    Clique graph(n);

    std::vector<int> ones(n, 1);
    TrafficManager manager(&graph, ones, ones, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      int count = (graph_random() % n) + 1;

      manager.Transport(from, to, count);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for clique with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}

TEST(Time, Chain) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    Chain graph(n);

    std::vector<int> big(n, kMaxValue);
    ChainTrafficManager manager(&graph, big, big, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      if (from > to) {
        std::swap(from, to);
      }

      manager.Transport(from, to, 1);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for chain with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}



TEST(Time, RandomFullyConnectedGraph) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    std::vector<std::vector<AbstractGraph::Edge>> connections;
    connections.resize(n);

    for (int i = 0; i < n; i++) {
      connections[i].resize(n);
      connections[i][i] = AbstractGraph::Edge(i, 0);

      for (int j = 0; j < i; j++) {
        int weight = (graph_random() % kMaxWeight) + 1;

        connections[i][j] = AbstractGraph::Edge(j, weight);
        connections[j][i] = AbstractGraph::Edge(i, weight);
      }
    }

    Graph graph(connections);

    std::vector<int> ones(n, 1);
    TrafficManager manager(&graph, ones, ones, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      int count = (graph_random() % n) + 1;

      manager.Transport(from, to, count);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for random graph with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}

TEST(Time, RandomClique) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    std::vector<std::vector<AbstractGraph::Edge>> connections;
    connections.resize(n);

    for (int i = 0; i < n; i++) {
      connections[i].resize(n);
      connections[i][i] = AbstractGraph::Edge(i, 0);

      for (int j = 0; j < i; j++) {
        int weight = (graph_random() % kMaxWeight) + 1;

        connections[i][j] = AbstractGraph::Edge(j, weight);
        connections[j][i] = AbstractGraph::Edge(i, weight);
      }
    }

    Clique graph(connections);

    std::vector<int> ones(n, 1);
    TrafficManager manager(&graph, ones, ones, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      int count = (graph_random() % n) + 1;

      manager.Transport(from, to, count);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for random clique with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}

TEST(Time, RandomChain) {
  std::mt19937 graph_random(416);

  for (int size_type = 0; size_type < kSizes; size_type++) {
    long long start_time = std::chrono::system_clock().now().time_since_epoch().count();

    int n = graph_sizes[size_type];
    std::vector<std::vector<AbstractGraph::Edge>> connections;
    connections.resize(n);

    for (int i = 0; i < n; i++) {
      if (i + 1 < n) {
        int weight = (graph_random() % kMaxWeight) + 1;
        connections[i].push_back(AbstractGraph::Edge(i + 1, weight));
      }
    }

    Chain graph(connections);

    std::vector<int> big(n, kMaxValue);
    ChainTrafficManager manager(&graph, big, big, 1);

    for (int i = 0; i < kIterations; i++) {
      int from = graph_random() % n;
      int to = graph_random() % n;
      while (from == to) {
        to = graph_random() % n;
      }
      if (from > to) {
        std::swap(from, to);
      }

      manager.Transport(from, to, 1);
    }

    long long end_time = std::chrono::system_clock().now().time_since_epoch().count();
    std::cout << "for random chain with size " << n << " time is " <<
              (end_time - start_time) / kTimeConstant << " ms\n";
  }
}