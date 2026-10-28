#include "ParticipantManager.h"

#include <algorithm>
#include <iostream>

// Register a new participant
bool ParticipantManager::registerParticipant(
    const Participant& participant)
{
    if (participantExists(participant.getParticipantID()))
    {
        std::cout << "Error: Participant ID already exists.\n";
        return false;
    }

    if (emailExists(participant.getEmail()))
    {
        std::cout << "Error: Email is already registered.\n";
        return false;
    }

    participants.push_back(participant);

    std::cout << "Participant registered successfully.\n";
    return true;
}

// Display all registered participants
void ParticipantManager::displayAllParticipants() const
{
    if (participants.empty())
    {
        std::cout << "No participants registered yet.\n";
        return;
    }

    std::cout << "\n========== ALL PARTICIPANTS ==========\n";

    for (const Participant& participant : participants)
    {
        participant.displayParticipant();
    }
}

// Search for a participant by ID
Participant* ParticipantManager::searchParticipant(int participantID)
{
    for (Participant& participant : participants)
    {
        if (participant.getParticipantID() == participantID)
        {
            return &participant;
        }
    }

    return nullptr;
}

// Remove a participant by ID
bool ParticipantManager::removeParticipant(int participantID)
{
    auto iterator = std::find_if(
        participants.begin(),
        participants.end(),
        [participantID](const Participant& participant)
        {
            return participant.getParticipantID() == participantID;
        });

    if (iterator == participants.end())
    {
        std::cout << "Participant not found.\n";
        return false;
    }

    participants.erase(iterator);

    std::cout << "Participant removed successfully.\n";
    return true;
}

// Count all registered participants
std::size_t ParticipantManager::getParticipantCount() const
{
    return participants.size();
}

// Check whether a participant ID already exists
bool ParticipantManager::participantExists(int participantID) const
{
    for (const Participant& participant : participants)
    {
        if (participant.getParticipantID() == participantID)
        {
            return true;
        }
    }

    return false;
}

// Check whether an email is already registered
bool ParticipantManager::emailExists(const std::string& email) const
{
    for (const Participant& participant : participants)
    {
        if (participant.getEmail() == email)
        {
            return true;
        }
    }

    return false;
}

// Display participants registered for a particular event
void ParticipantManager::displayParticipantsForEvent(int eventID) const
{
    bool found = false;

    std::cout << "\nParticipants registered for Event ID: "
              << eventID << '\n';

    for (const Participant& participant : participants)
    {
        if (participant.getEventID() == eventID)
        {
            participant.displayParticipant();
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No participants registered for this event.\n";
    }
}

// Count participants registered for a particular event
std::size_t ParticipantManager::getParticipantCountForEvent(
    int eventID) const
{
    std::size_t count = 0;

    for (const Participant& participant : participants)
    {
        if (participant.getEventID() == eventID)
        {
            ++count;
        }
    }

    return count;
}
// Access all registered participants
const std::vector<Participant>&
ParticipantManager::getParticipants() const
{
    return participants;
}