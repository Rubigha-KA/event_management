#ifndef WORKSHOP_H
#define WORKSHOP_H

#include "Event.h"
#include <string>

class Workshop : public Event {
private:
    std::string instructorName;
    int durationHours;

public:
    // Default constructor
    Workshop();

    // Parameterized constructor
    Workshop(
        int id,
        const std::string& name,
        const std::string& date,
        const std::string& venue,
        double budget,
        const std::string& instructor,
        int duration
    );

    // Destructor
    ~Workshop() override = default;

    // Getter methods
    std::string getInstructorName() const;
    int getDurationHours() const;

    // Overridden virtual functions
    void displayEvent() const override;
    std::string getEventType() const override;
};

#endif