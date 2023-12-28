#!/usr/bin/sh
# Title: 
# Author: 
# Additional Authors: 
# Additional Authors: 
# Filename: weather-out.sh
# Description: 
# Additional_Notes: 
# Version: 01.01.01
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
 
# compile options: 
DEBUG=0 # Turn Debugging off
# DEBUG=1 # Turn Debugging on

NAMEOFCOMPANY="ashersprograms"
NAMEOFCOMPANY_PROPER="Ashers Programs.com"
NAMEOFPROGRAM="weather-out.sh"
NAMEOFPROGRAM_PROPER="Weather Out.sh"
PARENTPROGRAM="todolist"
VERSION="01.01.01"

PROGRAM_ADD="/usr/bin/ashers_add"
PROGRAM_CAT="/bin/cat"
PROGRAM_ECHO="/bin/echo"
PROGRAM_MKDIR="/bin/mkdir"
WEATHER="$HOME/.conky/accu_weather/weather.sh"
CFG_LOCATION="$HOME/.config/$NAMEOFCOMPANY/"
CACHE_LOCATION="$HOME/.cache/$PARENTPROGRAM/"
CFG_WEATHER_COUNT=$CFG_LOCATION"TodoListWeatherCount.ini"
FILE_WEATHER=$CACHE_LOCATION"Weather.txt"

EXIT_ONE_OUTPUT="Could NOT create the directory: $CFG_LOCATION"
EXIT_TWO_OUTPUT="Could NOT create the directory: $CACHE_LOCATION"
ONE=1
SIXTY=60
checkfilesystem(){
    if [ $DEBUG -eq "1" ]; then $PROGRAM_ECHO "function checkfilesystem"; fi
    if [ ! -e $CFG_LOCATION ]; then
        $PROGRAM_MKDIR $CFG_LOCATION
        if [ ! -e $CFG_LOCATION ]; then
            if [ $DEBUG -eq "1" ]; then $PROGRAM_ECHO "$EXIT_ONE_OUTPUT"; fi
            exit 1;
        fi
    fi
    if [ ! -e $CACHE_LOCATION ]; then
        $PROGRAM_MKDIR $CACHE_LOCATION
        if [ ! -e $CACHE_LOCATION ]; then
            if [ $DEBUG -eq "1" ]; then echo "$EXIT_TWO_OUTPUT"; fi
            exit 2;
        fi
    fi
}
collectVariables(){
    if [ $DEBUG -eq "1" ]; then $PROGRAM_ECHO "function collectVariables"; fi
    if [ ! -e $CFG_WEATHER_COUNT ]; then
        $PROGRAM_ECHO "$SIXTY" > $CFG_WEATHER_COUNT
        WEATHERCOUNT=$SIXTY
    fi
}
chechvalidity_weather(){
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "function chechvalidity_weather"; fi
    local PASSWEATHER=0;
    WEATHERCOUNT=$(cat $CFG_WEATHER_COUNT)
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "The Weather count is: $WEATHERCOUNT. The file is $CFG_WEATHER_COUNT"; fi
    if [ $WEATHERCOUNT -eq "1" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "2" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "3" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "4" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "5" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "6" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "7" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "8" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "9" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "10" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "11" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "12" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "13" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "14" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "15" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "16" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "17" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "18" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "19" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "20" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "21" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "22" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "23" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "24" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "25" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "26" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "27" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "28" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "29" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "30" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "31" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "32" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "33" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "34" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "35" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "36" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "37" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "38" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "39" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "40" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "41" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "42" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "43" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "44" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "45" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "46" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "47" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "48" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "49" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "50" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "51" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "52" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "53" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "54" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "55" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "56" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "57" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "58" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "59" ]; then PASSWEATHER=1; fi
    if [ $WEATHERCOUNT -eq "60" ]; then PASSWEATHER=1; fi
    if [ $PASSWEATHER -eq "0" ]; then
        $($PROGRAM_ECHO "$SIXTY" > ${CFG_WEATHER_COUNT})
        WEATHERCOUNT=$SIXTY
    fi
}
getweather(){
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "function getweather"; fi
    local THISWEATHER=$($WEATHER)
    $PROGRAM_ECHO $THISWEATHER > "$FILE_WEATHER"
}
countWeather(){
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "function countWeather"; fi
    chechvalidity_weather
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "The Weather count is: $WEATHERCOUNT"; fi
    if [ $WEATHERCOUNT -ge "$SIXTY" ]; then
        getweather
        $($PROGRAM_ECHO "$ONE" > $CFG_WEATHER_COUNT)
    fi
    WEATHERCOUNT=$($PROGRAM_CAT $CFG_WEATHER_COUNT)
    WEATHERCOUNT=$($PROGRAM_ADD $WEATHERCOUNT $ONE)
    $($PROGRAM_ECHO "$WEATHERCOUNT" > $CFG_WEATHER_COUNT )
}
showweathernow(){
    local THISWEATHER;
    if [ $DEBUG -eq "$ONE" ]; then $PROGRAM_ECHO "function showweathernow"; fi
    if [ -e "$FILE_WEATHER" ]; then
        cat "$FILE_WEATHER"
    else
        getweather
        cat $FILE_WEATHER
    fi
}
main(){
    checkfilesystem # make sure that the directories exists and if not create them
    collectVariables
    countWeather
    showweathernow
}
main
# EOF
