#!/bin/sh
if test $# -ne 0
then
	echo "usage: $0"
else
	for projectname in ai communication gui radio simulation tracker robopet
	do
		./update.sh $projectname
	done
fi

