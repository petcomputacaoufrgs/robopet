#!/bin/sh
if test $# -ne 1
then
	echo "usage: $0 projectname"
	echo "given: $*"
else
	echo "update $1 ..."
	if test $1 != "robopet"
	then
		cd robopet-$1
	fi
	svn update
	if test $1 != "robopet"
	then
		cd ..
	fi
fi

