#include "mh.h"
#include "Ride.h"

void MinHeap::insert(Ride *ride) {
    heap.push_back(ride);
    upHeap(heap.size() - 1);
}

void MinHeap::cancelRide(int rideNumber) {
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i]->rideNumber == rideNumber) {
            std::swap(heap[i], heap.back());
            heap.pop_back();
            upHeap(i);
            downHeap(i);
            break;
        }
    }
}

void MinHeap::updateTrip(Ride *ride, int new_tripDuration) {
    if (ride) {
        return;
    }
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i]->rideNumber == ride->rideNumber) {
            int existing_tripDuration = heap[i]->tripDuration;

            if (new_tripDuration <= existing_tripDuration) {
                // Update the tripDuration only
                heap[i]->tripDuration = new_tripDuration;
            } else if (existing_tripDuration < new_tripDuration && new_tripDuration <= 2 * existing_tripDuration) {
                // Cancel the existing ride and create a new ride request with a penalty of 10 on existing rideCost
                heap[i]->tripDuration = new_tripDuration;
                heap[i]->rideCost += 10;
                upHeap(i);
                downHeap(i);
            } else if (new_tripDuration > 2 * existing_tripDuration) {
                // Automatically decline the ride and remove it from the data structure
                cancelRide(ride->rideNumber);
            }
            break;
        }
    }
}

void MinHeap::upHeap(int i) {
    while (i > 0 && *heap[parent(i)] < *heap[i]) {
        std::swap(heap[parent(i)], heap[i]);
        i = parent(i);
    }
}

void MinHeap::downHeap(int i) {
    int minIndex = i;
    unsigned int l = leftChild(i);
    if (l < heap.size() && *heap[l] < *heap[minIndex]) {
        minIndex = l;
    }
    unsigned int r = rightChild(i);
    if (r < heap.size() && *heap[r] < *heap[minIndex]) {
        minIndex = r;
    }
    if (i != minIndex) {
        std::swap(heap[i], heap[minIndex]);
        downHeap(minIndex);
    }
}

