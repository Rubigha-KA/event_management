#include "Workshop.h"

#include <iostream>
#include <stdexcept>
#include <string>

Workshop::Workshop()
    : Event(),
      instructorName("Not Assigned"),
      durationHours(1) {
}

Workshop::Workshop(
    int id,
    const std::string& name,
    const std::string& date,
    const std::string& venue,
    double budget,
    const std::string& instructor,
    int duration
)
    : Event(id, name, date, venue, budget),
      instructorName(instructor),
      durationHours(duration) {

    if (instructorName.empty()) {
        throw std::invalid_argument(
            "Instructor name cannot be empty."
        );
    }

    if (durationHours <= 0) {
        throw std::invalid_argument(
            "Workshop duration must be greater than zero."
        );
    }
}

// Getter: instructor name
std::string Workshop::getInstructorName() const {
    return instructorName;
}

// Getter: duration in hours
int Workshop::getDurationHours() const {
    return durationHours;
}

// Display workshop details
void Workshop::displayEvent() const {
    std::cout << "\n========== WORKSHOP DETAILS ==========\n";

    Event::displayEvent();

    std::cout << "Instructor Name : "
              << instructorName << '\n';

    std::cout << "Duration (Hours): "
              << durationHours << '\n';

    std::cout << "======================================\n";
}

// Return the event type
std::string Workshop::getEventType() const {
    return "Workshop";
}