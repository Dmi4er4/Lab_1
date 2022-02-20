//
// Created by dmi4er4 on 12.02.2022.
//
#include<gtest/gtest.h>
#include "traffic_manager.h"

TEST(TrafficManager, ConstructorsGettersSetters) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(full_graph, buns_amounts, vehicles, 1);
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

TEST(TrafficManager, MoveVehicles) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(full_graph, buns_amounts, vehicles, 1);
  int transport_time = manager.MoveVehicles(0, 3, 3);
  EXPECT_EQ(transport_time, 1);
  vehicles[3] += 3;
  vehicles[0] -= 3;
  EXPECT_EQ(manager.GetVehicles(), vehicles);
}

TEST(TrafficManager, Transport) {
  Graph full_graph(5);
  std::vector<int> buns_amounts{1, 2, 3, 4, 5};
  std::vector<int> vehicles{5, 4, 3, 2, 1};
  TrafficManager manager(full_graph, buns_amounts, vehicles, 1);
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
