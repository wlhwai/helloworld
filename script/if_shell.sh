#!/bin/sh

echo "Is is morning? Please answer yes or no : "
read timeofday

if [ "$timeofday" = "yes" ]; then
	echo "Good Morning!"
elif [ "$timeofday" = "no" ]; then
	echo "Good Evening!"
else
	echo "Sorry, $timeofday is note recognized. Enter yes or no"
	exit 1
fi

exit 0
