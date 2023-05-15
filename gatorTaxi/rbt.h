#pragma once

#include <map>
#include "Ride.h"

class RBT {
public:
    RBT() = default;

    void insert(int rideNumber, int rideCost, int tripDuration);
    Ride* search(int rideNumber); // Find the triplet with rideNumber
    void printRide(int rideNumber);
    void printRides(int rideNumber1, int rideNumber2);
    Ride* getNextRide();
    void cancelRide(int rideNumber);
    void updateTrip(int rideNumber, int new_tripDuration);

private:
    std::map<int, Ride*> rbtMap;
};
