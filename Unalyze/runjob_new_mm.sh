#!/bin/sh

echo hello! now starting
date


echo now doing -- field

./analyze <<EOF
newlist_minusminus
outnew_minusminus.root
EOF

