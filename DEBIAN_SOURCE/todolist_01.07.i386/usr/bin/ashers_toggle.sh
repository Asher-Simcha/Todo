#!/usr/bin/bash
# Title: Ashers Toggle Plus
# Author: Asher Simcha
# Additional Authors: Kerry for antiX
# Additional Authors: anticapitalista for antiX
# Additional Authors: secipolla for antiX
# Additional Authors: dolphin oracle for mx linux version 17
# Additional Authors: fehlix
# Additional Authors: 
# Filename: ashers_toggle
# Original_Filename: conkytoggle.sh
# Original_Filename: conkytoggleflux.sh
# Description: Toggles any program ON/OFF. With only one instance running
# Additional_Notes: 
# Version: 3.04
# Date: 11-13-2023
# Last_Modified: December 2022 
# Last_Modified: Sun December 10, 2017
# Last_Modified: December 2022
# Last_Modified: Wed 10-25-2023
# Last_Modified: Tues 10-31-2023
# Last_Modified: Wed 11-01-2023
# Last_Modified: 11-13-2023
# Last_Modified: 12-23-2023
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

# Original Filename:      conkytoggleflux.sh
# Original Purpose:       toggle conky on/off from fluxbox menu
# Authors:       Kerry and anticapitalista, secipolla for antiX
# Authors:       modified for mx linux version 17 by dolphin oracle
# Latest change: Sun December 10, 2017.
################################################################################
# Adjusted by fehlix, December 2022 
################################################################################
# Latest change: Wed 10-25-2023
# Authors:      modified for ashersprograms.com by Asher Simcha
# Latest change: Tues 10-31-2023
# Latest change: Wed 11-01-2023
# Latest change: Mon 11-13-2023
# Authors:      modified for ashersprograms as a toggle for any application

# NOTES by Ashersprograms: The original program was designed to toggle just one program and now the program will toggle any program that is your executable path.

#   Exit Codes
#   0 = Program was turned on
#   1 = Program was turned off
#   2 = Abnormal Exit
# 
# 
# Example of running the program
# 
# 
# 
# ashers_toggle.sh 
### This will toggle conky. 
# 
# ashers_toggle.sh -p asherstint
### This will toggle a Desktop Application named asherstint
# 
# ashers_toggle.sh -p todo_list -n
### This will only start the program but make sure only one instance of the program is running.

DEBUG=1 # Yes turn DEBUG on
DEBUG=0 # NO turn DEBUG off. This can be changed in CLI options
PROGRAM=conky

COMPANY_NAME="ashersprograms.com"
COMPANY_NAME_PROPER="Ashers Programs.com"
PROGRAMS_NAME="ashers_toggle.sh"
PROGRAMS_NAME_PROPER="Ashers Toggle.sh"

VERSION="3.04"

# Internal Variables do NOT change
DEFAULT=1 # The Default program is being used otherwise the option -p was chosen.
NOKILL=0 # This option is if you do not want to Kill the program and Just start it up

# START OF FUNCTIONS
launch_conky(){
if [ $DEBUG -eq 1 ]; then echo "function launch_conky"; fi
CONKY_TEMP=$(mktemp --tmpdir=${XDG_RUNTIME_DIR:-/tmp} conky-startup.sh.XXXXXXXXXXXX)
sed -e 's/^[[:space:]]*sleep.*/sleep 1s/' "$HOME"/.conky/conky-startup.sh > $CONKY_TEMP
sh $CONKY_TEMP
rm $CONKY_TEMP
}
autostart_off(){
if [ $DEBUG -eq 1 ]; then echo "function autostart_off"; fi
if [ -e "$HOME"/.config/autostart/conky.desktop ]; then
    sed -i -r s/Hidden=.*/Hidden=true/ "$HOME"/.config/autostart/conky.desktop
fi
}
autostart_on(){
if [ $DEBUG -eq 1 ]; then echo "function autostart_on"; fi
if [ -e "$HOME"/.config/autostart/conky.desktop ]; then
    sed -i -r s/Hidden=.*/Hidden=false/ "$HOME"/.config/autostart/conky.desktop
fi
}
Debugging(){
    if [ $DEBUG -eq 1 ]; then echo "function Debugging"; fi
    DEBUG=1
}
main(){
    if [ $DEBUG -eq 1 ]; then echo "function main"; fi
    RESULTS=$(ps -aux | grep $PROGRAM | grep -c -v grep) # this is a Variable that I have know for a long time.
    RESULTS2=$(pgrep -c -u "$USER" -x $PROGRAM) # this was the original Variable that determined if the program was ON(running) or OFF(NOT running).
    #DEFAULT=0 # The DEFAULT program is NOT being used.
    if [ $DEFAULT -eq 0 ]; then # the default program is NOT being used and $RESULTS needs to be adjusted for some reason the results always come out 2 and if the program is running the results are 3.
        if [ $DEBUG -eq 1 ]; then echo "RESULTS will now be modified: " $RESULTS; fi
        let "RESULTS -= 2"; # Subtracting 2 if the default PROGRAM is NOT running.
        if [ $DEBUG -eq 1 ]; then echo "RESULTS Adjusted: " $RESULTS; fi
    fi
    if [ $DEBUG -eq 1 ]; then
        echo "The program to toggle is: " $PROGRAM
        echo "RESULTS: " $RESULTS
        echo "RESULTS2: " $RESULTS2
        echo "NUMBER2: " $NUMBER2
    fi
    
    let "RESULTS += $RESULTS2"; # Adds the two results.
    if [ $RESULTS -eq 0 ]; then # if both results both returned 0 then run the program.
        if [ $DEBUG -eq 1 ]; then echo "Starting the Program: " $PROGRAM; fi
        if [ $DEFAULT -eq 1 ]; then # DEFAULT program needs more adjusting
            if [ grep -q "conky -c" "$HOME"/.conky/conky-startup.sh 2>/dev/null ]; then
                launch_conky
                autostart_on
            else
                if command -v conky-manager2 >/dev/null; then
                    conky-manager2 &
                elif command -v conky-manager >/dev/null; then
                    conky-manager &
                fi
            fi
#        elif [ $PROGRAM == "synergy" ]; then # this where you can write exceptions in just add another elif with a new statement.
#            if [ $DEBUG -eq 1 ]; then echo "sysnergy is an exception program where special start up can go instead.\r\nPlease that this is just an example."; fi
#            $PROGRAM & >/dev/null
        else
            if [ $DEBUG -eq 1 ]; then echo "This is where most programs will be started from "; fi
            $PROGRAM & >/dev/null
        fi
        exit 0; # this will now give a proper exit code.
    else # else if both results were greater then 1 the stop the program.
        if [ $DEBUG -eq 1 ]; then echo "Stopping the Program: " $PROGRAM; fi 
        if [ $NOKILL == 0 ]; then
            killall -u "$USER" $PROGRAM --quiet
        fi
        if [ $PROGRAM == "synergy" ]; then
            if [ $DEBUG -eq 1 ]; then echo "extra killall for synergy: killall: " $PROGRAMB; fi
            PROGRAMB=synergys
            killall -u "$USER" $PROGRAMB --quiet 
        fi
        if [ $DEFAULT -eq 1 ]; then # Default program needs more adjusting
            if [ $DEBUG -eq 1 ]; then echo "autostart for conky is starting"; fi
            autostart_off
        fi      
        exit 1; # this will now give a proper exit code
    fi
}
Examples(){
    clear
    if [ $DEBUG -eq 1 ]; then echo "function Examples"; fi
    echo "******************************************************"
    echo "*********** $COMPANY_NAME_PROPER **********************"
    echo "*********** $PROGRAMS_NAME_PROPER *************************"
    echo "*********** Version: $VERSION ****************************"
    echo "******************************************************"
    echo "Syntax: $PROGRAMS_NAME [-d|e|g|h|n|p[ProgramsName]|v]"
    echo 
    echo "# Displays this Example Section"
    echo "$PROGRAMS_NAME -e"
    echo 
    echo "# Display the Help file"
    echo "$PROGRAMS_NAME -h"
    echo 
    echo "# Display the License"
    echo "$PROGRAMS_NAME -g"
    echo 
    echo "# Display the Version information"
    echo "$PROGRAMS_NAME -v"
    echo 
    echo "# Toggle Conky on and off (default with no parameters)"
    echo "$PROGRAMS_NAME"
    echo 
    echo "# Toggle another program like Synergy"
    echo "$PROGRAMS_NAME -p synergy"
    echo 
    echo "# No Lets Start a Program Only"
    echo "# and only one instance of the program"
    echo "$PROGRAMS_NAME -n -p mx-tools "
    echo 
    echo "# "
    echo "# To Start Up Debugging type"
    echo "# This is NOT recommended using these options in a program, "
    echo "#   these options are here for Developers ONLY"
    echo "$PROGRAMS_NAME -d"
    echo "$PROGRAMS_NAME -d -n -p mx-tools"
    echo "$PROGRAMS_NAME -d -p synergy"
    echo 
}
Help(){
    clear
    if [ $DEBUG -eq 1 ]; then echo "function Help"; fi
    # Display Help
    echo "Description of the script functions are:"
    echo 
    echo "Syntax: $PROGRAMS_NAME [-d|e|g|h|n|p[ProgramsName]|v]"
    echo "options:"
    echo "-d                 Turn Debug ON"
    echo "-e                 Print the Example for this Program."
    echo "-g                 Print the GPL license notification."
    echo "-h                 Print this Help."
    echo "-n                 Do not kill the program only start it up, with no repeat."
    echo "-p ProgramsName    Specify the program you want to toggle."
    echo "-v                 Print software version and exit."
    echo
}
exit_abnormal(){  # Function: Exit with error.
    if [ $DEBUG -eq 1 ]; then echo "function exit_abnormal"; fi
    Help
    exit 1
}
License(){
    if [ $DEBUG -eq 1 ]; then echo "function License"; fi
	# Display License notification
	echo 
	echo "License agreement is:"
	echo "https://www.gnu.org/licenses/gpl-3.0.en.html"
	echo 
}
Version(){
    echo "$COMPANY_NAME_PROPER"
    echo "$PROGRAMS_NAME_PROPER"
    echo "$VERSION"
}
# END OF FUNCTIONS

# PROGRAM STARTS HERE
while getopts ":deghnp:v" options; do #Get the command line options
    case "${options}" in    
        d) # Turn Debug On
            Debugging;
            echo "DEBUG is ON"
            ;;
        e) # Display Examples
            Examples;
            exit 0
            ;;
        g) # display license notification.
            License;
            exit 0
            ;;
        h) # display Help
            Help;
            exit 0
            ;;
        n) # Do not kill the program only start it up
            NOKILL=1
            ;;
        p) # user a different program
            PROGRAM=${OPTARG} # Set $PROGRAM to specified value.
            DEFAULT=0 # The DEFAULT program is NOT being used
            ;;
        v) #print version
            Version
            exit 0
            ;;
        \?) # Invalid option
            echo "Error: Invalid option(s)";
            Help;
            exit 0
            ;; 
        :)                                    # If expected argument omitted:
            echo "Error: -${OPTARG} requires an argument."
            exit_abnormal                       # Exit abnormally.
            ;;
        *)                                    # If unknown (any other) option:
            exit_abnormal                       # Exit abnormally.
            ;;
    esac
done
main
