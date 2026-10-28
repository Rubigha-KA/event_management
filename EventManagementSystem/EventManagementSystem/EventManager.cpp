#include "EventManager.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

bool EventManager::addEvent(std::unique_ptr<Event> event)
{
    if (!event)
        throw std::invalid_argument("Cannot add an empty event.");

    if (searchEvent(event->getEventID()) != nullptr)
        return false;

    events.push_back(std::move(event));
    return true;
}

void EventManager::displayAllEvents() const
{
    if (events.empty())
    {
        std::cout << "\nNo events are currently available.\n";
        return;
    }

    std::cout << "\n========== ALL EVENTS ==========\n";

    for (const auto& event : events)
    {
        if (event)
        {
            event->displayEvent();

            std::cout << "Event Type : "
                      << event->getEventType() << '\n';

            std::cout << "--------------------------------\n";
        }
    }
}

Event* EventManager::searchEvent(int id) const
{
    for (const auto& event : events)
    {
        if (event && event->getEventID() == id)
            return event.get();
    }

    return nullptr;
}

bool EventManager::updateEvent(
    int id,
    const std::string& name,
    const std::string& date,
    const std::string& location,
    double eventBudget)
{
    Event* event = searchEvent(id);

    if (event == nullptr)
        return false;

    if (name.empty())
        throw std::invalid_argument("Event name cannot be empty.");

    if (date.empty())
        throw std::invalid_argument("Event date cannot be empty.");

    if (location.empty())
        throw std::invalid_argument("Venue cannot be empty.");

    if (!std::isfinite(eventBudget) || eventBudget < 0)
        throw std::invalid_argument(
            "Budget must be a valid non-negative number.");

    event->setEventName(name);
    event->setEventDate(date);
    event->setVenue(location);
    event->setBudget(eventBudget);

    return true;
}

bool EventManager::deleteEvent(int id)
{
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        if (*it && (*it)->getEventID() == id)
        {
            events.erase(it);
            return true;
        }
    }

    return false;
}

std::size_t EventManager::getEventCount() const
{
    return events.size();
}

const std::vector<std::unique_ptr<Event>>&
EventManager::getEvents() const
{
    return events;
}