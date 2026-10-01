#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "Trip.h"

class FileManager {
public:
    static bool saveTrip(const std::string &filename, const Trip &trip);
    static std::string loadTrips(const std::string &filename);
    static bool clearTrips(const std::string &filename);
};

#endif // FILEMANAGER_H
