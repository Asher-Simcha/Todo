#!/usr/bin/bash
# Title: 
# Author: 
# Additional Authors: 
# Additional Authors: 
# Filename: 
# Description: 
# Additional_Notes: 
# Version: 
# Date: 
# Last_Modified: 
# Source: 
# Additional_Sources: 
# License: 
# Additional_Licenses: 
# Credits: 
# Additional Credits: 
# Additional Credits: 
# Audio_Location: 
# Location_of_the_Video: 
# Embed_YouTube: 
# Website_For_Video: 
# Start_Time: 
# Parent_File: 
# Sibling_File: 
# Sibling_File: 
# Child_File: 
# Child_File: 
# Linkable: 1
# Display_Links: 1
# Display_Code: 1
# Visible: 1
# Article: 

DEBUG=0 # Turn Debugging off
# DEBUG=1 # Turn Debugging on

NAMEOFCOMPANY="ashersprograms"
NAMEOFCOMPANY_PROPER="Ashers Programs.com"
NAMEOFPROGRAM="weather-out.sh"
NAMEOFPROGRAM_PROPER="Weather Out.sh"
PARENTPROGRAM="todolist"
VERSION="01.01.01"

PROGRAM_ECHO="/bin/echo"
WEATHER="$HOME/.conky/accu_weather/weather.sh"
CFG_LOCATION="$HOME/.config/$NAMEOFCOMPANY/"
CACHE_LOCATION="$HOME/.cache/$PARENTPROGRAM/"
FILE_WEATHER=$CACHE_LOCATION"Weather.txt"
CFG_WEATHER_COUNT=$CFG_LOCATION"TodoListWeatherCount.ini"
ONE=1
OUTPUT_ERROR="This is a Child file and the appropriate files and folders do not exists for this program to work properly";
checkfilesystem(){
    if [ $DEBUG -eq "1" ]; then $PROGRAM_ECHO "function checkfilesystem"; fi
    if [ ! -e $CACHE_LOCATION ]; then
        if [ $DEBUG -eq "1" ]; then echo $OUTPUT_ERROR; fi
        exit 1;
    fi
    if [ ! -e $CFG_LOCATION ]; then
        if [ $DEBUG -eq "1" ]; then echo $OUTPUT_ERROR; fi
        exit 2;
    fi
    if [ ! -e $FILE_WEATHER ]; then
        if [ $DEBUG -eq "1" ]; then echo $OUTPUT_ERROR; fi
        exit 3;
    fi
    if [ ! -e $CFG_WEATHER_COUNT ]; then
        if [ $DEBUG -eq "1" ]; then echo $OUTPUT_ERROR; fi
        exit 4;
    fi
    
}
getweather(){
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "function getweather"; fi
    local THISWEATHER=$($WEATHER)
    $PROGRAM_ECHO $THISWEATHER > "$FILE_WEATHER"
}
resetWeatherCount(){
    $($PROGRAM_ECHO "$ONE" > ${CFG_WEATHER_COUNT})
}
main(){
    checkfilesystem # make sure that the directories exists and if not create them
    getweather
    resetWeatherCount
}
main


# EOF
