#include "Event.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

Event::Event()
    : eventID(1),
      eventName("Default Event"),
      eventDate("Not Scheduled"),
      venue("Not Assigned"),
      budget(0.0)
{
}

Event::Event(int id,
             std::string name,
             std::string date,
             std::string location,
             double eventBudget)
    : eventID(id),
      eventName(std::move(name)),
      eventDate(std::move(date)),
      venue(std::move(location)),
      budget(eventBudget)
{
    if (eventID <= 0)
        throw std::invalid_argument("Event ID must be positive.");

    if (eventName.empty())
        throw std::invalid_argument("Event name cannot be empty.");

    if (eventDate.empty())
        throw std::invalid_argument("Event date cannot be empty.");

    if (venue.empty())
        throw std::invalid_argument("Venue cannot be empty.");

    if (!std::isfinite(budget) || budget < 0)
        throw std::invalid_argument(
            "Budget must be a valid non-negative number.");
}

Event::~Event() = default;

int Event::getEventID() const
{
    return eventID;
}

std::string Event::getEventName() const
{
    return eventName;
}

std::string Event::getEventDate() const
{
    return eventDate;
}

std::string Event::getVenue() const
{
    return venue;
}

double Event::getBudget() const
{
    return budget;
}

void Event::setEventName(std::string name)
{
    if (name.empty())
        throw std::invalid_argument("Event name cannot be empty.");

    eventName = std::move(name);
}

void Event::setEventDate(std::string date)
{
    if (date.empty())
        throw std::invalid_argument("Event date cannot be empty.");

    eventDate = std::move(date);
}

void Event::setVenue(std::string location)
{
    if (location.empty())
        throw std::invalid_argument("Venue cannot be empty.");

    venue = std::move(location);
}

void Event::setBudget(double eventBudget)
{
    if (!std::isfinite(eventBudget) || eventBudget < 0)
        throw std::invalid_argument(
            "Budget must be a valid non-negative number.");

    budget = eventBudget;
}

void Event::displayEvent() const
{
    std::cout << "Event ID   : " << eventID << '\n';
    std::cout << "Event Name : " << eventName << '\n';
    std::cout << "Event Date : " << eventDate << '\n';
    std::cout << "Venue      : " << venue << '\n';
    std::cout << "Budget     : " << budget << '\n';
}

std::string Event::getEventType() const
{
    return "General Event";
}