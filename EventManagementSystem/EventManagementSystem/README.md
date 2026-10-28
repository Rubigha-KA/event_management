# Event Management System Using C++

A menu-driven C++ application for managing events and participant registrations using Object-Oriented Programming (OOP).

## Project Overview

The Event Management System helps users organize event information and maintain participant records. It supports event creation, searching, updating, deletion, and participant registration.

The project demonstrates how C++ classes, inheritance, polymorphism, file handling, and input validation can be applied to a practical management application.

## Features

### Event Management

* Add new events
* Display all events
* Search events by ID
* Update event details
* Delete events
* Count registered events

### Participant Management

* Register participants for existing events
* Display all participants
* Search participants by ID
* Remove participants
* Count participants
* Display participants associated with a particular event

### Additional Features

* Save and load event records using text files
* Save and load participant records using text files
* Validate user input
* Reject duplicate participant IDs and email addresses
* Check whether an event exists before participant registration

## Object-Oriented Programming Concepts

* **Encapsulation:** Protecting data through private members and public member functions.
* **Abstraction:** Providing manager classes with simple operations for managing records.
* **Inheritance:** Deriving `Workshop` and `CulturalEvent` from the base `Event` class.
* **Polymorphism:** Using virtual functions and overridden behavior for different event types.

## Technologies Used

* C++
* C++17
* GCC/G++
* Visual Studio Code
* Text-file handling

## Project Structure

```text
EventManagementSystem/
├── main.cpp
├── Event.h
├── Event.cpp
├── Workshop.h
├── Workshop.cpp
├── CulturalEvent.h
├── CulturalEvent.cpp
├── EventManager.h
├── EventManager.cpp
├── FileManager.h
├── FileManager.cpp
├── Participant.h
├── Participant.cpp
├── ParticipantManager.h
├── ParticipantManager.cpp
├── ParticipantFileManager.h
├── ParticipantFileManager.cpp
├── README.md
└── .gitignore
```

The exact files may vary with the final project version.

## Requirements

* A C++17-compatible compiler
* GCC/G++ installed and accessible from the terminal

## How to Compile

Open a terminal in the project directory and run:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp Event.cpp Workshop.cpp CulturalEvent.cpp EventManager.cpp FileManager.cpp Participant.cpp ParticipantManager.cpp ParticipantFileManager.cpp -o EventManagementSystem.exe
```

## How to Run

On Windows PowerShell:

```powershell
.\EventManagementSystem.exe
```

On systems where the executable is named differently, use the corresponding executable name.

## Data Storage

The application uses text files to save and restore event and participant information between program runs.

## Future Enhancements

* Graphical user interface
* Database integration
* Event capacity management
* Participant update functionality
* Improved reporting and search
* Login and access control

## Author

**Riya D.**

GitHub: [riyachristinadavid-rgb](https://github.com/riyachristinadavid-rgb)

## Academic Project

Developed as a C++ Object-Oriented Programming mini project.
