//
// Created by dmi4er4 on 12.02.2022.
//

#ifndef TRAFFIC_MANAGER_H
#define TRAFFIC_MANAGER_H
#include "graph.h"
#include <utility>
#include <vector>
class TrafficManager {
 public:
  TrafficManager(Graph graph,
                 const std::vector<int>& buns_amounts,
                 const std::vector<int>& vehicles,
                 int vehicle_capacity) : graph_(std::move(graph)),
                                         vehicle_capacity_(vehicle_capacity) {
    SetBunsAmounts(buns_amounts);
    SetVehicles(vehicles);
  }

  [[nodiscard]] std::vector<int> GetBunsAmounts() const;
  [[nodiscard]] int GetBunsAmount(int) const;
  void SetBunsAmounts(const std::vector<int>&);
  void SetBunsAmount(int, int);

  [[nodiscard]] std::vector<int> GetVehicles() const;
  [[nodiscard]] int GetVehicle(int) const;
  void SetVehicles(const std::vector<int>&);
  void SetVehicle(int, int);

  [[nodiscard]] int GetTotalBunsAmount() const;
  [[nodiscard]] int GetTotalVehicles() const;

  int MoveVehicles(int, int, int);
  int Transport(int, int, int);
 private:
  Graph graph_;
  std::vector<int> buns_amounts_;
  std::vector<int> vehicles_;
  int vehicle_capacity_;
  int total_buns_amount_{};
  int total_vehicles_{};
};
#endif //TRAFFIC_MANAGER_H
