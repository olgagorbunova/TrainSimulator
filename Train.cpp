//
//  Train.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "Train.hpp"
#include "SimConst.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

/* getVehicleType:
 * --------------
 * Returns integer for vehicle type.
 */
int Train::getVehicleType(Vehicle &a) {
    return a.getVehicleType();
}

/* getNrVehicles:
 * -------------
 * Returns number of vehicles as integer.
 */
int Train::getNrVehicles() {
    return train.size();
}

/* updateVehicle:
 * -------------
 * Function is used under train assembling for replacing a first found 'conceptual' vehicle of a specific type with a real vehicle with provided parameters.
 */
void Train::updateVehicle(int vehType, int vehIdNew, int param1, int param2) {
    for(auto i = 0; i < train.size(); i++)
    {
        int id = train[i]->getVehicleId();
        int type = train[i]->getVehicleType();
        if((id == -1) && (type == vehType)) { //identifies first 'conceptual' (id == -1) vehicle of provided vehicle type
            train[i]->setVehicleId(vehIdNew);
            switch (vehType) { //sets different train paramenters for different vehicle types
                case 0:
                    train[i]->setNrPassengers(param1); train[i]->setInternet(param2);
                    break;
                case 1:
                    train[i]->setNrPassengers(param1);
                    break;
                case 2:
                    train[i]->setCapacity(param1); train[i]->setArea(param2);
                    break;
                case 3:
                    train[i]->setCapacity(param1);
                    break;
                case 4:
                    train[i]->setSpeed(param1); train[i]->setPower(param2);
                    break;
                case 5:
                    train[i]->setSpeed(param1); train[i]->setFuelConsump(param2);
                    break;
                default:
                    break;
            }
            break;
        }
    }
}
/* detachVehicle:
 * -------------
 * Used during dissamble. Function detaches a physical vehicle from a train vector: sets vehicle parameters to values incicating that vehicle is not attached to a train. Updates values of inparameters for vehicle information.
 */
void Train::detachVehicle(int vehIdx, int &vehType, int &vehId, int &param1, int &param2) {
    if(train[vehIdx]->getVehicleId() != -1) { //identifies non-'conceptual' vehicle (vehicle id != -1)
        vehId = train[vehIdx]->getVehicleId();
        
        train[vehIdx]->setVehicleId(-1);
        
        vehType = train[vehIdx]->getVehicleType();
        
        switch (vehType) {
            case 0: //sets different train paramenters for different vehicle types
                param1 = train[vehIdx]->getNrPassengers(); param2 = train[vehIdx]->hasInternet();
                train[vehIdx]->setNrPassengers(0); train[vehIdx]->setInternet(0);
                break;
            case 1:
                param1 = train[vehIdx]->getNrPassengers(); param2 = 0;
                train[vehIdx]->setNrPassengers(0);
                break;
            case 2:
                param1 = train[vehIdx]->getCapacity(); param2 = train[vehIdx]->getArea();
                train[vehIdx]->setCapacity(0); train[vehIdx]->setArea(0);
                break;
            case 3:
                param1 = train[vehIdx]->getCapacity(); param2 = 0;
                train[vehIdx]->setCapacity(0);
                break;
            case 4:
                param1 = train[vehIdx]->getSpeed(); param2 = train[vehIdx]->getPower();
                train[vehIdx]->setSpeed(0); train[vehIdx]->setPower(0);
                break;
            case 5:
                param1 = train[vehIdx]->getSpeed(); param2 = train[vehIdx]->getFuelConsump();
                train[vehIdx]->setSpeed(0); train[vehIdx]->setFuelConsump(0);
                break;
            default:
                break;
        }
    }
}

/* findTrainByVehicle:
 * ------------------
 * Searches for train that contains provided vehicle id. If found, returns train number, else returns -1.
 */
int Train::findTrainByVehicle(int vehId) {
    for(auto i = 0; i < train.size(); i++)
    {
        if(train[i]->getVehicleId() == vehId)
            return trainNumber;
    }
    return -1;
}

/* addVehicle:
 * ----------
 * Adds vehicle to train vector with provided vehicle parometers.
 */
void Train::addVehicle(int vehType, int vehId, int param1, int param2) {
    switch (vehType) { //adds different vehicles depending on vehicle type
        case 0: 
            train.push_back(unique_ptr<Vehicle>(new Coach(vehId, param1, param2)));
            break;
        case 1:
            train.push_back(unique_ptr<Vehicle>(new Sleeping(vehId, param1)));
            break;
        case 2:
            train.push_back(unique_ptr<Vehicle>(new OpenFreight(vehId, param1, param2)));
            break;
        case 3:
            train.push_back(unique_ptr<Vehicle>(new CoveredFreight(vehId, param1)));
            break;
        case 4:
            train.push_back(unique_ptr<Vehicle>(new ElectrEngine(vehId, param1, param2)));
            break;
        case 5:
            train.push_back(unique_ptr<Vehicle>(new DieselEngine(vehId, param1, param2)));
            break;
        default:
            break;
    }
}

/* vehicleMissing:
 * --------------
 * Used during train assembling. Checking if a specific vehicle (identified by index in a vehicle vector) is missing for a train. Takes vehicle index as inparameter and updates reference argument with a missing vehicle type. If vehicle is not missing, updates with false value '-1'.
 */
bool Train::vehicleMissing(int vehIndex, int &missingVehType) {
    if(train[vehIndex]->getVehicleId() == -1)
    {
        missingVehType = train[vehIndex]->getVehicleType();
        return true;
    }
    missingVehType = -1;
    return false;
}

/* showVehicle:
 * -----------
 * Calls Vehicle class function for showing vehicle information. Vehicle identified by vehicle id as in-parameter.
 */
bool Train::showVehicle(int vehId) const {
    bool found = false;
    for(auto i = 0; i < train.size(); i++)
    {
        if(vehId == train[i]->getVehicleId())
        {
            train[i]->showInfo();
            found = true;
        }
    }
    return found;
}

/* showAllVehicles:
 * ---------------
 * Calls Vehicle class function for showing vehicle information for all vehicles in a train vector.
 */
void Train::showAllVehicles() {
    //orderVehicles();
    for(auto i = 0; i < train.size(); i++)
    {
        train[i]->showInfo();
    }
}

/* showTrain:
 * ---------
 * Shows train info. Calls Vehicle class function for showing vehicle information for all vehicles in a train vector.
 */
void Train::showTrain() {
    cout << endl << "TRAIN NUMBER " << trainNumber << endl;
    cout << "-------------------------------------" << endl;
    cout << "Current state      : ";
    switch (trainState) {
        case 0: cout << "NOT_ASSEMBLED";
            break;
        case 1: cout << "INCOMPLETE";
            break;
        case 2: cout << "ASSEMBLED";
            break;
        case 3: cout << "READY";
            break;
        case 4: cout << "RUNNING";
            break;
        case 5: cout << "ARRIVED";
            break;
        case 6: cout << "FINISHED";
            break;
        default:
            break;
    }
    cout << endl << "Departure station  : " << deptStation << endl;
    cout << "Destination station: " << destStation << endl;
    cout << "Departure time     : "; showTime(deptTime);
    cout << endl << "Arrival time       : ";showTime(destTime);
    cout << endl << "Maximum speed      : " << maxSpeed << endl;
    cout << "-------------------------------------" << endl;
    showAllVehicles();
}

/* orderVehicles:
 ---------------
 Sorting vehicled in reversed order based on vehicle type. Using helper function greaterVeh().
 */
/*
void Train::orderVehicles() {
    sort(train.rbegin(), train.rend(), greaterVeh);
}
 */

/* greaterVeh:
 Helper function for sorting. Comparing vehicled based on vehicle ID.
 */
/*
bool greaterVeh(const unique_ptr<Vehicle> &a, const unique_ptr<Vehicle> &b) {
    return *a < *b;
}
 */
