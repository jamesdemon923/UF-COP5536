#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include <cstdlib>
#include "mh.h"
#include "rbt.h"

class RideManager {
public:

    RideManager() = default;

    void labelDet(std::string op, std::string &label, std::string &rest);
    void printRide(int rideNumber);
    void printRides(int rideNumber1, int rideNumber2);
    void insert(int rideNumber, int rideCost, int tripDuration);
    void getNextRide();
    void cancelRide(int rideNumber);
    void updateTrip(int rideNumber, int new_tripDuration);

private:
    // RideManager integrates the functions of min heap and red-black tree 
    MinHeap mh;
    RBT rbt;
};
