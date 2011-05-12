#!/bin/bash

sudo apt-get install libpcre++-dev

wget "http://downloads.sourceforge.net/project/swig/swig/swig-2.0.2/swig-2.0.2.tar.gz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fswig%2F&ts=1305227026&use_mirror=ufpr" -O swig-2.0.2.tar.gz
tar -xf swig-2.0.2.tar.gz
cd swig-2.0.2 && ./configure && make && make install
