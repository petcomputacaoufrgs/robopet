#!/bin/sh

FOLDER=Box2D_v2.1.2
FILE=$FOLDER.zip
URL=http://box2d.googlecode.com/files/$FILE

echo "Downloading Box2D...\n"
wget $URL
unzip $FILE

echo -en "Installing...\n"
cd $FOLDER/Box2D/Build
cmake -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=ON ..
make
sudo make install

#echo "Now cd to the Box2D folder and do a 'sudo make install'"
echo "Done."
