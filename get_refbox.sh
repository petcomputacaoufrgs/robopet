#!/bin/sh

FOLDER=sslrefbox-2010.2
FILE=refbox.tar.gz
URL=http://small-size.informatik.uni-bremen.de/_media/referee:sslrefbox_2010.2.tar.gz

echo "Downloading SSL Referee Box...\n"
wget $URL -O refbox.tar.gz
tar -zxvf $FILE

echo -en "Installing...\n"
cd $FOLDER
make
sudo make install

echo "Done."
