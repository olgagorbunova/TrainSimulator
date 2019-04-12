//
//  Vehicle.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-29.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Vehicle.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

/* operator <:
 * ----------
 * Overloaded operator < for class Vehicle, for comparison of vehicles by vehicle id.
 */
bool Vehicle::operator<(const Vehicle &v) const
{
    return getVehicleId() < v.getVehicleId();
}

/* Coach::showInfo:
 * ---------------
 * Prints information about a passenger coach vehicle. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void Coach::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Passenger Coach] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Number of seats (" << Passenger::getNrPassengers() << ") Internet (";
        if(internetStatus == 1)
            cout << "Yes";
        else
            cout << "No";
        cout << ")";
    }
    cout << endl;
}

/* Sleeping::showInfo:
 * ------------------
 * Prints information about a passenger sleeping vagon. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void Sleeping::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Passenger Sleeping Car] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Number of beds (" << Passenger::getNrPassengers() << ")";
    }
    cout << endl;
}

/* OpenFreight::showInfo:
 * ---------------------
 * Prints information about an open freight vagon. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void OpenFreight::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Open Freight Car] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Cargo capacity (" << Freight::getCapacity() << " tons) Floor area (" << floorArea << " square m)";
    }
    cout << endl;
}

/* CoveredFreight::showInfo:
 * ------------------------
 * Prints information about a covered freight vagon. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void CoveredFreight::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Covered Freight Car] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Cargo capacity (" << Freight::getCapacity() << " cubic meters)";
    }
    cout << endl;
}

/* ElectrEngine::showInfo:
 * ----------------------
 * Prints information about an electrical engine vehicle. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void ElectrEngine::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Electrical Engine] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Max speed (" << Engine::getSpeed() << " km/h) Power (" << power << " kW)";
    }
    cout << endl;
}

/* DieselEngine::showInfo:
 * ----------------------
 * Prints information about a diesel engine vehicle. If vehicle id = -1, informs that vehicle not added to train and displays vehicle parameters as 0.
 */
void DieselEngine::showInfo() {
    int vehId = Vehicle::getVehicleId();
    
    cout << "[Diesel Engine] ";
    if(vehId == -1) {
        cout << "No vehicle added to train";
    }
    else {
        cout << "Vehicle ID (" << vehId << ") Max speed (" << Engine::getSpeed() << " km/h) Fuel consumption (" << fuelConsumption << " liters/h)";
    }
    cout << endl;
}
