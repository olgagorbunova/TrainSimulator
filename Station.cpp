//
//  Station.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Station.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

/* addDistance:
 * -----------
 * Adds a pair (destination, distance) to a destination map.
 */
void Station::addDistance(string destination, int km) {
    distances[destination] = km;
}

/* getDistance:
 * -----------
 * Returns distance to a destination, in km. If destination with given name not found, returns '-1'.
 */
int Station::getDistance(std::string destination) const {
    auto range = distances.equal_range(destination);
    for(auto it = range.first; it != range.second; ++it) {
        return it->second;
    }
    return -1;
}

/* addVehicleToPool:
 * ----------------
 * Adds vehicle with provided vehicle parameters to station vehicle pool.
 */
void Station::addVehicleToPool(int vehType, int vehId, int param1, int param2) {
    switch (vehType) { //adds different vehicles depending on vehicle type
        case 0:
            vehiclePool.push_back(unique_ptr<Vehicle>(new Coach(vehId, param1, param2)));
            break;
        case 1:
            vehiclePool.push_back(unique_ptr<Vehicle>(new Sleeping(vehId, param1)));
            break;
        case 2:
            vehiclePool.push_back(unique_ptr<Vehicle>(new OpenFreight(vehId, param1, param2)));
            break;
        case 3:
            vehiclePool.push_back(unique_ptr<Vehicle>(new CoveredFreight(vehId, param1)));
            break;
        case 4:
            vehiclePool.push_back(unique_ptr<Vehicle>(new ElectrEngine(vehId, param1, param2)));
            break;
        case 5:
            vehiclePool.push_back(unique_ptr<Vehicle>(new DieselEngine(vehId, param1, param2)));
            break;
        default:
            break;
    }
}

/* removeVehicleFromPool:
 * ---------------------
 * Removes vehicle with given vehicle id from a station vehicle pool.
 * Pre-condition: it has been verified that this vehicle is at the station pool.
 */
void Station::removeVehicleFromPool(int vehId) {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            vehiclePool.erase(vehiclePool.begin() + i, vehiclePool.begin() + i+1);
        }
    }
}

/* hasVehicle:
 * ----------
 * Sorts vehicles in pool to get vehicles with lowest id first.
 * Returns true and updates reference argument for vehId if vehicle with requested ID found in vehicle pool.
 */
bool Station::hasVehicle(int vehType, int &vehId) {
    orderVehPoolById();
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehType == vehiclePool[i]->getVehicleType())
        {
            vehId = vehiclePool[i]->getVehicleId();
            return true;
        }
    }
    vehId = -1;
    return false;
}

/* getVehicleType:
 * --------------
 * Returns vehicle type for vehicle with provided vehicle id. Returns -1 if vehicle with provided id not found.
 */
int Station::getVehicleType(int vehId) {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            return vehiclePool[i]->getVehicleType();
        }
    }
    return -1;
}

/* getVehicleParam1:
 * ----------------
 * Returns vehicle parameter 1 for vehicle with provided vehicle id. Returns -1 if vehicle with provided id not found.
 */
int Station::getVehicleParam1(int vehId) {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            int type = vehiclePool[i]->getVehicleType();
            if(type == 0 || type == 1)
                return vehiclePool[i]->getNrPassengers();
            else if(type == 2 || type == 3)
                return vehiclePool[i]->getCapacity();
            else
                return vehiclePool[i]->getSpeed();
        }
    }
    return -1;
}

/* vehicleHasParam2:
 * ----------------
 * Returns true if vehicle has parameter 2, otherwise returns false.
 */
bool Station::vehicleHasParam2(int vehId) {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            int type = vehiclePool[i]->getVehicleType();
            if(type == 1 || type == 3)
                return false;
            else
                return true;
        }
    }
    return false;
}

/* getVehicleParam2:
 * ----------------
 * Returns vehicle parameter 2 for vehicle with provided vehicle id. Returns -1 if vehicle with provided id not found.
 * Pre-condition: it is known that vehicle has parameter 2 (vehicleHasParam2() function to be used).
 */
int Station::getVehicleParam2(int vehId) {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            int type = vehiclePool[i]->getVehicleType();
            if(type == 0)
                return vehiclePool[i]->hasInternet();
            else if(type == 2)
                return vehiclePool[i]->getArea();
            else if(type == 4)
                return vehiclePool[i]->getPower();
            else if(type == 5)
                return vehiclePool[i]->getFuelConsump();
            else
                return -1;
        }
    }
    return -1;
}

/* showStation:
 * -----------
 * Shows station info. Calls showAllVehicles() function for showing vehicle information for all vehicles in a train vector.
 */
void Station::showStation() const {
    cout << endl << "STATION " << stationName << endl;
    cout << "-------------------------------------" << endl;
    cout << setfill(' ');
    cout << left << setw(30) << "Destinations" << "Km" << endl;
    cout << "-------------------------------------" << endl;
    auto start = distances.begin(), stop = distances.end();
    for(auto it = start; it != stop; ++it) {
        cout << left << setw(30) << it->first << it->second << endl;
    }
    cout << "-------------------------------------" << endl;
    cout << "Nr vehicles: " << vehiclePool.size() << endl;
    cout << "-------------------------------------" << endl;
    showAllVehicles();
    cout << endl;
}

/* showVehicle:
 * -----------
 * Calls Vehicle class function for showing vehicle information for a vehicles with provided id. Returns true if vehicle found, otherwise returns false.
 */
bool Station::showVehicle(int vehId) const {
    bool vehFound = false;
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        if(vehId == vehiclePool[i]->getVehicleId())
        {
            vehiclePool[i]->showInfo();
            vehFound = true;
        }
    }
    return vehFound;
}

/* showAllVehicles:
 * ---------------
 * Calls Vehicle class function for showing vehicle information for all vehicles in a vehicle pool.
 */
void Station::showAllVehicles() const {
    for(auto i = 0; i < vehiclePool.size(); i++)
    {
        vehiclePool[i]->showInfo();
    }
}

/* orderVehicles:
 ---------------
 Sorting vehicled order based on vehicle ID, ascending. Using helper function greaterVeh().
 */
void Station::orderVehPoolById() {
    sort(vehiclePool.begin(), vehiclePool.end(), greaterVeh);
}

/* greaterVeh:
 * ----------
 Helper function for sorting. Comparing vehicled based on vehicle ID.
 */
bool greaterVeh(const unique_ptr<Vehicle> &a, const unique_ptr<Vehicle> &b) {
    return *a < *b;
}
