//
//  Train.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-30.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Train_hpp
#define Train_hpp

#include <string>
#include <memory>
#include <vector>
#include "Time.hpp"
#include "Vehicle.hpp"

/* class TRAIN:
 * ------------
 * Class updates and provides train information. It uses vector of pointers to Vehicle objects to store information about which vagons a train contains.
 */
class Train {
protected:
    int trainNumber;
    int trainState;
    std::string deptStation;
    std::string destStation;
    Time deptTime;
    Time destTime;
    int maxSpeed;
    double avgSpeed;
    
    std::vector<std::unique_ptr<Vehicle>> train;

public:
    Train(int tNum, std::string depStn, std::string desStn, Time depTime, Time desTime, int mSpeed, int tState = 0, double speed = 0): trainNumber(tNum), trainState(tState), deptStation(depStn), destStation(desStn), deptTime(depTime), maxSpeed(mSpeed), destTime(desTime), avgSpeed(speed) {};
    
    int getTrainNumber() const {return trainNumber;}
    void setTrainNumber(int tNum) {trainNumber = tNum;}
    
    int getTrainState() const {return trainState;}
    void setTrainState(int tState) {trainState = tState;}
    
    std::string getDeptStation() const {return deptStation;}
    void setDeptStation(std::string depStn) {deptStation = depStn;}
    std::string getDestStation() const {return destStation;}
    void setDestStation(std::string desStn) {destStation = desStn;}
    
    Time getDeptTime() const {return deptTime;}
    void setDeptTime(Time depTime) {deptTime = depTime;}
    Time getDestTime() const {return destTime;}
    void setDestTime(Time desTime) {destTime = desTime;}
    
    int getMaxSpeed() const {return maxSpeed;}
    void setMaxSpeed(int mSpeed) {maxSpeed = mSpeed;}
    
    int getVehicleType(Vehicle &a);
    int getNrVehicles();
    
    void updateVehicle(int vehType, int vehIdNew, int param1, int param2);
    void detachVehicle(int vehIdx, int &vehType, int &vehId, int &param1, int &param2);
    
    int findTrainByVehicle(int vehId);
    
    bool vehicleMissing(int vehIndex, int &missingVehType);
    
    void addVehicle(int vehType, int vehId, int param1, int param2 = 0);
    bool showVehicle(int vehId) const;
    void showAllVehicles();
    void showTrain();
    
    //void orderVehicles();
};
//bool greaterVeh(const std::unique_ptr<Vehicle> &a, const std::unique_ptr<Vehicle> &b);
#endif /* Train_hpp */
