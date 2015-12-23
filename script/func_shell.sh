#!/bin/bash

yes_or_no() {
	echo "Is your name $1 ?"
	while true
	do
		echo "Enter yes or no: "
		read x
		case "$x" in
			y | yes ) return 0;;
			n | no  ) return 1;;
			* )			echo "Answer yes or no"
		esac
	done
}

echo "Original parameter are $*"

if yes_or_no $1
then
	echo "Hi $1, nice name"
else
	echo "Never Mind"
fi

exit 0
