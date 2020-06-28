# ATCwatch  -WatcH
Custom Arduino C++ firmware for the P8 and PineTime plus many more DaFit Smartwatches

About 150-200uA standby current consumtion.Currently 92 Hours Runtime with heavy notification and usage!.
Basic menu system and notification working.

If you want to use it on PineTime comment the #define P8WATCH to enable the PineTime Pinout. 
For other watches please try to check the pinout of them and change the pinout as needed.

#### You can support my work via paypal: https://paypal.me/hoverboard1 this keeps projects like this comming.

Use this portable Arduino version: https://atcnetz.de/downloads/D6Arduino.rar
here is a manual on how to use it: https://youtu.be/3gjmEdEDJ5A
Unzip, open Arduino.exe open the ATCwatch.ino file and compile. Done
Simply select the DaFit as the board and click on compile, you will get an Update file you can flash in the Arduino folder.

Please make shure you have always an option to go back to Bootlaoder somehow, i can only suggest to have one watch opened and connected an SWD St-Link V2 to it to develope on that.


#### This can be flashed without opening the Watch with this Repo https://github.com/atc1441/DaFlasherFiles and the DaFlasher app from the PlayStore(Android):
https://play.google.com/store/apps/details?id=com.atcnetz.paatc.patc&hl=en_US

https://www.youtube.com/watch?v=gUVEz-pxhgg

This firmware is meant to be used with the D6Notification App from the PlayStore(Android):
https://play.google.com/store/apps/details?id=com.atcnetz.de.notification&hl=gsw

## License:
You can use and edit the code as long as you mention me (Aaron Christophel and https://ATCnetz.de) in the source and somewhere in the menu of the working firmware, even when using small peaces of the code. :)
If you want to use the code or parts of it commercial please write an email to: info@atcnetz.de

## Credits:
Many Thanks to Daniel Thompson(https://github.com/daniel-thompson/wasp-os) to giving the Hint with the BMA423 Library
This way interrupts are finally possible with it.
This code uses the BMA421 Library wich is made by Bosch and this is under copyright by Bosch Sensortech GmbH
https://github.com/BoschSensortec/BMA423-Sensor-API
