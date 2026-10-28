#ifndef CULTURALEVENT_H
#define CULTURALEVENT_H

#include "Event.h"
#include <string>

class CulturalEvent : public Event {
private:
    std::string performanceCategory;

public:
    // Default constructor
    CulturalEvent();

    // Parameterized constructor
    CulturalEvent(
        int id,
        const std::string& name,
        const std::string& date,
        const std::string& venue,
        double budget,
        const std::string& category
    );

    // Destructor
    ~CulturalEvent() override = default;

    // Getter method
    std::string getPerformanceCategory() const;

    // Overridden virtual functions
    void displayEvent() const override;
    std::string getEventType() const override;
};

#endif