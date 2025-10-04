Here are the attribute you need to change so it fit your board:

-analogReadResolution(12); are set depend on what your board has, if it is 10bit adc just comment it out the Arduino IDE default is 10bit.

-analogReference(INTERNAL1V024); the function name and argument differ for each board. This is set for lgt8f328p board.

<img width="456" height="65" alt="Screenshot 2025-10-04 192208" src="https://github.com/user-attachments/assets/71897875-043e-4901-a398-154fb6b768f2" />

-float adcbit = 12; are for setting the bit your adc is using, if 10bit set as 10.

-float internal_ref_volt = 1.024; are for set to your internal reference at analogReference(INTERNAL1V024);

<img width="469" height="141" alt="Screenshot 2025-10-04 192346" src="https://github.com/user-attachments/assets/d999482a-bedd-4f7c-b0e1-2ff984bc55e9" />

-float divide = 2.0 / (100.0 + 2.0); voltage division for use with a voltage divider

<img width="1355" height="30" alt="Screenshot 2025-10-04 193243" src="https://github.com/user-attachments/assets/c2f95181-d082-413c-8931-91f4d09368c3" />

this is most likely all the change you need. For Arduino and lgt8f328p board this is all, for esp32 or stm32 it may be the same or different (i dont have them board).
