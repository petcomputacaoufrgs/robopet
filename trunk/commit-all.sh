#!/bin/sh
if test $# -ne 2
then
	echo "usage: $0 message username"
else
	for projectname in ai communication gui radio simulation tracker robopet hismas .
	do
		./commit.sh $projectname "Commiting all robopet. $1" $2
	done

	./commit.sh hismas "Commiting all robopet. $1" $2
fi
