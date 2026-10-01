#include "Trip.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Trip::Trip()
    : distance(0.0),
      mileage(0.0),
      fuelPrice(0.0),
      speed(0.0)
{
}

Trip::Trip(const std::string& source,
           const std::string& destination,
           double distance,
           double mileage,
           double fuelPrice,
           double speed,
           const std::string& vehicleType)
    : source(source),
      destination(destination),
      distance(distance),
      mileage(mileage),
      fuelPrice(fuelPrice),
      speed(speed),
      vehicleType(vehicleType)
{
}

const std::string& Trip::getSource() const { return source; }
const std::string& Trip::getDestination() const { return destination; }
double Trip::getDistance() const { return distance; }
double Trip::getMileage() const { return mileage; }
double Trip::getFuelPrice() const { return fuelPrice; }
double Trip::getSpeed() const { return speed; }
const std::string& Trip::getVehicleType() const { return vehicleType; }

double Trip::fuelRequired() const
{
    return distance / mileage;
}

double Trip::fuelCost() const
{
    return fuelRequired() * fuelPrice;
}

double Trip::travelTime() const
{
    return distance / speed;
}

std::string Trip::toFileString() const
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2);

    // The report screenshots show a dated, multi-line trip-history record.
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    char dateBuffer[32]{};
    std::strftime(dateBuffer, sizeof(dateBuffer),
                  "%Y-%m-%d %H:%M:%S", &localTime);

    out << "Trip Date: " << dateBuffer << "\n"
        << "Source: " << source << "\n"
        << "Destination: " << destination << "\n"
        << "Distance: " << distance << " km\n"
        << "Vehicle Type: " << vehicleType << "\n"
        << "Fuel Price: Rs. " << fuelPrice << " per litre\n"
        << "Fuel Required: " << fuelRequired() << " litres\n"
        << "Fuel Cost: Rs. " << fuelCost() << "\n"
        << "Travel Time: " << travelTime() << " hours\n"
        << "----------------------------------------\n";

    return out.str();
}
