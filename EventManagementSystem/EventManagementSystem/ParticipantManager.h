#ifndef PARTICIPANTMANAGER_H
#define PARTICIPANTMANAGER_H

#include "Participant.h"

#include <cstddef>
#include <string>
#include <vector>

class ParticipantManager
{
private:
    std::vector<Participant> participants;

public:
    // Register a participant
    bool registerParticipant(const Participant& participant);

    // Display all registered participants
    void displayAllParticipants() const;

    // Search for a participant by ID
    Participant* searchParticipant(int participantID);

    // Remove a participant by ID
    bool removeParticipant(int participantID);

    // Count registered participants
    std::size_t getParticipantCount() const;

    // Access all participants
    const std::vector<Participant>& getParticipants() const;

    // Check whether a participant ID exists
    bool participantExists(int participantID) const;

    // Check whether an email is already registered
    bool emailExists(const std::string& email) const;

    // Display participants registered for a particular event
    void displayParticipantsForEvent(int eventID) const;

    // Count participants registered for a particular event
    std::size_t getParticipantCountForEvent(int eventID) const;
};

#endif