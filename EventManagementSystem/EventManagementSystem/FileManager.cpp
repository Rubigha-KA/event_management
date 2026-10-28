#include "FileManager.h"

#include "Workshop.h"
#include "CulturalEvent.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{
    std::vector<std::string> splitLine(const std::string& line)
    {
        std::vector<std::string> fields;
        std::stringstream stream(line);
        std::string field;

        while (std::getline(stream, field, '|'))
        {
            fields.push_back(field);
        }

        return fields;
    }

    int parseInt(const std::string& value)
    {
        std::size_t position = 0;
        int result = std::stoi(value, &position);

        if (position != value.size())
        {
            throw std::invalid_argument("Invalid integer.");
        }

        return result;
    }

    double parseDouble(const std::string& value)
    {
        std::size_t position = 0;
        double result = std::stod(value, &position);

        if (position != value.size())
        {
            throw std::invalid_argument("Invalid number.");
        }

        return result;
    }

    void replaceFile(
        const std::string& temporaryFilename,
        const std::string& filename)
    {
#ifdef _WIN32
        if (!MoveFileExA(
                temporaryFilename.c_str(),
                filename.c_str(),
                MOVEFILE_REPLACE_EXISTING |
                MOVEFILE_WRITE_THROUGH))
        {
            throw std::runtime_error(
                "Unable to replace the event data file. "
                "Check whether the file is open or write-protected.");
        }
#else
        if (std::rename(
                temporaryFilename.c_str(),
                filename.c_str()) != 0)
        {
            throw std::runtime_error(
                "Unable to replace the event data file.");
        }
#endif
    }
}

void FileManager::saveEvents(
    const EventManager& manager,
    const std::string& filename)
{
    const std::string temporaryFilename = filename + ".tmp";

    {
        std::ofstream file(temporaryFilename);

        if (!file)
        {
            throw std::runtime_error(
                "Unable to open temporary file for saving.");
        }

        for (const auto& event : manager.getEvents())
        {
            if (!event)
            {
                continue;
            }

            if (const auto* workshop =
                    dynamic_cast<const Workshop*>(event.get()))
            {
                file << "WORKSHOP|"
                     << workshop->getEventID() << '|'
                     << workshop->getEventName() << '|'
                     << workshop->getEventDate() << '|'
                     << workshop->getVenue() << '|'
                     << workshop->getBudget() << '|'
                     << workshop->getInstructorName() << '|'
                     << workshop->getDurationHours() << '\n';
            }
            else if (const auto* cultural =
                         dynamic_cast<const CulturalEvent*>(event.get()))
            {
                file << "CULTURAL|"
                     << cultural->getEventID() << '|'
                     << cultural->getEventName() << '|'
                     << cultural->getEventDate() << '|'
                     << cultural->getVenue() << '|'
                     << cultural->getBudget() << '|'
                     << cultural->getPerformanceCategory() << '\n';
            }
            else
            {
                file << "EVENT|"
                     << event->getEventID() << '|'
                     << event->getEventName() << '|'
                     << event->getEventDate() << '|'
                     << event->getVenue() << '|'
                     << event->getBudget() << '\n';
            }

            if (!file)
            {
                throw std::runtime_error(
                    "Failed while writing event records.");
            }
        }

        file.close();

        if (!file)
        {
            throw std::runtime_error(
                "Failed to finish saving event records.");
        }
    }

    replaceFile(temporaryFilename, filename);

    std::cout << "Events saved successfully.\n";
}

void FileManager::loadEvents(
    EventManager& manager,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cout
            << "No saved event file found. Starting fresh.\n";
        return;
    }

    std::string line;
    std::size_t loadedCount = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        try
        {
            const auto fields = splitLine(line);

            if (fields.empty())
            {
                continue;
            }

            const std::string& type = fields[0];
            std::unique_ptr<Event> event;

            if (type == "EVENT" && fields.size() == 6)
            {
                event = std::make_unique<Event>(
                    parseInt(fields[1]),
                    fields[2],
                    fields[3],
                    fields[4],
                    parseDouble(fields[5]));
            }
            else if (type == "WORKSHOP" && fields.size() == 8)
            {
                event = std::make_unique<Workshop>(
                    parseInt(fields[1]),
                    fields[2],
                    fields[3],
                    fields[4],
                    parseDouble(fields[5]),
                    fields[6],
                    parseInt(fields[7]));
            }
            else if (type == "CULTURAL" && fields.size() == 7)
            {
                event = std::make_unique<CulturalEvent>(
                    parseInt(fields[1]),
                    fields[2],
                    fields[3],
                    fields[4],
                    parseDouble(fields[5]),
                    fields[6]);
            }
            else
            {
                std::cerr
                    << "Skipping invalid event record.\n";
                continue;
            }

            if (manager.addEvent(std::move(event)))
            {
                ++loadedCount;
            }
            else
            {
                std::cerr
                    << "Skipping duplicate event ID.\n";
            }
        }
        catch (const std::exception& error)
        {
            std::cerr << "Skipping invalid record: "
                      << error.what() << '\n';
        }
    }

    if (file.bad())
    {
        throw std::runtime_error(
            "An error occurred while reading events.");
    }

    std::cout << loadedCount
              << " event(s) loaded successfully.\n";
}