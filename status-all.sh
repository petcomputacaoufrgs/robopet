#!/bin/sh

for projectname in ai communication gui radio simulation tracker
	do
		echo svn status $projectname
		cd $projectname
		svn status | grep ^[^?].*$
		cd ..
	done

