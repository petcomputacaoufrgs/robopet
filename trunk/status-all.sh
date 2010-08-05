#!/bin/sh

for projectname in ai communication gui radio simulation tracker
	do
		echo svn status $projectname
		cd robopet-$projectname
		svn status
		cd ..
	done

