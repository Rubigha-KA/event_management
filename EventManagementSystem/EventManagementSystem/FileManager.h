#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "EventManager.h"
#include <string>

class FileManager {
public:
    static void saveEvents(const EventManager& manager,
                           const std::string& filename);

    static void loadEvents(EventManager& manager,
                           const std::string& filename);
};

#endif