#!/bin/bash
g++ -o tofwcali hadrontree.cxx tofwcali.cxx -lstdc++ `root-config --libs` -I/usr/local/root/include 
