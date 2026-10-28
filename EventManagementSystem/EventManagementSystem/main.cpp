#include "Event.h"
#include "Workshop.h"
#include "CulturalEvent.h"
#include "EventManager.h"
#include "FileManager.h"
#include "Participant.h"
#include "ParticipantManager.h"
#include "ParticipantFileManager.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace
{
    int readInt(const std::string& prompt)
    {
        int value;

        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value)
            {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                return value;
            }

            std::cout << "Invalid input. Enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double readDouble(const std::string& prompt)
    {
        double value;

        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value)
            {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                if (std::isfinite(value) && value >= 0)
                    return value;

                std::cout << "Enter a valid non-negative number.\n";
                continue;
            }

            std::cout << "Invalid input. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string readString(const std::string& prompt)
    {
        std::string value;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, value);

            if (value.empty())
            {
                std::cout << "This field cannot be empty.\n";
                continue;
            }

            if (value.find('|') != std::string::npos)
            {
                std::cout << "The character '|' is not allowed.\n";
                continue;
            }

            return value;
        }
    }

    std::unique_ptr<Event> createEvent()
    {
        std::cout << "\nSelect Event Type:\n";
        std::cout << "1. General Event\n";
        std::cout << "2. Workshop\n";
        std::cout << "3. Cultural Event\n";

        int type = readInt("Enter event type: ");

        if (type < 1 || type > 3)
            throw std::invalid_argument("Invalid event type.");

        int id = readInt("Enter Event ID: ");

        if (id <= 0)
            throw std::invalid_argument("Event ID must be positive.");

        std::string name = readString("Enter Event Name: ");
        std::string date = readString("Enter Event Date: ");
        std::string venue = readString("Enter Venue: ");
        double budget = readDouble("Enter Budget: ");

        if (type == 1)
        {
            return std::make_unique<Event>(
                id, name, date, venue, budget);
        }

        if (type == 2)
        {
            std::string instructor =
                readString("Enter Instructor Name: ");

            int duration = readInt("Enter Duration in Hours: ");

            if (duration <= 0)
                throw std::invalid_argument(
                    "Duration must be greater than zero.");

            return std::make_unique<Workshop>(
                id, name, date, venue, budget, instructor, duration);
        }

        std::string category =
            readString("Enter Performance Category: ");

        return std::make_unique<CulturalEvent>(
            id, name, date, venue, budget, category);
    }

    void displayMenu()
    {
        std::cout << "\n====================================\n";
        std::cout << "       EVENT MANAGEMENT SYSTEM\n";
        std::cout << "====================================\n";
        std::cout << "1. Add Event\n";
        std::cout << "2. Display All Events\n";
        std::cout << "3. Search Event\n";
        std::cout << "4. Update Event\n";
        std::cout << "5. Delete Event\n";
        std::cout << "6. Count Events\n";
        std::cout << "7. Participant Management\n";
        std::cout << "0. Save and Exit\n";
        std::cout << "====================================\n";
    }

    void saveParticipants(const ParticipantManager& participants)
    {
        if (!ParticipantFileManager::saveParticipants(
                participants, "participants.txt"))
        {
            std::cerr << "Warning: Participant data was not saved.\n";
        }
    }

    void participantMenu(
        ParticipantManager& participants,
        const EventManager& events)
    {
        bool running = true;

        while (running)
        {
            std::cout << "\n====================================\n";
            std::cout << "      PARTICIPANT MANAGEMENT\n";
            std::cout << "====================================\n";
            std::cout << "1. Register Participant\n";
            std::cout << "2. Display All Participants\n";
            std::cout << "3. Search Participant\n";
            std::cout << "4. Remove Participant\n";
            std::cout << "5. Count Participants\n";
            std::cout << "6. View Participants for an Event\n";
            std::cout << "0. Return to Main Menu\n";
            std::cout << "====================================\n";

            int choice = readInt("Enter your choice: ");

            switch (choice)
            {
                case 1:
                {
                    int participantID =
                        readInt("Enter Participant ID: ");

                    if (participantID <= 0)
                    {
                        std::cout
                            << "Participant ID must be positive.\n";
                        break;
                    }

                    std::string name =
                        readString("Enter Participant Name: ");

                    std::string email =
                        readString("Enter Participant Email: ");

                    int eventID = readInt("Enter Event ID: ");

                    if (eventID <= 0)
                    {
                        std::cout << "Event ID must be positive.\n";
                        break;
                    }

                    if (events.searchEvent(eventID) == nullptr)
                    {
                        std::cout
                            << "Registration failed: Event does not exist.\n";
                        break;
                    }

                    Participant participant(
                        participantID, name, email, eventID);

                    if (participants.registerParticipant(participant))
                    {
                        saveParticipants(participants);
                    }

                    break;
                }

                case 2:
                    participants.displayAllParticipants();
                    break;

                case 3:
                {
                    int id = readInt(
                        "Enter Participant ID to search: ");

                    Participant* participant =
                        participants.searchParticipant(id);

                    if (participant != nullptr)
                    {
                        participant->displayParticipant();
                    }
                    else
                    {
                        std::cout << "Participant not found.\n";
                    }

                    break;
                }

                case 4:
                {
                    int id = readInt(
                        "Enter Participant ID to remove: ");

                    if (participants.removeParticipant(id))
                    {
                        saveParticipants(participants);
                    }

                    break;
                }

                case 5:
                    std::cout << "Total Participants: "
                              << participants.getParticipantCount()
                              << '\n';
                    break;

                case 6:
                {
                    int eventID =
                        readInt("Enter Event ID: ");

                    if (events.searchEvent(eventID) == nullptr)
                    {
                        std::cout << "Event not found.\n";
                        break;
                    }

                    events.searchEvent(eventID)->displayEvent();

                    participants.displayParticipantsForEvent(eventID);

                    std::cout << "Registered Participants: "
                              << participants.getParticipantCountForEvent(
                                     eventID)
                              << '\n';

                    break;
                }

                case 0:
                    running = false;
                    break;

                default:
                    std::cout
                        << "Invalid choice. Select a valid option.\n";
                    break;
            }
        }
    }
}

int main()
{
    EventManager manager;
    ParticipantManager participants;

    try
    {
        FileManager::loadEvents(manager, "events.txt");
    }
    catch (const std::exception& error)
    {
        std::cerr << "Warning: Could not load saved events: "
                  << error.what() << '\n';
    }

    try
    {
        ParticipantFileManager::loadParticipants(
            participants, "participants.txt");
    }
    catch (const std::exception& error)
    {
        std::cerr << "Warning: Could not load participants: "
                  << error.what() << '\n';
    }

    bool running = true;

    while (running)
    {
        displayMenu();

        int choice = readInt("Enter your choice: ");

        try
        {
            switch (choice)
            {
                case 1:
                {
                    auto event = createEvent();

                    if (manager.addEvent(std::move(event)))
                    {
                        FileManager::saveEvents(manager, "events.txt");
                        std::cout << "Event added successfully!\n";
                    }
                    else
                    {
                        std::cout
                            << "Duplicate ID! Event was not added.\n";
                    }

                    break;
                }

                case 2:
                    manager.displayAllEvents();
                    break;

                case 3:
                {
                    int id = readInt("Enter Event ID to search: ");
                    Event* event = manager.searchEvent(id);

                    if (event != nullptr)
                        event->displayEvent();
                    else
                        std::cout << "Event not found.\n";

                    break;
                }

                case 4:
                {
                    int id = readInt("Enter Event ID to update: ");

                    if (manager.searchEvent(id) == nullptr)
                    {
                        std::cout << "Event not found.\n";
                        break;
                    }

                    std::string name = readString("Enter New Name: ");
                    std::string date = readString("Enter New Date: ");
                    std::string venue = readString("Enter New Venue: ");
                    double budget = readDouble("Enter New Budget: ");

                    if (manager.updateEvent(
                            id, name, date, venue, budget))
                    {
                        FileManager::saveEvents(manager, "events.txt");
                        std::cout << "Event updated successfully!\n";
                    }
                    else
                    {
                        std::cout << "Event not found.\n";
                    }

                    break;
                }

                case 5:
                {
                    int id = readInt("Enter Event ID to delete: ");

                    if (manager.deleteEvent(id))
                    {
                        FileManager::saveEvents(manager, "events.txt");
                        std::cout << "Event deleted successfully!\n";
                    }
                    else
                    {
                        std::cout << "Event not found.\n";
                    }

                    break;
                }

                case 6:
                    std::cout << "Total Events: "
                              << manager.getEventCount() << '\n';
                    break;

                case 7:
                    participantMenu(participants, manager);
                    break;

                case 0:
                    FileManager::saveEvents(manager, "events.txt");
                    saveParticipants(participants);

                    std::cout << "Data saved. Exiting program.\n";
                    running = false;
                    break;

                default:
                    std::cout
                        << "Invalid choice. Select a valid option.\n";
                    break;
            }
        }
        catch (const std::exception& error)
        {
            std::cerr << "\nError: " << error.what() << '\n';
        }
    }

    return 0;
}