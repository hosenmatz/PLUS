HOW TO USE THE APP

1. Copy Otto libraries into the Arduino IDE folder, replace all the old original libraries.
2. Upload the 'OTTO_NEW_OTTO_APP_9600.ino' sketch to Otto
3. Install the latest version APP .apk in your android phone
4. Enable Bluetooth
5. Search to find Otto and pair the Bluetooth address /name
6. You should be able now to use the APP to control Otto
7. You can also change the mode with the app at any time and play with the new features

# OttoDIY---APP 
Created for bluetooth conectivity. 

Please make sure that you use all the Libraries within these folders, even if you already have similar libraries.

If you have a default Bluetooth module use the OttoDIYAPP_122_baudrate9600.ino sketch.

Please check this repository for Android app updates.

Otto will be in his standard waiting MODE, once the APP is connected to Otto - a command to put him into MODE 4, app mode, will be sent to Otto, the features and control from the app will then be possible.

In the event that Otto does not seem to function with the app, select MODE 4 from the app, this will resend the command to put him into app mode again. Otto will display the MODE number on his Matrix mouth each time it is changed.

If all else fails and Otto still does not resond to the app, 

Please double check the Baud rate of the sketch matches the Baud rate of the Bluetooth module, the default for most standard modules is 9600 but this might not be correct for every module.
