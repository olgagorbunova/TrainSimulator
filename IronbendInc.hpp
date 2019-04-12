//
//  IronbendInc.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-31.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef IronbendInc_hpp
#define IronbendInc_hpp

#include <memory>
#include <vector>
#include <string>
#include "Train.hpp"
#include "Station.hpp"
#include "Time.hpp"


/* class IRONBEND INC:
 * ------------------
 * Class handles information for all simulation components: train, vehicles and stations. Information is accesible via classes vectors of pointers to Train and Station objects.
 * Information for the simulation components can be read and written by calling the class functions.
 */
class IronbendInc {
private:
    std::vector<std::unique_ptr<Train>> ironbendTrains;
    std::vector<std::unique_ptr<Station>> ironbendStations;
public:
    IronbendInc() {}
    
    void addTrain(int tNum, std::string depStn, std::string desStn, Time depTime, Time desTime, int mSpeed, int tState = 0, double speed = 0);
    
    void addVehicleToTrain(int trainNum, int vehType, int vehId, int param1, int param2 = 0);
    
    std::string getDeptStation(int trainNum) const;
    std::string getArrStation(int trainNum) const;
    bool getDeptTime(int trainNum, Time &t);
    bool getArrTime(int trainNum, Time &t);
    int getTrainState(int trainNum) const;
    void setTrainState(int trainNum, int state);
    int getTrainMaxSpeed(int trainNum) const;
    
    double getTrainAvgSpeed(int trainNum);
    
    bool assembleTrain(int trainNum);
    void diassembleTrain(int trainNum);
    
    bool showTrain(int trainNum) const;
    bool showTrainByVeh(int vehId) const;
    void showTrainByState(int state) const;
    void showAllTrains() const;
    
    bool showVehicle(int vehId) const;
    void showAllVehicles() const;
    
    bool stationFound(std::string stationName);
    void addStation(std::string stationName);
    void addDistance(std::string stationName, std::string destination, int km);
    int getDistance(std::string stationName, std::string destination) const;
    
    void addVehicleToPool(std::string stationName, int vehType, int vehId, int param1, int param2 = 0);
    void removeVehicleFromPool(std::string stationName, int vehId);
    
    int getVehicleType(std::string stationName, int vehId);
    int getVehicleParam1(std::string stationName, int vehId);
    bool hasVehicleParam2(std::string stationName, int vehId);
    int getVehicleParam2(std::string stationName, int vehId);
    
    void showStationNames() const;
    bool showStation(std::string stationName) const;
    void showAllStations() const;
};
#endif /* IronbendInc_hpp */
