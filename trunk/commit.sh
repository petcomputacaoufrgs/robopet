#!/bin/sh
if test $# -ne 3
then
	echo "usage: $0 projectname message username"
	echo "given: $*"
else
	echo "commit $1 ..."
	if test $1 != "robopet"
	then
		cd robopet-$1
	fi
	svn commit . -m "$2" --username $3 --no-auth-cache
	if test $1 != "robopet"
	then
		cd ..
	fi
fi
