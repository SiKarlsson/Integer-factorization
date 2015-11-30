#!/bin/bash
cpp -m32 -P -nostdinc ttmath/ttmathuint.h | \
    tr '\n' ' ' | \
    sed 's/\s\+/ /g' | \
    sed 's/\([^a-zA-Z0-9'\''_]\) /\1/g' | \
    sed 's/ \([^a-zA-Z0-9'\''_%\($]\)/\1/g' | \
    sed 's/^ //' | \
    sed 's/  / /g' | \
    cat > incl.h && wc -c incl.h
