#!/bin/sh
if test $# -ne 2
then
	echo "usage: $0 projectname username"
	echo "given: $*"
else
	echo "update $1 ..."
	if test $1 != "robopet"
	then
		cd $1
	fi
	svn update --username $2
	if test $1 != "robopet"
	then
		cd ..
	fi
fi

