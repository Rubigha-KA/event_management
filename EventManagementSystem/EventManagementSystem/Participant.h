#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>

class Participant
{
private:
    int participantID;
    std::string participantName;
    std::string email;
    int eventID;

public:
    // Default constructor
    Participant();

    // Parameterized constructor
    Participant(
        int id,
        const std::string& name,
        const std::string& emailAddress,
        int registeredEventID
    );

    // Getters
    int getParticipantID() const;
    std::string getParticipantName() const;
    std::string getEmail() const;
    int getEventID() const;

    // Setters
    void setParticipantName(const std::string& name);
    void setEmail(const std::string& emailAddress);
    void setEventID(int id);

    // Display participant details
    void displayParticipant() const;
};

#endif