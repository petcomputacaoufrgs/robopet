#!/bin/sh
if test $# -ne 2
then
	echo "usage: $0 projectname message"
	echo "given: $*"
else
	echo "commit $1 ..."
	if test $1 != "robopet"
	then
		cd robopet-$1
	fi
	svn commit . -m "$2"
	if test $1 != "robopet"
	then
		cd ..
	fi
fi
