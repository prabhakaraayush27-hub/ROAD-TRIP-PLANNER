#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace {
// Runtime copy of saved trip records, as described in the report.
std::vector<Trip> runtimeTrips;
}

bool FileManager::saveTrip(const std::string &filename, const Trip &trip)
{
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
        return false;

    file << trip.toFileString() << "\n";
    runtimeTrips.push_back(trip);
    return true;
}

std::string FileManager::loadTrips(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return "";

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool FileManager::clearTrips(const std::string &filename)
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open())
        return false;

    runtimeTrips.clear();
    return true;
}
