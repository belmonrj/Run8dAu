#!/bin/bash
g++ -o analyze hadrontree.cxx analyze.cxx -lstdc++ `root-config --libs` -I/usr/local/root/include 
