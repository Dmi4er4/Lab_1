//
// Created by dmi4er4 on 12.02.2022.
//

#include <algorithm>
#include <cassert>
#include "traffic_manager.h"

const int kInfinity = std::numeric_limits<int>::max();

//getters and setters for buns_amounts
std::vector<int> TrafficManager::GetBunsAmounts() const {
  return buns_amounts_;
}
int TrafficManager::GetBunsAmount(int town) const {
  assert(town >= 0 && town < graph_.GetSize());
  return buns_amounts_[town];
}
void TrafficManager::SetBunsAmounts(const std::vector<int>& buns_amounts) {
  assert(buns_amounts.size() == graph_.GetSize());
  buns_amounts_.resize(buns_amounts.size());
  total_buns_amount_ = 0;
  for (int i = 0; i < buns_amounts.size(); i++) {
    buns_amounts_[i] = buns_amounts[i];
    total_buns_amount_ += buns_amounts[i];
  }
}
void TrafficManager::SetBunsAmount(int buns_amount, int town) {
  assert(town >= 0 && town < graph_.GetSize());
  total_buns_amount_ -= buns_amounts_[town];
  total_buns_amount_ += buns_amount;
  buns_amounts_[town] = buns_amount;
}

//getters and setters for vehicles
std::vector<int> TrafficManager::GetVehicles() const {
  return vehicles_;
}
int TrafficManager::GetVehicle(int town) const {
  assert(town >= 0 && town < graph_.GetSize());
  return vehicles_[town];
}
void TrafficManager::SetVehicles(const std::vector<int>& vehicles) {
  assert(vehicles.size() == graph_.GetSize());
  vehicles_.resize(vehicles.size());
  total_vehicles_ = 0;
  for (int i = 0; i < vehicles.size(); i++) {
    vehicles_[i] = vehicles[i];
    total_vehicles_ += vehicles[i];
  }
}
void TrafficManager::SetVehicle(int vehicle, int town) {
  assert(town >= 0 && town < graph_.GetSize());
  total_vehicles_ -= vehicles_[town];
  total_vehicles_ += vehicle;
  vehicles_[town] = vehicle;
}

//getters for total amounts
int TrafficManager::GetTotalBunsAmount() const {
  return total_buns_amount_;
}
int TrafficManager::GetTotalVehicles() const {
  return total_vehicles_;
}
int TrafficManager::MoveVehicles(int from, int to, int count) {
  assert(from >= 0 && from < graph_.GetSize());
  assert(to >= 0 && to < graph_.GetSize());
  vehicles_[from] -= count;
  vehicles_[to] += count;
  std::vector<Graph::Edge> path = graph_.GetShortestPath(from, to);
  int result = 0;
  for (Graph::Edge element: path) {
    result += element.length;
  }
  return result;
}
int TrafficManager::Transport(int from, int to, int buns_amount) {
  assert(from >= 0 && from < graph_.GetSize());
  assert(to >= 0 && to < graph_.GetSize());
  int vehicles_amount =
      buns_amount / vehicle_capacity_ + (buns_amount % vehicle_capacity_ > 0);
  std::vector<std::pair<int, int>> sorted_paths;
  for (int i = 0; i < graph_.GetSize(); i++) {
    std::vector<Graph::Edge> path = graph_.GetShortestPath(i, to);
    int result = 0;
    for (Graph::Edge element: path) {
      result += element.length;
    }
    if (path.empty()) {
      result = kInfinity;
    }
    sorted_paths.emplace_back(result, i);
  }
  std::sort(sorted_paths.begin(), sorted_paths.end());
  int max_movement_time = 0;
  for (auto& path: sorted_paths) {
    int vehicles_to_move = std::min(vehicles_[path.second],
                                    vehicles_amount - vehicles_[from]);
    vehicles_[path.second] -= vehicles_to_move;
    vehicles_[from] += vehicles_to_move;
    max_movement_time = std::max(path.first, max_movement_time);
    if (vehicles_[from] == vehicles_amount) {
      break;
    }
  }
  int result = max_movement_time + MoveVehicles(from, to, vehicles_amount);
  buns_amounts_[from] -= buns_amount;
  buns_amounts_[to] += buns_amount;
  return result;
}
