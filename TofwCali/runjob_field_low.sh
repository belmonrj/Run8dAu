#!/bin/sh

echo hello! now starting
date
echo now doing ++ field

./tofwcali <<EOF
lowlist_plusplus
outlow_plusplus.root
EOF

echo done with ++ field!
date
echo now doing -- field

./tofwcali <<EOF
lowlist_minusminus
outlow_minusminus.root
EOF

echo done with -- field!
echo all done!  have a nice day!
date
