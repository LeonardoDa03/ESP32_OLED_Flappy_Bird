A basic ESP32-C3, OLED display, Flappy Bird Game with adjustable settings.

- Download and install Arduino IDE version-2.x.x (Arduino Download page: https://www.arduino.cc/en/software/) - Select based on your running OS.
- DOWNLOAD this code by clicking the Code->Download Zip button and extract the ZIP folder on your computer 
- Rename the folder by removing "-main"
- Double Click the "ESP32_OLED_Flappy_Bird.ino" file (.ino is the extension of Arduino main sketch file)
- Goto: File->Preferencies... (or click Cntrl + ,) and in the "Additional boards manager URLs" copy and paste the following URL: https://dl.espressif.com/dl/package_esp32_index.json
- Goto and Select: Tools->Board->esp32->ESP32C3 Dev Module
- Connect your ESP32C3 board to your via USB cable
- Under Tools->Port Select your board COM port (on Windows) or dev/tty (on MacOS/Linux)
- Configure your preferencies in the "GameSettings.h" file (choose your welcome message)
- Hit the Upload button (secon button on upper left) and wait for the compiler to be done
- Enjoy!
