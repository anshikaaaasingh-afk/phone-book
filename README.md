# Phone Book (Contact Manager) 📇

A terminal-based Phone Book application written in C. Add, search, edit,
delete, and store contacts — with data saved to a file so nothing is lost
between runs.

## About

This project is a simple command-line contact manager that lets you keep
track of names and phone numbers directly from the terminal, using file
handling for persistent storage.

## Demo

```
===== PHONE BOOK =====
1. Add Contact
2. View All Contacts
3. Search Contact
4. Edit Contact
5. Delete Contact
6. Exit
Enter your choice: 1

Enter name: Anshika
Enter phone number: 9876543210
Contact added successfully!
```

## Features

- Add new contacts (name + phone number)
- View all saved contacts in a list
- Search for a contact by name
- Edit an existing contact's details
- Delete a contact
- Persistent storage — contacts are saved to a file and reloaded next time
- Input validation to avoid duplicate or malformed entries

## Getting Started

### Prerequisites

- A C compiler (`gcc` or similar)

### Compile

```bash
gcc -o phonebook phonebook.c
```

### Run

```bash
./phonebook
```

## How It Works

- Contacts are stored using a struct with fields for name and phone number.
- All contacts are saved to a local file (e.g. `contacts.txt` or
  `contacts.dat`) so your data persists across sessions.
- A simple menu-driven loop lets you pick an action each time the program runs.

## Project Structure

```
phone-book/
├── phonebook.c    # Main program logic
├── contacts.txt   # Saved contact data (created automatically)
└── README.md      # This file
```

## Future Improvements

- Sort contacts alphabetically
- Add email addresses or multiple phone numbers per contact
- Search by phone number as well as name
- Switch storage to a binary file or simple database format

## License

Free to use and modify for personal or educational purposes.
