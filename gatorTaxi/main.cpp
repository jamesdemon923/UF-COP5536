#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "func.h"


using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " file_name\n";
        return 1;
    }

    // Read the input_file
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: unable to open input file " << argv[1] << "\n";
        return 1;
    }

    // Create the output_file
    std::ofstream outfile("output_file.txt");
    if (!outfile) {
        std::cerr << "Error: unable to open output file\n";
        return 1;
    }

    // Save the original buffer of std::cout
    std::streambuf *coutbuf = std::cout.rdbuf();

    // Redirect std::cout to the output file
    std::cout.rdbuf(outfile.rdbuf());

    RideManager manager; 
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string op, label, rest; // rest is used to store the string after "(", which can help me get the numbers I want easily.
        iss >> op;
        // Get the label by determining keywords
        manager.labelDet(op, label, rest);

        if (label == "I") {

            int rideNumber, rideCost, tripDuration;
            char c;

            std::istringstream iss(rest);

            // Read the numbers for each variable
            iss >> rideNumber >> c >> rideCost >> c >> tripDuration;

            manager.insert(rideNumber, rideCost, tripDuration);
        }
        else if (label == "P") {

            int rideNumber1, rideNumber2;
            char c;

            std::istringstream iss(rest);
            
            // Check if the string contains a comma
            if (rest.find(',') != std::string::npos) {
                iss >> rideNumber1 >> c >> rideNumber2;
                manager.printRides(rideNumber1, rideNumber2);
            } 
            else {
                iss >> rideNumber1;
                manager.printRide(rideNumber1);
            }

        }
        else if (label == "U") {

            int rideNumber, newTripDuration;
            char c;

            std::istringstream iss(rest);

            iss >> rideNumber >> c >> newTripDuration;

            manager.updateTrip(rideNumber, newTripDuration);
        }
        else if (label == "G") {

            manager.getNextRide();
        }
        else if (label == "C") {

            int rideNumber;
            char c;

            std::istringstream iss(rest);

            iss >> rideNumber;

            manager.cancelRide(rideNumber);
        }
    }

    // Restore the original buffer of std::cout
    std::cout.rdbuf(coutbuf);
    
    cout << "run!" << endl;
    infile.close();
    outfile.close();

    return 0;
}


