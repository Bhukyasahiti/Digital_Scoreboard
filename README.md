# Digital_Scoreboard
# 🧾 README – Digital Scoreboard Using ESP32

##  Project Overview

This project implements a **Bluetooth-enabled digital scoreboard** designed for two-player games like table tennis. It uses an **ESP32 microcontroller**, **MAX7219-controlled 7-segment displays**, and **smartphone-based Bluetooth control** to allow players to **increment, decrement, or reset scores** in real-time.

---

##  Objectives

- Replace manual scorekeeping with a **wireless, user-friendly solution**.
- Ensure **real-time score updates** displayed clearly on a 7-segment module.
- Support **Bluetooth-based commands** and **physical buttons** for score control.

---

##  Components Used

- **ESP32 microcontroller** (with inbuilt Bluetooth and Wi-Fi)  
- **MAX7219-based 8-digit 7-segment display**  
- **Smartphone** with Bluetooth Serial Terminal App  
- **Pushbuttons** for manual control (Player 1, Player 2, Reset)  
- **Buzzer** for score change feedback  
- **Power supply** (via USB)

---

##  System Workflow

1. **Initialization:** ESP32 starts and connects via Bluetooth.  
2. **Input Control:**  
   - Bluetooth commands (`P1+`, `P2+`, `P1-`, `P2-`, `RESET`) from smartphone  
   - Pushbuttons for direct control  
3. **Processing:** Commands are interpreted by the ESP32.  
4. **Display Output:** Scores are updated in real-time.  
5. **Persistence:** Scores saved using Preferences memory.

---

##  Bluetooth Command Format

| Command | Action                     |
|---------|----------------------------|
| `P1+`   | Increment Player 1's score |
| `P2+`   | Increment Player 2's score |
| `P1-`   | Decrement Player 1's score |
| `P2-`   | Decrement Player 2's score |
| `RESET` | Reset both scores to 0     |

---

##  Features

- Dual player score display  
- Bluetooth and button input support  
- Persistent score storage  
- Real-time score refresh  
- Buzzer feedback  

---

##  Setup Instructions

1. Connect hardware components.
2. Upload the `Tinkering.cpp` code to ESP32 using Arduino IDE.
3. Connect via a Bluetooth serial terminal to `ESP32_Scoreboard`.
4. Use commands or buttons to control the scoreboard.

---

##  Results

- Accurate real-time scoring.  
- Wireless and portable scoreboard.  
- User-friendly smartphone interface.  

---

##  Challenges

- Initial Bluetooth pairing issues.  
- 7-segment display interfacing with ESP32.  

---

##  Future Enhancements

- Battery backup for portability.  
- Support for more than two players.  
- Sound/milestone alerts.

