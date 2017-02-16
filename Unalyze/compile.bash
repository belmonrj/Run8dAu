#!/bin/bash
#g++ -o analyze hadrontree.cxx analyze.cxx -lstdc++ `root-config --libs` -I/opt/alice/root/v5-34-05/include
g++ -o analyze hadrontree.cxx analyze.cxx -lstdc++ `root-config --libs` -I$ROOTSYS/include
