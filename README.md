# jiiot-client
Send data from microcontroller (arduino or esp8266) to JiIOT server using GET method.

In this repository there are two folders containing the code for arduino and esp8266. In each folder there are an examples how to using this code for a simple implementation.

Esp8266 chip using
- firmware : LUA 
- flashing tools : nodemcu flasher https://github.com/nodemcu/nodemcu-flasher (with default setting)
- IDE : esplorer https://github.com/4refr0nt/ESPlorer or https://esp8266.ru/esplorer/

;----------------------------------------------

jiiot-client folder :
- Arduino
  - main.ino
  - example.ino
  
- Esp8266
  - init.lua
  - example.lua
  - example-lua.ino

Tested

a. Arduino : 

  1. UNO (DIP, SMD, clone)
  2. Mega2560
  3. NANO
  
b. Esp8266 :

  1. esp01 (black and blue board)
  2. esp12e (nodeMCU board)
  3. esp12
