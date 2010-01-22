#!/bin/sh
if test $# -ne 2
then
	echo "usage: $0 projectname username"
else
	echo "checkout $1 ..."
	svn checkout https://robopet-$1.googlecode.com/svn/trunk robopet-$1 --username $2@gmail.com
fi
