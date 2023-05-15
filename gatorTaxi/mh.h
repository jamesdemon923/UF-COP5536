#pragma once

#include <vector>
#include <stdexcept>

struct Ride;

class MinHeap {
public:
    MinHeap() = default;

    void insert(Ride *ride);
    void cancelRide(int rideNumber);
    void updateTrip(Ride *ride, int new_tripDuration);

private:
    std::vector<Ride*> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void upHeap(int i);
    void downHeap(int i);
};
