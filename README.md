**Build a Electron Distance Sensor**

In this experiment you are going to build a sensor able to measure distances from 10cm up to 200cm. The data will be transmitted via cell to a cloud service.

**Required Parts**

To build this sensor you need the following hardware:

- 1x breadboard
- 1x Particle Electron
- 1x HC-SR04 sensor
- 1x 470 Ohm resistor
- 1x 1k Ohm resistor
- 4x male to female wires

**Prepare your laptop**

[**https://docs.particle.io/guide/tools-and-features/cli/photon/**](https://docs.particle.io/guide/tools-and-features/cli/photon/)

**Wire up the circuit on breadboard**

Place components as shown in the schema.

The HC-SR04 sensor is a 5V device while the Electron operates at 3.3V. Therefore, we provide power to the sensor from the Vin pin (= 5V from USB).

The 2 resistors function as a voltage divider to convert 5V coming from the sensor to a safe 3.3V level.

R1: 470 Ohm (yellow purple black black [brown])
R2: 1k Ohm (brown black black brown [brown])


![alt text](https://github.com/Code-for-Miami/iot-flood-tracker/blob/master/Wiring.png)


**Connect Particle to the cloud**

**Identify device**

Connect the device to your computer using USB and put the device in [listening mode](blinking dark blue) by holding down the S MODE button until the main status LED blinks dark blue, about 3 seconds

First you want to know the Device ID of the Photon you just connected.
```
$ particle identify

Your device id is 2300211353337353037
Your IMEI is 35316207243
Your ICCID is 8936500002860393
Your system firmware version is 0.7.0
```
If firmware Version not 0.7 or higher see Mario or Christina

Copy this device id in your TextPad, you will need it in a few moments.

Photon status LED, it should be BREADING CYAN when it&#39;s happily connected to the internet.

Add device to your account (See Mario, Cristina to be add to the Code for Miami account)

Write sketch for the Photon

Open the online build environment of Particle.io on build.particle.io.

At the left-hand side you can see the vertical menu which you will use during the process. Hover you mouse over each item to get familiar with the different options:



**FLASH** - **VERIFY**  - **SAVE** - **CODE** - **LIBRARIES**  - **DOCS**  - **DEVICES** - **SETTINGS**

**Let&#39;s get started!**

- First we want to select the Photon we connected to our account in the previous step. From the menu, press DEVICES
- Check if your device is listed and select it by clicking the yellow star in front of the device name.
- From the menu, press &quot;\&lt; \&gt;&quot; Code to open the code editor
- Press CREATE NEW APP and enter a Title (e.g. MyFloodMeasuring  )
- Again at the left-hand side press Libraries (first item below &quot;\&lt; \&gt;&quot;)
- In the Community Libraries search box type: HC\_SR04
- Press on the search result HC\_SR04
- Press INCLUDE IN APP, select the app you just created (e.g. MyFloodMeasuring) and press ADD TO THIS APP



Paste the code fromgit url, https://github.com/Code-for-Miami/iot-flood-tracker/blob/master/GiveMeData.ino replacing it&#39;s current content

- From the menu, press VERIFY.
This should result in the message Code verified! Great work.
- Now you are ready to press FLASH
If everything goes well, you will get a:
Flash successful! Please wait a moment while your device is updated...
- The device should return to breading cyan status color

#### **Monitor the published sensor values**

Debug readings from local serial port (Photon need to be connected to USB)
```
$ particle serial monitor
Opening serial monitor for com port: "/dev/tty.usbmodem1411"
Serial monitor opened successfully:
Report: 13.55 cm
Report: 55.19 cm
Report: 55.17 cm
Report: 59.33 cm
Report: -1.00 cm
Report: 55.88 cm
Report: 57.36 cm
Report: 30.78 cm
Report: 110.74 cm
Report: -1.00 cm
Report: 229.14 cm
Report: 231.03 cm
```


**Go Hack add features and build the hardware**
