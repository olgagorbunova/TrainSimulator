//
//  Station.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Station_hpp
#define Station_hpp

#include "Vehicle.hpp"
#include <map>
#include <string>
#include <vector>

/* class TRAIN:
 * ------------
 * Class updates and provides station information. It uses vector of pointers to Vehicle objects to store information about which vagons are available at a station pool, as well as a map container to store information about other stations that you can travel to from this station, as well as distances to them.
 */
class Station {
private:
    std::string stationName;
    std::map<std::string, int> distances;
    std::vector<std::unique_ptr<Vehicle>> vehiclePool;
    
public:
    Station(std::string sName):stationName(sName) {};
    
    std::string getStationName() const {return stationName;}
    void setStationName(std::string sName) {stationName = sName;}
    
    void addDistance(std::string destination, int km);
    int getDistance(std::string destination) const;
    
    void addVehicleToPool(int vehType, int vehId, int param1, int param2 = 0);
    void removeVehicleFromPool(int vehId);
    
    bool hasVehicle(int vehType, int &vehId);
    
    int getVehicleType(int vehId);
    int getVehicleParam1(int vehId);
    bool vehicleHasParam2(int vehId);
    int getVehicleParam2(int vehId);
    
    void showStation() const;
    bool showVehicle(int vehId) const;
    void showAllVehicles() const;
    
    void orderVehPoolById();
};
bool greaterVeh(const std::unique_ptr<Vehicle> &a, const std::unique_ptr<Vehicle> &b);

#endif /* Station_hpp */
