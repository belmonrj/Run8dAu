#!/bin/sh

echo hello! now starting
date
echo now doing ++ field

./analyze <<EOF
newlist_plusplus
outnew_plusplus.root
EOF
