#ifndef TRAFFIC_MANAGER_H
#define TRAFFIC_MANAGER_H
#include "abstract_graph.h"
#include <utility>
#include <vector>
class TrafficManager {
 public:
  TrafficManager(AbstractGraph* graph,
                 const std::vector<int>& buns_amounts,
                 const std::vector<int>& vehicles,
                 int vehicle_capacity);

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
  virtual int Transport(int, int, int);

 protected:
  AbstractGraph* graph_;
  std::vector<int> buns_amounts_;
  std::vector<int> vehicles_;
  int vehicle_capacity_;
  int total_buns_amount_{};
  int total_vehicles_{};
};

class ChainTrafficManager : public TrafficManager {
 public:
  ChainTrafficManager(AbstractGraph* graph,
                 const std::vector<int>& buns_amounts,
                 const std::vector<int>& vehicles,
                 int vehicle_capacity);

  virtual int Transport(int, int, int) override;
};

#endif //TRAFFIC_MANAGER_H
