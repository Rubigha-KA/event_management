#include "Participant.h"

#include <iostream>
#include <utility>

// Default constructor
Participant::Participant()
    : participantID(0),
      participantName(""),
      email(""),
      eventID(0)
{
}

// Parameterized constructor
Participant::Participant(
    int id,
    const std::string& name,
    const std::string& emailAddress,
    int registeredEventID
)
    : participantID(id),
      participantName(name),
      email(emailAddress),
      eventID(registeredEventID)
{
}

// Get participant ID
int Participant::getParticipantID() const
{
    return participantID;
}

// Get participant name
std::string Participant::getParticipantName() const
{
    return participantName;
}

// Get participant email
std::string Participant::getEmail() const
{
    return email;
}

// Get registered event ID
int Participant::getEventID() const
{
    return eventID;
}

// Update participant name
void Participant::setParticipantName(
    const std::string& name
)
{
    participantName = name;
}

// Update participant email
void Participant::setEmail(
    const std::string& emailAddress
)
{
    email = emailAddress;
}

// Update registered event ID
void Participant::setEventID(int id)
{
    eventID = id;
}

// Display participant details
void Participant::displayParticipant() const
{
    std::cout << "\n------------------------------\n";
    std::cout << "     PARTICIPANT DETAILS\n";
    std::cout << "------------------------------\n";

    std::cout << "Participant ID   : "
              << participantID << '\n';

    std::cout << "Participant Name : "
              << participantName << '\n';

    std::cout << "Email            : "
              << email << '\n';

    std::cout << "Registered Event : "
              << eventID << '\n';

    std::cout << "------------------------------\n";
}