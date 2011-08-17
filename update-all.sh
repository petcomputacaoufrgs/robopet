#!/bin/sh
for projectname in ai communication gui radio simulation tracker robopet hismas .
do
	./update.sh $projectname
done
