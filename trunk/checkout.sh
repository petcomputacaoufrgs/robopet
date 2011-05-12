#!/bin/sh
if test $# -ne 2
then
	echo "usage: $0 projectname username"
else
	echo "checkout $1 ..."
	if [ "$1" = "hismas" ]
	then
		svn checkout https://hismas.googlecode.com/svn/trunk hismas --username $2
	else
		svn checkout https://robopet-$1.googlecode.com/svn/trunk $1 --username $2
	fi
fi
