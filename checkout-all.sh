#!/bin/sh
if test $# -ne 1
then
	echo "usage: $0 username"
else
	for projectname in ai communication gui radio simulation tracker hismas
	do
		./checkout.sh $projectname $1
	done
fi
