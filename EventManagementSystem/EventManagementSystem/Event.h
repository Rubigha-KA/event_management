#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    int eventID;
    std::string eventName;
    std::string eventDate;
    std::string venue;
    double budget;

public:
    // Default constructor
    Event();

    // Parameterized constructor
    Event(int id, std::string name, std::string date,
          std::string location, double eventBudget);

    // Virtual destructor
    virtual ~Event();

    // Setters
    void setEventID(int id);
    void setEventName(std::string name);
    void setEventDate(std::string date);
    void setVenue(std::string location);
    void setBudget(double eventBudget);

    // Getters
    int getEventID() const;
    std::string getEventName() const;
    std::string getEventDate() const;
    std::string getVenue() const;
    double getBudget() const;

    // Virtual function for polymorphism
    virtual void displayEvent() const;

    // Identify the type of event
    virtual std::string getEventType() const;
};

#endif