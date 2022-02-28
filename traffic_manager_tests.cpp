#include "gtest/gtest.h"
#include "traffic_manager.h"
#include "graph.h"
#include "clique.h"
#include "chain.h"

// Graph tests
TEST(TrafficManager, GraphConstructorsGettersSetters) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 15);
  EXPECT_EQ(manager.GetTotalVehicles(), 15);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);

  manager.SetVehicle(5, 4);
  manager.SetBunsAmount(5, 0);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 19);
  EXPECT_EQ(manager.GetTotalVehicles(), 19);
  buns_amounts[0] = 5;
  vehicles[4] = 5;
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, GraphMoveVehicles) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  int transport_time = manager.MoveVehicles(0, 3, 3);
  EXPECT_EQ(transport_time, 1);
  vehicles[3] += 3;
  vehicles[0] -= 3;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, GraphTransport) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  int transport_time = manager.Transport(4, 1, 4);
  EXPECT_EQ(transport_time, 2);
  buns_amounts[1] += 4;
  buns_amounts[4] -= 4;
  vehicles[0] -= 3;
  vehicles[4] -= 1;
  vehicles[1] += 4;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
}


// Clique tests
TEST(TrafficManager, CliqueConstructorsGettersSetters) {
  Clique full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 15);
  EXPECT_EQ(manager.GetTotalVehicles(), 15);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);

  manager.SetVehicle(5, 4);
  manager.SetBunsAmount(5, 0);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 19);
  EXPECT_EQ(manager.GetTotalVehicles(), 19);
  buns_amounts[0] = 5;
  vehicles[4] = 5;
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, CliqueMoveVehicles) {
  Clique full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  int transport_time = manager.MoveVehicles(0, 3, 3);
  EXPECT_EQ(transport_time, 1);
  vehicles[3] += 3;
  vehicles[0] -= 3;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, CliqueTransport) {
  Clique full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(&full_graph, buns_amounts, vehicles, 1);
  int transport_time = manager.Transport(4, 1, 4);
  EXPECT_EQ(transport_time, 2);
  buns_amounts[1] += 4;
  buns_amounts[4] -= 4;
  vehicles[0] -= 3;
  vehicles[4] -= 1;
  vehicles[1] += 4;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
}


// Chain tests
TEST(TrafficManager, ChainConstructorsGettersSetters) {
  Chain chain(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  ChainTrafficManager manager(&chain, buns_amounts, vehicles, 1);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 15);
  EXPECT_EQ(manager.GetTotalVehicles(), 15);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);

  manager.SetVehicle(5, 4);
  manager.SetBunsAmount(5, 0);
  EXPECT_EQ(manager.GetTotalBunsAmount(), 19);
  EXPECT_EQ(manager.GetTotalVehicles(), 19);
  buns_amounts[0] = 5;
  vehicles[4] = 5;
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, ChainMoveVehicles) {
  Chain chain(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  ChainTrafficManager manager(&chain, buns_amounts, vehicles, 1);
  int transport_time = manager.MoveVehicles(0, 3, 3);
  EXPECT_EQ(transport_time, 3);
  vehicles[3] += 3;
  vehicles[0] -= 3;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, ChainTransport) {
  Chain chain(5);
  std::vector<int> buns_amounts{1, 0, 5, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  ChainTrafficManager manager(&chain, buns_amounts, vehicles, 1);
  int transport_time = manager.Transport(2, 4, 5);
  EXPECT_EQ(transport_time, 3);
  buns_amounts[4] += 5;
  buns_amounts[2] -= 5;
  vehicles[4] += 5;
  vehicles[2] -= 3;
  vehicles[1] -= 2;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
  EXPECT_EQ(manager.GetBunsAmounts(), buns_amounts);
}