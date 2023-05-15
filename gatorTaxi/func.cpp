#include <iostream>
#include "func.h"

// Determine the label
void RideManager::labelDet(std::string op, std::string &label, std::string &rest){
    std::string sc1 = "Insert(";
    std::string sc2 = "GetNextRide(";
    std::string sc3 = "Print(";
    std::string sc4 = "UpdateTrip(";
    std::string sc5 = "CancelRide(";

    if(op.substr(0,sc1.size()) == sc1) {
        label = "I";
        rest = op.substr(sc1.size());
    }
    else if (op.substr(0,sc2.size()) == sc2) {
        label = "G";
        rest = op.substr(sc2.size());
    }
    else if (op.substr(0,sc3.size()) == sc3) {
        label = "P";
        rest = op.substr(sc3.size());
    }
    else if (op.substr(0,sc4.size()) == sc4) {
        label = "U";
        rest = op.substr(sc4.size());
    }
    else if (op.substr(0,sc5.size()) == sc5) {
        label = "C";
        rest = op.substr(sc5.size());
    }
}

// Prints the triplet (rideNumber, rideCost, tripDuration) in RBT
void RideManager::printRide(int rideNumber) {
    rbt.printRide(rideNumber);
}

// Prints all triplets (rx, rideCost, tripDuration) for which rideNumber1 <= rx <= rideNumber2 in RBT
void RideManager::printRides(int rideNumber1, int rideNumber2) {
    rbt.printRides(rideNumber1, rideNumber2);
}

// Insert the new triplet
void RideManager::insert(int rideNumber, int rideCost, int tripDuration) {
    Ride* ride = rbt.search(rideNumber);
    if(ride){
        // If the rideNumber has already existed, print the Duplicate RideNumber and shut down the program.
        std::cout << "Duplicate RideNumber" << std::endl;
        std::exit(1); 
    }
    else{
        // Otherwise, insert the new triplet into min heap and red black tree
        Ride* ride = new Ride(rideNumber, rideCost, tripDuration);
        mh.insert(ride);
        rbt.insert(rideNumber, rideCost, tripDuration);
    }
}

// Find the ride with the lowest rideCost (ties are broken by selecting the ride with the lowest tripDuration), output it, and delete it from min heap and red black tree
void RideManager::getNextRide() {
    Ride* ride = rbt.getNextRide();
    if (ride) {
        std::cout << "(" << ride->rideNumber << "," << ride->rideCost << "," << ride->tripDuration << ")" << std::endl;
        cancelRide(ride->rideNumber);
    }
}

// Delete the triplet
void RideManager::cancelRide(int rideNumber) {
    Ride* ride = rbt.search(rideNumber);
    if (ride) {
        mh.cancelRide(rideNumber);
        rbt.cancelRide(rideNumber);
    }
}

// Update the trip according to the relationship between the new tripDuration and the old one
void RideManager::updateTrip(int rideNumber, int new_tripDuration) {
    Ride* ride = rbt.search(rideNumber);
    if(ride){
        rbt.updateTrip(rideNumber, new_tripDuration);
        mh.updateTrip(ride, new_tripDuration);
    }

}
