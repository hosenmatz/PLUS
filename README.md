
# Otto DIY+ (PLUS)
"Otto DIY with steroids" 

This Repository have all open source files for Otto DIY+ an interactive robot that anyone can make!,
Otto DIY + can make everything that Otto DIY does + Bluetooth + APP + switch + sensors + strength +... anything you might expand feel FREE to add and contribute. for LED Matrix we have a separate repository here https://github.com/OttoDIY/Matrix_hands
Is completely open source, Arduino compatible, 3D printable, once you have all components and tools you will be able to build your own Otto
<img src="https://github.com/OttoDIY/PLUS/blob/master/APP/OttoDIY%2B.jpg" width="900" align="center">

This is a more advanced version requires some expertise and patience, if you want to start slow as a beginner  please go to [Otto DIY repository](https://github.com/OttoDIY/DIY)

Start by [downloading all files here](https://github.com/OttoDIY/PLUS/archive/master.zip)

## For the hardware
Gather all the off the shelf parts in the BOM file that you'll need for this assembly, then 3d print the  .stl files and then follow the instruction manual to build your own robot.

## For the quick start programming and learners
1. download mBlock.cc V3; is an opensource software released by MakeBlock for easy programming Robot by Drop and Drag blocks. Based on Scratch 2.0 (MIT), beside sharing the great Feature of Scratch, mBlock also integrated an Arduino Code generator for upload program into Arduino based Hardware.
2. install Otto Extension in mBlock software use Arduino mode
3. drag and drop functions, dance, sounds and conditionals from robot Otto blocks
4. connect and check COM port
5. upload your own code! 

## For the advanced programming
1. Download & Install Arduino IDE: https://www.arduino.cc/en/Main/Software also this driver if you have a clone board: http://www.wch.cn/download/CH341SER_EXE.html for PC, or http://www.wch.cn/download/CH341SER_MAC_ZIP.html for MAC
2. Copy all libraries to C:\Users\user\Documents\Arduino\libraries (or wherever your library folder is installed):
3. Open  any .ino code, make sure in tools you have "Board: Arduino Nano" "Processor ATmega328" and your Otto is connected to the corresponding port
4. Upload the APP code to Otto DIY+
5. Download and install the  APP
6. Share in our Otto builder Facebook group https://www.facebook.com/ottodiy/groups/

### Otto DIY+ is  design using Autodesk Fusion 360
So is completely parametric and precise to adjust tolerances
[You can modify it for customization](https://gallery.autodesk.com/fusion360/projects/otto-diyplus) or further improvements

### Hall of fame Otto builders list
Our broad community is awesome! we have been developing and improving OttoDIY project together ;)

| contribution  | date | builder name | country |
| --- | --- | --- | --- |
| oscillator algorithm library| Jan 2015 | Obijuan | Spain  |
| inventor of Zowi 3D printable | Dec 2015  | Javier Isabel |Spain |
| Bobwi (combination of Bob and Zowi  | Jan 2016  |G4alileo |Spain  |
| BT, battery, nose LED RGB, touch and tilt | April 2016 |Davor Levstek  |Croatia |
| Robonino with voice control |May 2016|Santiago|Spain |
| Calibration tool  | June 2016 |Rafael López  |Spain |
| FreeCAD model|August 2016|Juan Carlos López Sánchez |Spain |
| ESPOtto voice | Sept 2016 |Gustavo Reynaga |Mexico|
| Otto arms |Sept 2016|Jason Leung| Hong Kong |
| Google Play android APP  | Oct 2016 |Juan Felix Mateos |Spain |
| Switch alternative |Dec 2016|Robert Holt |United States |
| Custom PCB, OttoDIY+ repository | Jan 2017 |Jason Snow |England |
| Single ladies dance| Jan 2017  |brico3D |Spain |
| Nose and DIY APP |Feb 2017|Andrés Fernández Muñoz|Spain |
| feedback  | March 2017   |Frank Lopez |United States |
| feedback | March 2017  |Octavio P Nogueira |Brazil  |
| Custom PCB | 	March 2017 |Marco|Italy |
| Laser cut Otto |March 2017|Florian Festi|Germany |
| XXL Head |March 2017|Markus Otte |Germany |
| XGoBroRobo IR control |March 2017|Jonathan Hess |Germany |
| Easy BT Easy HC-06 | May 2017  |Pablo E. García Palacios  |Spain |
| Custom PCB, battery booster, noise detection | April 2017|Pedro 51|France |
| graphical coding  | June 2017  |Liao Ping Lun  |China |
| Otto bender mod| June 2017  |bricogeek |Spain |
| remote control | July 2017  |Jayesh Chauhan |India  |
| Customizable Otto 3D print |July 2017|Brandon Bowles |United States |
| quadruped Otto | August 2017  |quadruped |China |
| control from laptop | August 2017  |SungHyun Ryu |South Korea |
| touch code | September 2017  |Alberto |Spain |
| Otto wheels | September 2017 |Jason Snow |England |
| Tito +| September 2017 |Jason Snow |England |
| 6 modes code | October 2017  |Davor Levstek  |Croatia |
| Otto accessories| October 2017  |Lucid Wolf|Australia |
| Otto accessories Halloween  | October 2017  |Trish Davies  |Australia |
| mbloc scratch graphical coding| November 2017  |Hien Phan |Vietnam |
| Otto Santa Claus| December 2017  |Dreamfactory  |Argentina |
| Otto Nutcraker| December 2017  |Dreamfactory  |Argentina |
| SelfProgramming| December 2017  |YoJuLab  |South Korea |
| open APP inventor | January 2018 |Jason Snow |England |
| LED eyes | January 2018 |Mr. Chan|China |
| Otto learning| January 2018  |Hien Phan |Vietnam |
| new APP BETA | February 2018 |Jason Snow |England |
| Otto meets MARS | March 2018 |Jason Snow |England |
| arduinoblocks | April 2018 |Juan |Spain |
| libraries update | May 2018 |Jason Snow |England |

Special thanks to all these #Ottobuilder that made and are making this project evolve and accessible to everyoone in the world. If we we are missing one please let us know!

### Pending  to develop idea list
Feel free to grab and mix ideas from this table for your Otto and if you are nice person please share with all the community

| Function-Feature  | sensor(input) | movement (output) | 
| --- | --- | --- | 
| drumer  |microphone|hands+stick|
| Car-balancing  |accelerometer|4x4 wheels|
| Sumo |IR|wheels+bumper|
| omniwheel |magnet switch|wheels+rollers|
| Train |IR|Steam generator|
| Humanoid |variable resistor modes|+servos control|
| Spider 6-8 legs |gestures|+vibrators|
| hover or drone |accelerometer|+DC motor control|
| look around xiaofang |timer|new head|
| writer |encoders|DC+ pen holder|
| following line |IR+encoders|step motors|
| Bubbles |light|DC fan|
| crane |Buttons|+servos control|
| Gripper |Tilt Sensor|+servo|
| reaction to music  |keepon|vibrators|
| Follow music | MP3 SD card|disco lights|
| Voice commands |telegram|multiple boards|
| clap rhythm |arms codes|vibrators|

## License CC-BY-SA
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Otto DIY</span> by <a xmlns:cc="http://creativecommons.org/ns#"  property="cc:attributionName"> [www.ottodiy.com](http://www.ottodiy.com) </a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
