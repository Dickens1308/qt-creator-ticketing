# Bus Ticket Booking System

A Qt-based desktop application for managing bus ticket bookings and reservations.

## System Requirements

- Ubuntu 20.04 or later
- Qt 5.12 or later
- SQLite 3
- C++11 compatible compiler
- CMake 3.10 or later

## Dependencies

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    qt5-default \
    qttools5-dev \
    qttools5-dev-tools \
    libqt5sql5-sqlite \
    cmake

```

# Buid instructions
#### 1. Clone the repository 
```bash
git clone https://github.com/yourusername/bus-ticket-system.git
cd bus-ticket-system
```

#### 2. Create build directory:
```bash
mkdir build
cd build
```

#### 3. Confugure and build:
```bash
cmake ..
make
./bus-ticket-system
```

# Project Structure

```bash
UiSystem/
├── src/
│   ├── mainwindow.cpp
│   ├── bookingdialog.cpp
│   ├── ticketdialog.cpp
│   └── historydialog.cpp
├── include/
│   ├── mainwindow.h
│   ├── bookingdialog.h
│   ├── ticketdialog.h
│   └── historydialog.h
├── ui/
│   ├── mainwindow.ui
│   ├── bookingdialog.ui
│   ├── ticketdialog.ui
│   └── historydialog.ui
└── database/
    └── login.db
```
