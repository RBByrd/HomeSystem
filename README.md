# House Page, and Home Automation System
This project started with the idea that our new home would have a House Page website. 
A locally hosted webpage that would give information, and functionality to home owners and guests while on the home network.
Some of the functions for guests will be:
 
 Layout of the home.
  
  Where certain amenities are, bathrooms, trashcans, cups. 
  A declaration of what they are welcome to (top shelf of the fridge, snack drawer in the pantry)
  
  More interactive uses too!
  
  A bar page that encourages guests to serve themselves during certain times. 
  A list of the current spirits, and cocktail recipes. With the ability to favorite, and submit new recipes for logged in users
  
  A lights page that will allow owners and privilaged guests the ability to change the color of LED lights and
  save preferred hues to their account
  
 Functions that owners would be able to take advantage of along with the above:
  
  Be able to check the status of the alarm system.
  See logs of when Zones have been breached.
  
  Access sercurity cameras
  
  Play music through built in speakers
  
  
# Hardware
Much of the project is in the starting phases and will grow as I add more devices to the network.
I will add schematics for the devices as they are finished.


# House Site Server
Since the intent for this system is local use only, a Raspberry Pi should be able to handle the load. 
The Raspberry Pi will also run python services to interact with the other hardware. 


# Home Alarm System
Many people have probably purchased a home that has an installed security system already.
One they don't want to purchase a service for or don't want to use for any other reason. 
Many times this leaves hardware that seems to be useless.
I removed the old alarm panel and found I was able tap into the switches that monitored the doors, and windows.
The siren is also functional.
Currently I am developing a program that will use an Ardiuno UNO to be able to use these switches and siren for a simple unmonitored alarm system.
The alarm system will also use serial communication to relay information to the web server where a python program can use that to create logs.


# Cameras
Future Project

# Lights
Future Project
