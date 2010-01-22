#!/bin/sh
if test $# -ne 1
then
	echo "usage: $0 message"
else
	for projectname in ai communication gui radio simulation tracker robopet
	do
		./commit.sh $projectname "Commiting all robopet. $1"
	done
fi
