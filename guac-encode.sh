#!/bin/bash
# made by totallyNotAUser
# reads from command line args
# writes to stdout

output=""
for i in "$@"
do
	output="${output},${#i}.${i}"
done

echo "${output:1};"
