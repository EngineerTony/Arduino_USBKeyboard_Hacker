# Arduino_USBKeyboard_Hacker
Uses the Arduino Uno microcontroller to emulate a USB keyboard and insert random text into the computer at random intervals

\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#
## Usage:
Once the Arduino is programed and the 16U2 is flashed, plug the arduino into a Windows computer and let the USB keyboard drivers install as normal.  Then wait between 1 and 10 minutes for a random injection of text.

\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#
## Process summary:
  1. Program the keyboard_hacker.ino onto your Arduino UNO R3
  2. Use Flip software (from [ATMEL](http://www.atmel.com/tools/FLIP.aspx)) and flash the 16U2 USB to Serial emulator with new firmware to make it appear as a USB keyboard to the computer
  3. Plug into the computer to prank/joke and wait...
  4. *NOTE:* you will need to use Flip and flash the 16U2 back to usbserial-uno to go back to a "normal" UNO afterwards

\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#
## Full process:
  **Arduino**
  1. Save the keyboard_hacker.ino onto your computer
  2. Plug Arduino Uno into computer and start Arduino programming environment
    * You can find the Arduino Programming software at [arduino.cc](https://www.arduino.cc/)
  3. Set the correct board type (UNO) and PORT in the Arduino programing software
  4. Open the keyboard_hacker.ino file and flash onto the Arduino
  5. Then open FLIP
  
**FLIP**
  1. Download from [http://www.atmel.com/tools/FLIP.aspx](http://www.atmel.com/tools/FLIP.aspx) if you don't have it yet
  2. Use File->Load HEX file and open Arduino-keyboard-0.3.hex
  3. Use Device->Select to select the ATmega16u2 chip
    * Please *NOTE* that you must check the chip code on the small back microchip near the USB plug and the oval silver crystal oscillator to confirm this number
  4. Now you must force the Ardunio into dfu-boot mode to flash the 16U2 chip
    * With the Arduino still connected/powered by USB connect the Reset-peg to ground for under one second (like this http://www.arduino.cc/en/Hacking/DFUProgramming8U2) 
    * The LED's should turn off then back on again
  5. Use Settings->Communication to select USB
  6. In the pop up box click OPEN the connection
  7. The lights in the "Operations Flow" area of the main window will light up
  8. Now click Run (with the Erase, Program and Verify boxes checked/ticked)
  9. If all goes well now you can unplug your arduino from the USB and re-plug it into the computer you want to trick

*If you get an ERROR at Step 5 your ATMEL ATmegaxxu2 chip did not reset into DFU mode.  Try Step 4 again and confirm your Arduino LEDs turned off.  Sometimes you will need to ground the Reset Peg on a different GND plug.*

\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#
Turn your Arduino Keyboard back to an Arduino UNO
Repeat the process under the FLIP title above, but this time use the Arduino-usbserial.hex file.

Thanks to [hunt.net.nz](http://hunt.net.nz/users/darran/) for the Keyboard.hex files and inspiration
Thank you to all the Arduino creators, users and question answer(er)s that made this possible.

Enjoy =D
