# ECE-425-Final-Project




ECE 425 

Final Project: 
Digital Clock with an Alarm

Mario Hernandez
Instructor: Aaron Nanas
Spring 2025
5/8/2025















Introduction
This final project focuses on designing and implementing a digital clock with alarm and snooze functionality using the TM4C123G LaunchPad and EduBase Board. The system displays time on an LCD screen, allows manual time and alarm setting using push buttons, and utilizes LEDs for the alarm signal. The Alarm was designed to go into automatic snooze mode until the alarm is turned off, where there is a countdown displayed on the LCD displaying the time until the alarm goes off again. A light sensor is also incorporated to dismiss the alarm(turning off the Alarm), introducing practical interaction between user input and environmental feedback.

Background and Methodology:
This project incorporates fundamental embedded systems principles such as timekeeping, GPIO interfacing, interrupt handling, periodic timers, analog signal processing, and state-based logic control. I was able to incorporate these fundamental topics into a fully functional Alarm system that properly displays correct timing at an accurate pace(correctly updating every second). While at the same time allowing for the Alarm to be properly triggered when timing matches. 

Key Concepts Applied:
- GPIO input/output for button and LED control and LCD communication
- SysTick for delay and timing operations, provides millisecond-level delay functions
- Timer0A (GPTM) for 1 Hz system clock ticks
- ADC for analog light sensor input, reads analog input from a light sensor to dismiss the alarm.
- Modular programming structure using C- all this was done in Keil.
- Interrupt Handling is used to detect button presses via Port D interrupts




![image](https://github.com/user-attachments/assets/04104e48-0a1d-4c4d-b11d-812397d98839)


![image](https://github.com/user-attachments/assets/4e727ca6-255d-44cc-9178-d046cbd396a2)

![image](https://github.com/user-attachments/assets/3e395ae5-83e9-4212-80cc-f68162bea6e1)



Analysis and Results
System Behavior:
- Time can be set manually using buttons SW2 (hours), SW3 (minutes), and SW4 (start clock).


- Alarm time is configured in real-time using SW2 and SW3 again after the clock is running.


- When the alarm time matches the current time, LEDs are activated.


- A snooze cycle begins, alternating 5-second LED flashes and a visible countdown.


- The alarm can be dismissed by covering the light sensor (PE1).






Challenges:
- Button mappings required precise alignment between hardware layout and interrupt handlers.
- LCD formatting needed careful cursor control to avoid display artifacts.
- Synchronizing snooze logic and countdown display with the main timekeeping loop required timed flag management.
- Time delay was used to minimize button debouncing
- Sw5 was not working on the edubase board, which limited my options. 


Results:
- The system successfully runs with no compile-time errors.
- LCD updates every second and accurately reflects time and alarm status.
- Light sensor input works reliably to dismiss the alarm.
- Snooze functionality repeats in 5-second on/off cycles until dismissed.

ECE 425 final project presentation
https://youtu.be/PD9biLL2htg?si=-CHa_UX2TxUzQFfM

Conclusion
This project provided hands-on experience with embedded systems design, including modular C programming, peripheral interfacing, interrupt-driven I/O, and time-critical application logic. I deepened my understanding of the TM4C123G’s capabilities, especially the GPTM, SysTick, ADC, and GPIO modules. The ability to extend the system to include real-world interaction through a light sensor helped solidify how embedded systems bridge software and hardware in practical scenarios. Future improvements could include buzzer, PWM control, alarm sound patterns, storing multiple alarm presets, and using more reliable like in the lab to minimize debouncing. 
