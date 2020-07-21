#!/bin/bash
# made by totallyNotAUser
# tested on cygwin's bash
# reads from command line args
# writes to stdout, each part on new line

input=$@
output=""

number_part=""
text_part=""

for (( i=0; i<${#input}; i++ ))
do
	if [[ ${input:i:1} =~ [0-9] ]] && [[ ${number_part:-1:1} != "." ]]
	then
		number_part="${number_part}${input:i:1}"
	elif [[ ${input:i:1} = "." ]] && [[ ${number_part:-1:1} != "." ]]
	then
		number_part="${number_part}."
	else
		number_part=${number_part%?}
		text_part="${input:i:number_part}"
		let "i+=number_part"
		output="${output}${text_part}\n"
		text_part=""
		number_part=""
		[[ ${input:i:1} = ";" ]] && break
	fi
done <<< "$input"

# or maybe echo?
printf "${output}"
