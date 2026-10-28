#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Event.h"

class EventManager
{
private:
    std::vector<std::unique_ptr<Event>> events;

public:
    // Add an event
    bool addEvent(std::unique_ptr<Event> event);

    // Access all events
    const std::vector<std::unique_ptr<Event>>& getEvents() const;

    // Display all events
    void displayAllEvents() const;

    // Search for an event by ID
    Event* searchEvent(int id) const;

    // Update event details
    bool updateEvent(
        int id,
        const std::string& name,
        const std::string& date,
        const std::string& venue,
        double budget
    );

    // Delete an event
    bool deleteEvent(int id);

    // Get the number of events
    std::size_t getEventCount() const;
};

#endif