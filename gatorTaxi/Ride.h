#pragma once

struct Ride {
    int rideNumber, rideCost, tripDuration;

    // Constructor
    Ride(int r, int c, int t) : rideNumber(r), rideCost(c), tripDuration(t) {}

    // Comparison for min heap
    bool operator<(const Ride& rhs) const {
        if (rideCost == rhs.rideCost) {
            return tripDuration > rhs.tripDuration;
        }
        return rideCost > rhs.rideCost;
    }
};
