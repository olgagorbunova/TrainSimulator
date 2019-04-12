//
//  IronbendInc.cpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-31.
//  Copyright © 2018 Olga. All rights reserved.
//

#include "IronbendInc.hpp"
using namespace std;

/* addTrain:
 * --------
 * Train is added to the train vector.
 */
void IronbendInc::addTrain(int tNum, std::string depStn, std::string desStn, Time depTime, Time desTime, int mSpeed, int tState, double speed) {
    ironbendTrains.push_back(unique_ptr<Train>(new Train(tNum, depStn, desStn, depTime, desTime, mSpeed, tState, speed)));
}

/* addVehicleToTrain:
 * -----------------
 * Vehicle is added to a train in the train vector.
 */
void IronbendInc::addVehicleToTrain(int trainNum, int vehType, int vehId, int param1, int param2) {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
            ironbendTrains[i]->addVehicle(vehType, vehId, param1, param2);
    }
}

/* getDeptStation:
 * --------------
 * Returns name of the departure station for train with number as function's in-parameter. Returns error message if no station found.
 */
string IronbendInc::getDeptStation(int trainNum) const {
    string deptStation = "Info not found";
    
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
            deptStation = ironbendTrains[i]->getDeptStation();
    }
    return deptStation;
}

/* getArrStation:
 * -------------
 * Returns name of the arrival station for train with number as function's in-parameter. Returns error message if no station found.
 */
string IronbendInc::getArrStation(int trainNum) const {
    string arrStation = "Info not found";
    
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
            arrStation = ironbendTrains[i]->getDestStation();
    }
    return arrStation;
}

/* getDeptTime:
 * -----------
 * Updates reference in-paramenter to departure time for train with number as function's in-parameter. Returns boolean false if no train found, else returns true.
 */
bool IronbendInc::getDeptTime(int trainNum, Time &t) {
    bool result = false;
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            t = ironbendTrains[i]->getDeptTime();
            return true;
        }
    }
    return result;
}

/* getArrTime:
 * ----------
 * Updates reference in-paramenter to arrival time for train with number as function's in-parameter. Returns boolean false if no train found, else returns true.
 */
bool IronbendInc::getArrTime(int trainNum, Time &t) {
    bool result = false;
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            t = ironbendTrains[i]->getDestTime();
            return true;
        }
    }
    return result;
}

/* getArrStation:
 * -------------
 * Returns state as integer for train with number as function's in-parameter. Returns -1 if no train found.
 */
int IronbendInc::getTrainState(int trainNum) const {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            return ironbendTrains[i]->getTrainState();
        }
    }
    return -1;
}

/* setTrainState:
 * -------------
 * Sets state for a train (searches in train vector by train number).
 */
void IronbendInc::setTrainState(int trainNum, int state) {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            ironbendTrains[i]->setTrainState(state);
        }
    }
}

/* getTrainMaxSpeed:
 * ----------------
 * Returns a train's max speed. Returns -1 if no train found by the train number.
 */
int IronbendInc::getTrainMaxSpeed(int trainNum) const {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            return ironbendTrains[i]->getMaxSpeed();
        }
    }
    return -1;
}

/* getTrainAvgSpeed:
 * ----------------
 * Calculates trains traveling time (in hours), and then calculates trains average speed (KM/H) by dividing distance between departure and destination stattions by travelling time. Returns train's average speed. Returns -1 if no train found by the train number.
 */
double IronbendInc::getTrainAvgSpeed(int trainNum) {
    Time deptTime, arrTime, travelTime;
    Time midnight(12, 59);
    Time oneMin(0, 1);
    string deptStation, arrStation;
    int maxSpeed = 0;
    int distance = 0;
    double travelHrs, avgSpeed;
    
    for(auto i = 0; i < ironbendTrains.size(); i++) //search for train
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            deptTime = ironbendTrains[i]->getDeptTime();
            arrTime = ironbendTrains[i]->getDestTime();
            deptStation = ironbendTrains[i]->getDeptStation();
            arrStation = ironbendTrains[i]->getDestStation();
            maxSpeed = ironbendTrains[i]->getMaxSpeed();
        }
    }
    for(auto i = 0; i < ironbendStations.size(); i++) //search for departure station
    {
        if(deptStation == ironbendStations[i]->getStationName())
        {
            distance = ironbendStations[i]->getDistance(arrStation); //get distance to arrival station
        }
    }
    if(arrTime < deptTime) { //calculate travel time if arrival and departire are different days (trave over midnight)
        travelTime = (midnight - deptTime + oneMin) + arrTime;
    }
    else { //calculate travel time if arrival and departire are same day
        travelTime = arrTime - deptTime;
    }
    int min  = travelTime.getMin();
    int hrs = travelTime.getHour();
    travelHrs = static_cast<double>(hrs) + static_cast<double>(min)/60; //calculate average speed
    avgSpeed = distance/travelHrs;
    
    if(avgSpeed > maxSpeed) { //return max speed as average if avgSpeed > maxSpeed
        return maxSpeed;
    }
    else {
        return avgSpeed;
    }
}

/* assembleTrain:
 * -------------
 * Attempts to assemble train.
 * Checking what kind of vehicles train is missing and looking for available vehicle att departure station. If found, assignes vehicle to train and removes from station vehicle pool.
 * Keeps track of how many vehicles are added to train and calculates missing vehicles. If no vehicles missing at the end of attempt, atempt considered successful and true is returned. If not, false is returned.
 */
bool IronbendInc::assembleTrain(int trainNum) {
    
    int nrMissingVeh = 0;
    int vehId, param1, param2;
    
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            int nrVehicles = ironbendTrains[i]->getNrVehicles();
            for(int vehIdx = 0; vehIdx < nrVehicles; vehIdx++) {
                int missingVehType;
                if(ironbendTrains[i]->vehicleMissing(vehIdx, missingVehType))
                {
                    string stationName = ironbendTrains[i]->getDeptStation();
                    for(auto j = 0; j < ironbendStations.size(); j++)
                    {
                        if(stationName == ironbendStations[j]->getStationName())
                        {
                            //look for missing veh at dept station
                            if(ironbendStations[j]->hasVehicle(missingVehType, vehId)) { //if station has missing veh
                                param1 = ironbendStations[j]->getVehicleParam1(vehId);
                                param2 = 0;
                                if(ironbendStations[j]->vehicleHasParam2(vehId)) {
                                    param2 = ironbendStations[j]->getVehicleParam2(vehId);
                                }
                                ironbendStations[j]->removeVehicleFromPool(vehId);
                                ironbendTrains[i]->updateVehicle(missingVehType, vehId, param1, param2);
                            }
                            else
                                nrMissingVeh++;
                        }
                    }
                }
            }
        }
    }
    if(nrMissingVeh == 0) {
        return true;
    }
    else
        return false;
}

/* diassembleTrain:
 * ---------------
 * Train is diassembled and removed vehicles are added to the destination station vehicle pool.
 */
void IronbendInc::diassembleTrain(int trainNum) {
    int vehType, vehId, param1, param2;
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber())
        {
            int nrVehicles = ironbendTrains[i]->getNrVehicles();
            
            for(int vehIdx = 0; vehIdx < nrVehicles; vehIdx++) {
                ironbendTrains[i]->detachVehicle(vehIdx, vehType, vehId, param1, param2); //functions takes reference paramenters which are then used to add vehicle to arrival station pool:
                string station = ironbendTrains[i]->getDestStation();
                addVehicleToPool(station, vehType, vehId, param1, param2);
            }
        }
    }
}

/* showTrain:
 * ---------
 * Show information about a train by train number. Returns false if train not found, else returns true.
 */
bool IronbendInc::showTrain(int trainNum) const {
    bool trainFound = false;
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(trainNum == ironbendTrains[i]->getTrainNumber()) {
            ironbendTrains[i]->showTrain();
            trainFound = true;
        }
    }
    return trainFound;
}

/* showTrainByVeh:
 * --------------
 * Show information about a train by vehicle number. Returns false if train with such vehicle not found, else returns true.
 */
bool IronbendInc::showTrainByVeh(int vehId) const {
    bool trainFound = false;
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(ironbendTrains[i]->findTrainByVehicle(vehId) != -1) {
            showTrain(ironbendTrains[i]->findTrainByVehicle(vehId));
            trainFound = true;
        }
    }
    return trainFound;
}

/* showTrainByState:
 * ----------------
 * Show information about trains with given state.
 */
void IronbendInc::showTrainByState(int state) const {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        if(state == ironbendTrains[i]->getTrainState()) {
            ironbendTrains[i]->showTrain();
        }
    }
}

/* showAllTrains:
 * -------------
 * Show all train information.
 */
void IronbendInc::showAllTrains() const {
    for(auto i = 0; i < ironbendTrains.size(); i++)
    {
        ironbendTrains[i]->showTrain();
    }
}

/* showVehicle:
 * -----------
 * Show information about a vehicle, include current location. Returns false if vehicle with such id not found, else returns true.
 */
bool IronbendInc::showVehicle(int vehId) const {
    bool vehicleFound = false;
    bool vehFoundAtStation = false;
    
    for(auto i = 0; i < ironbendStations.size(); i++) //looking for vehicle at stations
    {
        vehFoundAtStation = ironbendStations[i]->showVehicle(vehId);
        if(vehFoundAtStation) {
            cout << "Current location: station " << ironbendStations[i]->getStationName() << endl;
            return true;
        }
    }
    if(!vehFoundAtStation) { //looking for vehicle at trains
        for(auto j = 0; j < ironbendTrains.size(); j++) {
            vehicleFound = ironbendTrains[j]->showVehicle(vehId);
            if(vehicleFound) {
                cout << "Current location: train nr " << ironbendTrains[j]->getTrainNumber() << endl;
                return true;
            }
        }
    }
    return vehicleFound;
}

/* showAllVehicles:
 * ---------------
 * Show information about all vehicles.
 */
void IronbendInc::showAllVehicles() const {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        ironbendStations[i]->showAllVehicles();
    }
    
}

/* stationFound:
 * ------------
 * Looking for station by station name. Returns true if found, else returns false.
 */
bool IronbendInc::stationFound(std::string stationName) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return true;
    }
    return false;
}

/* addStation:
 * ----------
 * Adds station to a station vector.
 */
void IronbendInc::addStation(std::string stationName) {
    ironbendStations.push_back(unique_ptr<Station>(new Station(stationName)));
}

/* addDistance:
 * -----------
 * Adds destination and distance to destination to a station in station vector.
 */
void IronbendInc::addDistance(std::string stationName, std::string destination, int km) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            ironbendStations[i]->addDistance(destination, km);
    }
}

/* getDistance:
 * -----------
 * Returns distance to destination from a station in station vector. If not station found, returns -1.
 */
int IronbendInc::getDistance(std::string stationName, std::string destination) const {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return ironbendStations[i]->getDistance(destination);
    }
    return -1;
}

/* addVehicleToPool:
 * ----------------
 * Adds vehicle to a stattion in a station's vehicle pool.
 */
void IronbendInc::addVehicleToPool(string stationName, int vehType, int vehId, int param1, int param2) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            ironbendStations[i]->addVehicleToPool(vehType, vehId, param1, param2);
    }
}

/* removeVehicleFromPool:
 * ---------------------
 * Removes vehicle from a stattion in a station's vehicle pool.
 */
void IronbendInc::removeVehicleFromPool(std::string stationName, int vehId) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            ironbendStations[i]->removeVehicleFromPool(vehId);
    }
}

/* getVehicleType:
 * ---------------
 * Returns vehicle type, by station name and vehicle id. Returns -1 if no station found.
 */
int IronbendInc::getVehicleType(std::string stationName, int vehId) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return ironbendStations[i]->getVehicleType(vehId);
    }
    return -1;
}

/* getVehicleParam1:
 * ----------------
 * Returns vehicle's parameter 1, by station name and vehicle id. Returns -1 if no station found.
 */
int IronbendInc::getVehicleParam1(std::string stationName, int vehId) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return ironbendStations[i]->getVehicleParam1(vehId);
    }
    return -1;
}

/* hasVehicleParam2:
 * ----------------
 * Returns true if a vehicle has parameter 2, by station name and vehicle id. Returns false if vehicle does not have parameter 2.
 */
bool IronbendInc::hasVehicleParam2(std::string stationName, int vehId) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return ironbendStations[i]->vehicleHasParam2(vehId);
    }
    return false;
}

/* getVehicleParam2:
 * ----------------
 * Returns vehicle's parameter 2, by station name and vehicle id. Returns -1 if no station found.
 */
int IronbendInc::getVehicleParam2(std::string stationName, int vehId) {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName())
            return ironbendStations[i]->getVehicleParam2(vehId);
    }
    return -1;
}

/* showStationNames:
 * ----------------
 * Shows all station names.
 */
void IronbendInc::showStationNames() const {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        cout << ironbendStations[i]->getStationName() << endl;
    }
}

/* showStation:
 * -----------
 * Shows a station by station name. Returns false if no station found, else returns true.
 */
bool IronbendInc::showStation(std::string stationName) const {
    bool stationFound = false;
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        if(stationName == ironbendStations[i]->getStationName()) {
            ironbendStations[i]->showStation();
            stationFound = true;
        }
    }
    return stationFound;
}

/* showAllStations:
 * ---------------
 * Shows all stations.
 */
void IronbendInc::showAllStations() const {
    for(auto i = 0; i < ironbendStations.size(); i++)
    {
        ironbendStations[i]->showStation();
    }
}
