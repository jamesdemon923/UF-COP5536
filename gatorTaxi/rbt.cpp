#include <iostream>
#include "rbt.h"

void RBT::insert(int rideNumber, int rideCost, int tripDuration) {
    rbtMap[rideNumber] = new Ride(rideNumber, rideCost, tripDuration);
}

Ride* RBT::search(int rideNumber){
    auto it = rbtMap.find(rideNumber);
    if (it != rbtMap.end()) {
        return it->second;
    }
    return 0;
}

void RBT::printRide(int rideNumber) {
    auto it = rbtMap.find(rideNumber);
    if (it != rbtMap.end()) {
        Ride *ride = it->second;
        std::cout << "(" << ride->rideNumber << "," << ride->rideCost << "," << ride->tripDuration << ")" << std::endl;
    }
    else {
        std::cout << "(0,0,0)" << std::endl;
    }
}

void RBT::printRides(int rideNumber1, int rideNumber2) {
    auto lower = rbtMap.lower_bound(rideNumber1);
    auto upper = rbtMap.upper_bound(rideNumber2);

    if (lower == rbtMap.end() || lower == upper) {
        std::cout << "(0,0,0)" << std::endl;
        return;
    }

    for (auto it = lower; it != upper; ++it) {
        Ride *ride = it->second;
        std::cout << "(" << ride->rideNumber << "," << ride->rideCost << "," << ride->tripDuration << ")";
        if (std::next(it) != upper) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

Ride* RBT::getNextRide() {
    if (rbtMap.empty()) {
        std::cout << "No active ride requests" << std::endl;
        return 0;
    }
    auto it = rbtMap.begin();
    Ride* min_ride = it->second;
    for (++it; it != rbtMap.end(); ++it) {
        Ride* ride = it->second;
        if (ride->rideCost < min_ride->rideCost ||
            (ride->rideCost == min_ride->rideCost && ride->tripDuration < min_ride->tripDuration)) {
            min_ride = ride;
        }
    }
    return min_ride;
}

void RBT::cancelRide(int rideNumber) {
    auto it = rbtMap.find(rideNumber);
    if (it != rbtMap.end()) {
        delete it->second;
        rbtMap.erase(it);
    }
}

void RBT::updateTrip(int rideNumber, int new_tripDuration) {
    auto it = rbtMap.find(rideNumber);
    if (it != rbtMap.end()) {
        Ride *ride = it->second;
        int existing_tripDuration = ride->tripDuration;

        if (new_tripDuration <= existing_tripDuration) {
            // Update the tripDuration only
            ride->tripDuration = new_tripDuration;
        } else if (existing_tripDuration < new_tripDuration && new_tripDuration <= 2 * existing_tripDuration) {
            // Penalty of 10 on existing rideCost
            ride->rideCost += 10;
            ride->tripDuration = new_tripDuration;
        } else if (new_tripDuration > 2 * existing_tripDuration) {

            cancelRide(rideNumber);
        }
    }
}
