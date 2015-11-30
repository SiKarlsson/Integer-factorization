#!/bin/bash
    tr '\n' ' ' | \
    sed 's/\s\+/ /g' | \
    sed 's/\([^a-zA-Z0-9'\''_]\) /\1/g' | \
    sed 's/ \([^a-zA-Z0-9'\''_%\($]\)/\1/g' | \
    sed 's/^ //' | \
    sed 's/\<return\>/R /g' | \
    sed 's/\<operator\>/O/g' | \
    sed 's/\<uint\>/U/g' | \
    sed 's/\<UInt\>/V/g' | \
    sed 's/\<value_size\>/S/g' | \
    sed 's/\<const\>/C/g' | \
    sed 's/\<table\>/T/g' | \
    sed 's/std:://g' | \
    sed 's/  / /g' | \
    cat > incl.h && wc -c incl.h
