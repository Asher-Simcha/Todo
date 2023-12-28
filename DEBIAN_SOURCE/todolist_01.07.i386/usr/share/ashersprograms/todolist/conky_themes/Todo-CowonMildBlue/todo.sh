#!/bin/sh
# Title: Todo.sh for Todo-New
# Author:  Asher Simcha
# Additional Authors: 
# Additional Authors: 
# Filename: todo.sh
# Description:  displays the context of the TODO, NOTES, AND EVENTS. IN WHOLE WITH CODE.
# Additional_Notes: 
# Version: 1.04
# Date: 11-24-2023
# Last_Modified: 11-24-2023
# Last_Modified: 12-10-2023
# Last_Modified: 12-11-2023
# Last_Modified: 12-12-2023
# Last_Modified: 12-15-2023
# Last_Modified: 12-16-2023
# Last_Modified: 12-17-2023
# Last_Modified: 12-21-2023
# Source: 
# Additional_Sources: 
# License: Copyright 2023-2024 ashersprograms.com
# Additional_Licenses: 
# Credits: 
# Additional Credits:  MX-Linux Inspired by conky-harddisks.sh
# Additional Credits: 
# Audio_Location: 
# Location_of_the_Video: 
# Embed_YouTube: 
# Website_For_Video: 
# Start_Time: 
# Parent_File: todolist.ini
# Sibling_File: 
# Sibling_File: 
# Child_File: 
# Child_File: 
# Linkable: 1
# Display_Links: 1
# Display_Code: 1
# Visible: 1
DEBUG=0 # Turn Debugging off
#DEBUG=1 # Turn Debugging on
SHOWFORTUNE=0
SHOWFORTUNEBEFORE=0
SHOWWEATHER=0
SHOWWEATHERBEFORE=0
PASS=0
TODOLISTCOUNT=0
HEADERSHOW=0
SHOWENDING=0
FORTUNE="/usr/games/fortune"
FORTUNEARG="debian-hints"
WEATHER="$HOME/.conky/accu_weather/weather.sh"
CFG_LOCATION="$HOME/.config/ashersprograms/"
CACHE_LOCATION="$HOME/.cache/todolist/"
#PROGRAMTOEXECUTE="$FORTUNE $FORTUNEARG"
PROGRAMTOEXECUTE="$FORTUNE"
PROGRAM_ADD="/usr/bin/ashers_add"
PROGRAM_CAT="/bin/cat"
PROGRAM_COMPARE="/usr/bin/ashers_stringcompare"
PROGRAM_CUT="/bin/cut"
PROGRAM_FOLD="/bin/fold"
PROGRAM_ECHO="/bin/echo"
PROGRAM_ISSET="/usr/bin/ashers_isset"
PROGRAM_INI="/usr/bin/ashers_ini"
PROGRAM_MD="/bin/mkdir"
PROGRAM_TR="/bin/tr"
FILENAMEFORTUNE=$CACHE_LOCATION"FortuneSaying.txt"
FILE_WEATHER=$CACHE_LOCATION"Weather.txt"
EVENT1=$CACHE_LOCATION"Event1.txt"
EVENT2=$CACHE_LOCATION"Event2.txt"
cfg="cfg_pass"
dfs="Fortune Cookie says: Today this the Greatest Day of Your Life"
ev1="Event1"
ev2="Event2"
nt1="Note1"
nt2="Note2"
ts1="Task1"
ts2="Task2"
ts3="Task3"
ts4="Task4"
ts5="Task5"
o="Order"
one=1
f="-f"
r="-r"
s="-s"
sfb="SFBefore"
shf="ShowFortune"
sw="ShowWeather"
swb="SWBefore"
t="true"
tw="Weather"
te=28
ten=10
twen=20
v="-v"
w="-w"
zero=0
fiv=60
NOTE1=$CACHE_LOCATION"Note1.txt"
NOTE2=$CACHE_LOCATION"Note2.txt"
TASK1=$CACHE_LOCATION"Task1.txt"
TASK2=$CACHE_LOCATION"Task2.txt"
TASK3=$CACHE_LOCATION"Task3.txt"
TASK4=$CACHE_LOCATION"Task4.txt"
TASK5=$CACHE_LOCATION"Task5.txt"
TODO_MAIN_CFG_FILE="$CFG_LOCATION/todolist.ini"
CFG_COUNT=$CFG_LOCATION"TodoListCount.ini" # INTERNAL to determine if fortune is to be refreshed or not
CFG_WEATHER_COUNT=$CFG_LOCATION"TodoListWeatherCount.ini"
checkfilesystem(){
    if [ $DEBUG -eq "1" ]; then echo "function checkfilesystem"; fi
    if [ -e $TODO_MAIN_CFG_FILE ]; then
        if [ ! -e $CFG_LOCATION ]; then # if the .config directoy does not exists create it now
            $PROGRAM_MD $CFG_LOCATION
        fi
        if [ ! -e $CACHE_LOCATION ]; then # if the .cache directory does not exists create it now
            $PROGRAM_MD $CACHE_LOCATION
        fi
        if [ ! -e $CFG_COUNT ]; then # the number in the program is $TODOLISTCOUNT
            $PROGRAM_ECHO "$ten" > $CFG_COUNT
        fi
        if [ ! -e $CFG_WEATHER_COUNT ]; then
            $PROGRAM_ECHO "$ten" > $CFG_WEATHER_COUNT
        fi
    else
        exit 1;
    fi
}
collectVariables(){
    if [ $DEBUG -eq "1" ]; then echo "function collectVariables"; fi
    SHOWFORTUNE=$($PROGRAM_INI $f $TODO_MAIN_CFG_FILE $r $shf )
    if [ $DEBUG -eq "1" ]; then echo "SHOWFORTUNE: $SHOWFORTUNE"; fi
    SHOWFORTUNE=$($PROGRAM_COMPARE $SHOWFORTUNE $t) # 1 is display 0 is DONT display
    if [ $DEBUG -eq "1" ]; then echo "SHOWFORTUNE: $SHOWFORTUNE"; fi
    if [ $SHOWFORTUNE -eq 1 ]; then
        if [ -e $FILENAMEFORTUNE ]; then 
            #PASS=1; 
            FORTUNEVARIABLE=$($PROGRAM_CAT $FILENAMEFORTUNE )
        else
            createfortune
            if [ -e $FILENAMEFORTUNE ]; then 
                FORTUNEVARIABLE=$($PROGRAM_CAT $FILENAMEFORTUNE )
            else
                FORTUNEVARIABLE=$dfs
                $($PROGRAM_ECHO $FORTUNEVARIABLE > $FILENAMEFORTUNE)
            fi
        fi
        SHOWFORTUNEBEFORE=$($PROGRAM_INI $f $TODO_MAIN_CFG_FILE $r $sfb )
        SHOWFORTUNEBEFORE=$($PROGRAM_COMPARE $SHOWFORTUNEBEFORE $t) # 1 is display 0 is DONT display
    fi
    SHOWWEATHER=$($PROGRAM_INI $f $TODO_MAIN_CFG_FILE $r $sw)
    if [ $DEBUG -eq "1" ]; then echo "SHOWWEATHER: $SHOWWEATHER"; fi
    SHOWWEATHER=$($PROGRAM_COMPARE $SHOWWEATHER $t) # 1 is display 0 is DONT display
    if [ $DEBUG -eq "1" ]; then echo "SHOWWEATHER: $SHOWWEATHER"; fi
    if [ $SHOWWEATHER -eq "1" ]; then
        SHOWWEATHERBEFORE=$($PROGRAM_INI $f $TODO_MAIN_CFG_FILE $r $swb)
        SHOWWEATHERBEFORE=$($PROGRAM_COMPARE $SHOWWEATHERBEFORE $t)
    fi
}
chechvalidity_weather(){
    if [ $DEBUG -eq "1" ]; then echo "function chechvalidity_weather"; fi
    local PASSWEATHER=0;
    WEATHERCOUNT=$(cat $CFG_WEATHER_COUNT)
    if [ $DEBUG -eq "1" ]; then echo "the Weather count is: $WEATHERCOUNT"; fi
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
        $(echo "60" > ${CFG_WEATHER_COUNT})
        WEATHERCURRENTCOUNT=$(cat $CFG_WEATHER_COUNT)
    fi
}
checkvalidity(){
    if [ $DEBUG -eq "1" ]; then echo "function checkvalidity"; fi
    local PASS=0
    if [ $TODOLISTCOUNT -eq "1" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "2" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "3" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "4" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "5" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "6" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "7" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "8" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "9" ]; then PASS=1; fi
    if [ $TODOLISTCOUNT -eq "10" ]; then PASS=1; fi
    if [ $PASS -eq "$zero" ]; then $PROGRAM_ECHO "$one" > $CFG_COUNT; fi
}
getweather(){
    if [ $DEBUG -eq "1" ]; then echo "function getweather"; fi
    local THISWEATHER=$($WEATHER)
    echo $THISWEATHER > "$FILE_WEATHER"
}
countWeather(){
    if [ $DEBUG -eq "1" ]; then echo "function countWeather"; fi
    if [ $SHOWWEATHER -eq "$one" ]; then
        WEATHERCOUNT=$(cat $CFG_WEATHER_COUNT)
        chechvalidity_weather
        if [ $DEBUG -eq "1" ]; then echo "The Weather count is: $WEATHERCOUNT"; fi
        if [ $WEATHERCOUNT -ge "$fiv" ]; then
            getweather
            $(echo "1" > $CFG_WEATHER_COUNT)
        fi
        WEATHERCOUNT=$(cat $CFG_WEATHER_COUNT)
        WEATHERCOUNT=$($PROGRAM_ADD $WEATHERCOUNT $one)
        $($PROGRAM_ECHO "$WEATHERCOUNT" > $CFG_WEATHER_COUNT )
    fi
}
countFortune(){
    if [ $DEBUG -eq "1" ]; then echo "function countFortune"; fi
    if [ $SHOWFORTUNE -eq "$one" ]; then
        if [ -e $CFG_COUNT ]; then
            TODOLISTCOUNT=$(cat $CFG_COUNT )
            if [ "10" -eq $TODOLISTCOUNT ]; then # a loop do this every 10 times
                createfortune
                $PROGRAM_ECHO "$one" > $CFG_COUNT
            else
                TODOLISTCOUNT=$($PROGRAM_ADD $TODOLISTCOUNT $one)
                $PROGRAM_ECHO "$TODOLISTCOUNT" > $CFG_COUNT
            fi
            checkvalidity 
        else
            $PROGRAM_ECHO "$one" > $CFG_COUNT
            if [ ! -e $FILENAMEFORTUNE ]; then
                createfortune
            fi
        fi
    fi
}

createfortune(){
    if [ $DEBUG -eq "1" ]; then echo "function createfortune"; fi
    TEXT=$($PROGRAMTOEXECUTE)
    TEXT_FILTER1=$($PROGRAM_ECHO "$TEXT" | $PROGRAM_TR '\n' ' ')
    TEXT_FILTER2=$($PROGRAM_ECHO "$TEXT_FILTER1" | $PROGRAM_FOLD $w $te $s )
    $($PROGRAM_ECHO "$TEXT_FILTER2" > $FILENAMEFORTUNE )
}
showfortune1(){
    if [ $DEBUG -eq "1" ]; then echo "function showfortune1"; fi
    if [ $SHOWFORTUNE -eq "$one" ]; then
        if [ $SHOWFORTUNEBEFORE -eq "$one" ]; then
            showfortuneNow
        fi
    fi
}
showfortune2(){
    if [ $DEBUG -eq "1" ]; then echo "function showfortune2"; fi
    if [ $SHOWFORTUNE -eq "$one" ]; then
        if [ $SHOWFORTUNEBEFORE -eq "$zero" ]; then
            showfortuneNow
        fi
    fi
}
showweather1(){
    if [ $DEBUG -eq "1" ]; then echo "function showweather1"; fi
    if [ $SHOWWEATHER -eq "$one" ]; then
        if [ $SHOWWEATHERBEFORE  -eq "$one" ]; then
            showweathernow
        fi
    fi
}
showweather2(){
    if [ $DEBUG -eq "1" ]; then echo "function showweather2"; fi
     if [ $SHOWWEATHER -eq "$one" ]; then
        if [ $SHOWWEATHERBEFORE -eq "$zero" ]; then
            showweathernow
        fi
    fi
}
showfortuneNow()
{
    SHOWENDING=1
    echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}FORTUNE'
    echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$FILENAMEFORTUNE' | fold -w 40 -s}'
    echo '${color}'
}
showweathernow(){
    local THISWEATHER;
    SHOWENDING=1
    if [ $DEBUG -eq "1" ]; then echo "function showweathernow"; fi
    if [ -e "$FILE_WEATHER" ]; then
        THISWEATHER=$(cat "$FILE_WEATHER")
    else
        getweather
        THISWEATHER=$(cat "$FILE_WEATHER")
    fi
    echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}WEATHER'
    echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}'$THISWEATHER
    echo '${color}' 
}
events()
{
    if [  -e  $EVENT1 ]; then
        SHOWENDING=1
        echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Event 1'
        echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec  cat '$EVENT1' | fold -w 40 -s}'
        if [ -e $EVENT2 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Event 2'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$EVENT2' | fold -w 40 -s}'
        fi
    fi
}
notes()
{
    if [  -e  $NOTE1 ]; then
        SHOWENDING=1
        echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Note 1'
        echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$NOTE1' | fold -w 40 -s}'
        if [ -e $NOTE2 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Note 2'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$NOTE2' | fold -w 40 -s}'
        fi
    fi
}
tasks()
{
    if [  -e  $TASK1 ]; then
        SHOWENDING=1
        echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Task 1'
        echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$TASK1' | fold -w 40 -s}'
        if [ -e $TASK2 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Task 2'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$TASK2' | fold -w 40 -s}'
        fi
        if [ -e $TASK3 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Task 3'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$TASK3' | fold -w 40 -s}'
        fi
        if [ -e $TASK4 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Task 4'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$TASK4' | fold -w 40 -s}'
        fi
        if [ -e $TASK5 ]; then
            echo '${color5}${voffset 2}${font Roboto-Light:bold:pixelsize=12}Task 5'
            echo '${color6}${voffset 1}${font Roboto-Light:bold:pixelsize=12}${exec cat '$TASK5' | fold -w 40 -s}'
        fi
    fi
}
displayheader()
{
    echo '${color6}${voffset 2}${hr 4}';
}
header()
{
    HEADERSHOW=0;
    if [ -e ~/.cache/todo_list/Event1.txt ]; then 
        displayheader
        HEADERSHOW=1;
    fi
    if [ $HEADERSHOW -eq 0 ]; then
        if [ -e ~/.cache/todo_list/Note1.txt ]; then
            displayheader
            HEADERSHOW=1;
        fi
    fi
    if [ $HEADERSHOW -eq 0 ]; then
        if [ -e ~/.cache/todo_list/Note1.txt ]; then
            displayheader
        fi
    fi   
}
ending()
{
    if [ $SHOWENDING -eq "1" ]; then
        echo "";
    fi
}
main(){
    if [ $DEBUG -eq "1" ]; then echo "function main"; fi
    checkfilesystem # make sure that the directories exists and if not create them
    collectVariables
    countFortune
    countWeather
    showweather1
    showfortune1
    header
    local variable1=$($PROGRAM_INI $f $TODO_MAIN_CFG_FILE $r $o)
    local variable1results=$($PROGRAM_ISSET $variable1)
    if [ $variable1results -eq "0" ]; then variable1="1"; fi
    case $variable1 in
        2)
            events
            tasks
            notes
        ;;
        3)
            tasks
            events
            notes
        ;;
        4)
            tasks
            notes
            events
        ;;
        5)
            notes
            events
            tasks
        ;;
        6)
            notes
            tasks
            events
        ;;
        *)
            events
            notes
            tasks
        ;;
    esac
    showweather2
    showfortune2
    ending
}
main
