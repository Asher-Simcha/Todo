#!/bin/sh
# AccuWeather (r) RSS weather tool for conky
#
# USAGE: weather.sh <locationcode>
# USAGE: weather.sh 	#the program will look up the weather for you
# USAGE: replace with your zip code line YOURZIPCODE 
#
# EXAMPLES:
# weather.sh
# weather.sh 85076
# change YOURZIPCODE to your zip code and run the program again
# weather.sh
# Date: 05-12-2023
# Last_Modified: 05-14-2023
METRIC=0 #Should be 0 or 1; 0 for F, 1 for C
YOURZIPCODE="null"
if [ "$YOURZIPCODE" != "null" ]; then
  CITY=$YOURZIPCODE
else
	if [ -z $1 ]; then
		# Get public IP address
		public_ip=$(curl -s https://api.ipify.org)
		# Use IP address to get geolocation information
		response=$(curl -s "https://ipapi.co/$public_ip/json/")
		# Extract zip code from the response
		CITY=$(echo "$response" | jq -r '.postal')
	else
		CITY=$1
	fi
fi
curl -s "http://rss.accuweather.com/rss/liveweather_rss.asp\?metric\=${METRIC}\&locCode\=$CITY" > /dev/null
testInternet=$(echo $?);
if [ $testInternet -eq 0 ]; then
    curl -s http://rss.accuweather.com/rss/liveweather_rss.asp\?metric\=${METRIC}\&locCode\=$CITY | perl -ne 'if (/Currently/) {chomp;/\<title\>Currently: (.*)?\<\/title\>/; print "$1"; }'
else
    echo "Internet NOT Available"
fi
