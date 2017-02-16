#!/bin/sh

echo hello! now starting
date
echo now doing ++ field

./analyze <<EOF
lowlist_plusplus
outlow_plusplus.root
EOF
