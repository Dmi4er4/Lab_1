//
// Created by dmi4er4 on 12.02.2022.
//

#include <algorithm>
#include "traffic_manager.h"

const int kInfinity = std::numeric_limits<int>::max();

//getters and setters for buns_amounts
std::vector<int> TrafficManager::GetBunsAmounts() const {
  return buns_amounts_;
}
int TrafficManager::GetBunsAmount(int town) const {
  return buns_amounts_[town];
}
void TrafficManager::SetBunsAmounts(const std::vector<int>& buns_amounts) {
  total_buns_amount_ = 0;
  for (int i = 0; i < buns_amounts.size(); i++) {
    buns_amounts_[i] = buns_amounts[i];
    total_buns_amount_ += buns_amounts[i];
  }
}
void TrafficManager::SetBunsAmount(int buns_amount, int town) {
  total_buns_amount_ -= buns_amounts_[town];
  total_buns_amount_ += buns_amount;
  buns_amounts_[town] = buns_amount;
}

//getters and setters for vehicles
std::vector<int> TrafficManager::GetVehicles() const {
  return vehicles_;
}
int TrafficManager::GetVehicle(int town) const {
  return vehicles_[town];
}
void TrafficManager::SetVehicles(const std::vector<int>& vehicles) {
  total_vehicles_ = 0;
  for (int i = 0; i < vehicles.size(); i++) {
    vehicles_[i] = vehicles[i];
    total_vehicles_ += vehicles[i];
  }
}
void TrafficManager::SetVehicle(int vehicle, int town) {
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
  vehicles_[from] -= count;
  vehicles_[to] += count;
  std::vector<Edge> path = graph_.GetShortestPath(from, to);
  int result = 0;
  for (Edge element: path) {
    result += element.length;
  }
  if (path.empty()) {
    result = kInfinity;
  }
  return result;
}
int TrafficManager::Transport(int from, int to, int buns_amount) {
  int vehicles_amount =
      buns_amount / vehicle_capacity_ + (buns_amount % vehicle_capacity_ > 0);
  std::vector<std::pair<int, int>> sorted_paths;
  for (int i = 0; i < graph_.GetSize(); i++) {
    std::vector<Edge> path = graph_.GetShortestPath(i, to);
    int result = kInfinity;
    for (Edge element: path) {
      result += element.length;
    }
    sorted_paths.push_back({result, i});
  }
  int result = 0;
  std::sort(sorted_paths.begin(), sorted_paths.end());
  for (auto& path: sorted_paths) {
    int vehicles_to_move = std::min(vehicles_[path.second],
                                    vehicles_amount - vehicles_[from]);
    vehicles_[path.second] -= vehicles_to_move;
    vehicles_[from] += vehicles_to_move;
    result += path.first;
    if (vehicles_[from] == vehicles_amount) {
      break;
    }
  }
  result += MoveVehicles(from, to, buns_amount);
  return result;
}
