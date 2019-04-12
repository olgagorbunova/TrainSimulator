//
//  Vehicle.hpp
//  ProjectTrains
//
//  Created by Olga on 2018-05-29.
//  Copyright © 2018 Olga. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp
#include "SimConst.hpp"

/* class VEHICLE:
 * -------------
 * Vehicle is an abstract base class that represents a generic vehicle concept.
 */
class Vehicle {
private:
    int vehicleId;
    
public:
    Vehicle(int id): vehicleId(id) {}
    virtual ~Vehicle() {};
    
    int getVehicleId() const {return vehicleId;}
    void setVehicleId(int id) {vehicleId = id;}
    
    virtual int getVehicleType() const = 0;
    virtual void showInfo() {};
    
    virtual int getNrPassengers() const {return 0;} //passenger
    virtual void setNrPassengers(int nrPass) {}; //passenger
    virtual int hasInternet() {return 0;} //coach
    virtual void setInternet(int internet) {}; //coach
    
    virtual int getCapacity() const {return 0;} //freight
    virtual void setCapacity(int capacity) {}; //freight
    virtual int getArea() const {return 0;} //open
    virtual void setArea(int area) {}; //open
    
    virtual int getSpeed() const {return 0;} //engine
    virtual void setSpeed(int speed) {}; //engine
    virtual int getPower() const {return 0;} //electrical
    virtual void setPower(int pow) {}; //electrical
    virtual int getFuelConsump() const {return 0;} //diesel
    virtual void setFuelConsump(int fuelConsump) {}; //diesel
    
    bool operator<(const Vehicle &v) const;
};

/* class PASSENGER:
 * ---------------
 * Derived from Vehicle. Manages information about all passenger vehicles at a higher level. Parameter 1 for all passenger vehicles is a member of this class.
 */
class Passenger: public Vehicle {
private:
    int nrPassengers; //parameter 1
    
public:
    Passenger(int vehId, int nrPass): Vehicle(vehId) {nrPassengers = nrPass;}
    virtual ~Passenger() {};
    
    virtual int getVehicleType() const = 0;
    virtual void showInfo() {};
    
    virtual int getNrPassengers() const {return nrPassengers;}
    virtual void setNrPassengers(int nrPass) {nrPassengers = nrPass;}
};

/* class FREIGHT:
 * -------------
 * Derived from Vehicle. Manages information about all freight vehicles at a higher level. Parameter 1 for all freight vehicles is a member of this class.
 */
class Freight: public Vehicle {
private:
    int capacity; //parameter 1
    
public:
    Freight(int vehId, int aCapacity): Vehicle(vehId) {capacity = aCapacity;}
    virtual ~Freight() {};
    
    virtual int getVehicleType() const = 0;
    virtual void showInfo() {};
    
    virtual int getCapacity() const {return capacity;}
    virtual void setCapacity(int aCapacity) {capacity = aCapacity;}
};

/* class ENGINE:
 * ------------
 * Derived from Vehicle. Manages information about all engine vehicles at a higher level. Parameter 1 for all engine vehicles is a member of this class.
 */
class Engine: public Vehicle {
private:
    int maxSpeed; //parameter 1
public:
    Engine(int vehId, int speed): Vehicle(vehId) {maxSpeed = speed;}
    virtual ~Engine() {};
    
    virtual int getVehicleType() const = 0;
    virtual void showInfo() {};
    
    virtual int getSpeed() const {return maxSpeed;}
    virtual void setSpeed(int speed) {maxSpeed = speed;}
};

/* class COACH:
 * -----------
 * Derived from Passenger. Manages information about passenger coach vehicle. Parameter 2 for passenger coach vehicle is a member of this class.
 */
class Coach: public Passenger {
private:
    int internetStatus; //parameter 2
    
public:
    Coach(int vehId, int nrPass, int internet): Passenger(vehId, nrPass) {internetStatus = internet;}
    virtual ~Coach() {};
    
    virtual int getVehicleType() const {return COACH_PASS;}
    virtual void showInfo();
    
    virtual int hasInternet() {return internetStatus;}
    virtual void setInternet(int internet) {internetStatus = internet;}
};

/* class SLEEPING:
 * --------------
 * Derived from Passenger. Manages information about passenger sleeping vagon vehicle.
 */
class Sleeping: public Passenger {
public:
    Sleeping(int vehId, int nrPass): Passenger(vehId, nrPass) {}
    virtual ~Sleeping() {};
    
    virtual int getVehicleType() const {return SLEEPING_PASS;}
    virtual void showInfo();
};

/* class OPEN FREIGHT:
 * ------------------
 * Derived from Freight. Manages information about open freight vehicle. Parameter 2 for open freight vehicle is a member of this class.
 */
class OpenFreight: public Freight {
private:
    int floorArea; //parameter 2
public:
    OpenFreight(int vehId, int aCapacity, int area): Freight(vehId, aCapacity) {floorArea = area;}
    virtual ~OpenFreight() {};
    
    virtual int getVehicleType() const {return OPEN_FREIGHT;}
    virtual void showInfo();
    
    virtual int getArea() const {return floorArea;}
    virtual void setArea(int area) {floorArea = area;}
};

/* class COVERED FREIGHT:
 * ---------------------
 * Derived from Freight. Manages information about covered freight vehicle.
 */
class CoveredFreight: public Freight {
public:
    CoveredFreight(int vehId, int aCapacity): Freight(vehId, aCapacity) {}
    virtual ~CoveredFreight() {};
    
    virtual int getVehicleType() const {return COVERED_FREIGHT;}
    virtual void showInfo();
};

/* class OPEN FREIGHT:
 * ------------------
 * Derived from Engine. Manages information about electrical engine vehicle. Parameter 2 for electrical engine vehicle is a member of this class.
 */
class ElectrEngine: public Engine {
private:
    int power; //parameter 2
public:
    ElectrEngine(int vehId, int speed, int pow): Engine(vehId, speed) {power = pow;}
    virtual ~ElectrEngine() {};
    
    virtual int getPower() const {return power;}
    virtual void setPower(int pow) {power = pow;}
    
    virtual int getVehicleType() const {return ELECTRICAL_ENGINE;}
    virtual void showInfo();
};

/* class DIESEL ENGINE:
 * -------------------
 * Derived from Engine. Manages information about diesel engine vehicle. Parameter 2 for diesel engine vehicle is a member of this class.
 */
class DieselEngine: public Engine {
private:
    int fuelConsumption; //parameter 2
    
public:
    DieselEngine(int vehId, int speed, int fuelConsump): Engine(vehId, speed) {fuelConsumption = fuelConsump;}
    virtual ~DieselEngine() {};
    
    virtual int getFuelConsump() const {return fuelConsumption;}
    virtual void setFuelConsump(int fuelConsump) {fuelConsumption = fuelConsump;}
    
    virtual int getVehicleType() const {return DIESEL_ENGINE;}
    virtual void showInfo();
};

#endif /* Vehicle_hpp */
