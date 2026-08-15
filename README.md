# 🔐 Anti-Theft Locker System

An Arduino-based electronic locker security system developed and tested in the Wokwi simulator. It combines password authentication, a 4×4 keypad, 16×2 LCD, servo locking, red/green status LEDs, an audible alarm, failed-attempt detection, and automatic relocking.

## 🎯 Project Overview

The system allows a user to enter a password through a keypad. The Arduino verifies the password and controls the locker:

- Correct password → access is granted and the servo unlocks the locker.
- Incorrect password → access is denied and the failed-attempt counter increases.
- Three failed attempts → security alert and alarm are activated; the system remains locked.
- Successful access → the locker automatically returns to the locked position after approximately 5 seconds.

The complete circuit is represented by `diagram.json` and was tested in Wokwi.

## ✨ Features

- 🔑 Password-based authentication
- 🔢 4×4 keypad input
- 📟 16×2 LCD status messages
- 🟢 Green LED for successful access
- 🔴 Red LED for failed access/security alert
- 🔊 Buzzer security alarm
- ⚙️ Servo-based lock/unlock mechanism
- 🚨 Three-attempt security protection
- 🔒 Automatic relocking
- 🖥️ Serial Monitor status/debug messages
- 🧪 Complete Wokwi simulation and functional testing

**Demo password:** `1234`  
Press `#` to submit and `*` to clear.

> For this educational simulation, the password is stored directly in the Arduino source code.

## 🧰 Hardware Requirements

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| 16×2 LCD | User/status display |
| 4×4 Keypad | Password input |
| Servo Motor | Lock/unlock mechanism |
| Green LED | Access granted |
| Red LED | Access denied/security |
| Buzzer | Security alarm |
| Resistors | LED current limiting |
| Jumper wires | Connections |

## 💻 Software Requirements

- Wokwi Arduino Simulator
- Arduino C/C++
- `LiquidCrystal`
- `Keypad`
- `Servo`

The required libraries are listed in `libraries.txt`.

## 📁 Repository Structure

```text
anti-theft-locker-system/
├── electronic-safe.ino   # Main Arduino program
├── diagram.json          # Exact Wokwi circuit configuration
├── libraries.txt         # Required libraries
└── README.md             # Project documentation
```

## 🔌 Wiring / Pin Configuration

The exact circuit is stored in `diagram.json`.

| Component | Arduino connection |
|---|---|
| Servo signal | D6 |
| LCD | D12, D11, D10, D9, D8, D7 |
| Keypad rows | D5, D4, D3, D2 |
| Keypad columns | A3, A2, A1, A0 |
| Green LED | A4 |
| Red LED | A5 |
| Buzzer | D13 |

The LEDs are connected through resistors. The exact component placement and wiring are defined by `diagram.json`.

## ▶️ Wokwi Simulation Instructions

1. Open the project in Wokwi.
2. Ensure `electronic-safe.ino`, `diagram.json`, and `libraries.txt` are present.
3. Click **Play** to start the simulation.
4. Wait for the startup screen.
5. When the LCD displays `ENTER PASSWORD:`, enter a test input using the keypad.
6. Press `#` to submit.
7. Press `*` to clear an entry.

### Successful-access test

Enter:

```text
1234#
```

Expected behavior:

```text
ACCESS GRANTED
LOCKER OPEN
```

The green LED turns on, the servo moves to the unlock position, and after approximately 5 seconds the locker automatically locks.

### Failed-access test

Enter an incorrect password and press `#`.

Expected behavior:

```text
ACCESS DENIED
ATTEMPT: 1/3
```

Repeat incorrect entries to reach the security-alert state.

## 🧪 Test Results

| Test Case | Input / Condition | Expected Result | Observed Result | Status |
|---|---|---|---|---|
| Successful access | `1234#` | Access granted; green LED; servo unlocks | Access granted and locker opened | ✅ PASS |
| Failed attempt 1 | Wrong password + `#` | Access denied; 1/3 shown | Access denied; counter shown | ✅ PASS |
| Failed attempt 2 | Wrong password + `#` | Access denied; 2/3 shown | Access denied; counter shown | ✅ PASS |
| Failed attempt 3 | Wrong password + `#` | Security alert | Alert/alarm activated | ✅ PASS |
| Security alert | Three failed attempts | Red LED + buzzer | Red LED and buzzer activated | ✅ PASS |
| System locked | Alarm completed | Reset required | `SYSTEM LOCKED / RESET REQUIRED` | ✅ PASS |
| Automatic locking | Successful access + delay | Servo returns to lock position | `AUTO LOCKED / SAFE` | ✅ PASS |

## 🔄 System Flow

```text
System Starts
     ↓
Locker Locked
     ↓
Enter Password
     ↓
Check Password
   ↙       ↘
Correct   Incorrect
  ↓          ↓
Unlock    Attempt +1
  ↓          ↓
5 sec    Attempts < 3?
  ↓       ↙       ↘
Auto Lock Yes      No
  ↓       ↓         ↓
Locked  Try Again  Alarm
                    ↓
               System Locked
                Reset Required
```

## 🧠 Main Program Functions

- `setup()` — initializes hardware and startup state.
- `loop()` — reads keypad input.
- `handleKeyPress()` — handles numbers, `#`, and `*`.
- `checkPassword()` — validates the entered password.
- `accessGranted()` — unlocks the locker.
- `accessDenied()` — handles incorrect passwords.
- `activateAlarm()` — handles three failed attempts.
- `autoLock()` — returns the servo to the lock position.
- `showEnterPassword()` — displays the password-entry screen.

## 🐙 GitHub Usage

### Clone the repository

```bash
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd anti-theft-locker-system
```

### Reproduce the project

Open the repository files and import/use `diagram.json` with the Arduino source in Wokwi.

### Update the project

```bash
git add .
git commit -m "Update anti-theft locker system"
git push
```

The repository should contain the source code, circuit configuration, library list, and documentation so another student can understand and reproduce the simulation.

## 📝 Limitations

This is an educational embedded-system simulation, not a production security product. The password is stored in source code for demonstration. A physical security implementation would need secure credential storage, stronger mechanical protection, power management, enclosure design, and tamper protection.

## 🏆 Project Outcome

The completed project demonstrates:

**Password Authentication → Access Control → Servo Unlocking → Failed-Attempt Detection → Security Alarm → System Lock → Automatic Relocking**

It provides practical experience in embedded-system programming, hardware interfacing, simulation, testing, debugging, documentation, and project presentation.

## 🤖 AI-Assisted Development

This project was developed as part of an AI-assisted project execution activity. AI/ChatGPT was used for guidance during planning, implementation, debugging, testing, documentation, and project presentation. The final circuit was assembled and the program was executed and tested in Wokwi.

---

**Project:** Anti-Theft Locker System  
**Platform:** Arduino Uno + Wokwi  
**Domain:** Embedded Systems / Security  
**Status:** ✅ Completed and Tested
