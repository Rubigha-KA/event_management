#include "ParticipantFileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

// Save all participants to a file
bool ParticipantFileManager::saveParticipants(
    const ParticipantManager& manager,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open participant file for saving.\n";
        return false;
    }

    for (const auto& participant : manager.getParticipants())
    {
        file << participant.getParticipantID() << '|'
             << participant.getParticipantName() << '|'
             << participant.getEmail() << '|'
             << participant.getEventID() << '\n';

        if (!file)
        {
            std::cerr << "Error: Failed to write participant data.\n";
            return false;
        }
    }

    file.close();

    if (!file)
    {
        std::cerr << "Error: Failed to finish saving participants.\n";
        return false;
    }

    std::cout << "Participants saved successfully.\n";
    return true;
}

// Load participants from a file
bool ParticipantFileManager::loadParticipants(
    ParticipantManager& manager,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "No participant file found. Starting fresh.\n";
        return true;
    }

    std::string line;
    std::size_t loadedCount = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream stream(line);

        std::string idText;
        std::string name;
        std::string email;
        std::string eventIDText;
        std::string extra;

        if (!std::getline(stream, idText, '|') ||
            !std::getline(stream, name, '|') ||
            !std::getline(stream, email, '|') ||
            !std::getline(stream, eventIDText, '|') ||
            std::getline(stream, extra, '|'))
        {
            std::cerr << "Skipping invalid participant record.\n";
            continue;
        }

        try
        {
            std::size_t position1 = 0;
            std::size_t position2 = 0;

            int participantID = std::stoi(idText, &position1);
            int eventID = std::stoi(eventIDText, &position2);

            if (position1 != idText.size() ||
                position2 != eventIDText.size())
            {
                std::cerr << "Skipping invalid participant ID.\n";
                continue;
            }

            Participant participant(
                participantID,
                name,
                email,
                eventID
            );

            if (manager.registerParticipant(participant))
            {
                ++loadedCount;
            }
        }
        catch (const std::exception&)
        {
            std::cerr << "Skipping invalid participant record.\n";
        }
    }

    if (file.bad())
    {
        std::cerr << "Error: Failed while reading participant file.\n";
        return false;
    }

    std::cout << loadedCount
              << " participant(s) loaded successfully.\n";

    return true;
}