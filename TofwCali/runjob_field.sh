#!/bin/sh

echo hello! now starting
date
echo now doing ++ field

./tofwcali <<EOF
inlist_plusplus
out_plusplus.root
EOF

echo done with ++ field!
date
echo now doing -- field

./tofwcali <<EOF
inlist_minusminus
out_minusminus.root
EOF

echo done with -- field!
echo all done!  have a nice day!
date
