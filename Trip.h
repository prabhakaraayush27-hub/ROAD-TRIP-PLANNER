#ifndef TRIP_H
#define TRIP_H

#include <string>

class Trip
{
public:
    Trip();
    Trip(const std::string& source,
         const std::string& destination,
         double distance,
         double mileage,
         double fuelPrice,
         double speed,
         const std::string& vehicleType);

    const std::string& getSource() const;
    const std::string& getDestination() const;
    double getDistance() const;
    double getMileage() const;
    double getFuelPrice() const;
    double getSpeed() const;
    const std::string& getVehicleType() const;

    double fuelRequired() const;
    double fuelCost() const;
    double travelTime() const;

    std::string toFileString() const;

private:
    std::string source;
    std::string destination;
    double distance;
    double mileage;
    double fuelPrice;
    double speed;
    std::string vehicleType;
};

#endif // TRIP_H
