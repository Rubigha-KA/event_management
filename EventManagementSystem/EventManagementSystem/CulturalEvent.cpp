#include "CulturalEvent.h"

#include <iostream>
#include <stdexcept>
#include <string>

CulturalEvent::CulturalEvent()
    : Event(),
      performanceCategory("General") {
}

CulturalEvent::CulturalEvent(
    int id,
    const std::string& name,
    const std::string& date,
    const std::string& venue,
    double budget,
    const std::string& category
)
    : Event(id, name, date, venue, budget),
      performanceCategory(category) {

    if (performanceCategory.empty()) {
        throw std::invalid_argument(
            "Performance category cannot be empty."
        );
    }
}

// Getter: performance category
std::string CulturalEvent::getPerformanceCategory() const {
    return performanceCategory;
}

// Display cultural event details
void CulturalEvent::displayEvent() const {
    std::cout << "\n======= CULTURAL EVENT DETAILS =======\n";

    Event::displayEvent();

    std::cout << "Performance Category: "
              << performanceCategory << '\n';

    std::cout << "======================================\n";
}

// Return the event type
std::string CulturalEvent::getEventType() const {
    return "Cultural Event";
}