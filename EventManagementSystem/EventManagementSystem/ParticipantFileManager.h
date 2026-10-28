#ifndef PARTICIPANT_FILE_MANAGER_H
#define PARTICIPANT_FILE_MANAGER_H

#include <string>

#include "ParticipantManager.h"

class ParticipantFileManager
{
public:
    // Save participant records to a file
    static bool saveParticipants(
        const ParticipantManager& manager,
        const std::string& filename
    );

    // Load participant records from a file
    static bool loadParticipants(
        ParticipantManager& manager,
        const std::string& filename
    );
};

#endif