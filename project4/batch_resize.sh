#!/bin/bash

# Name:
# Project:
# File:
# Instructor:
# Class:
# LogonID:

# Reset
Color_Off='\e[0m'       # Text Reset

# Regular Colors
Black='\e[0;30m'        # Black
Red='\e[0;31m'          # Red
Green='\e[0;32m'        # Green
Yellow='\e[0;33m'       # Yellow
Blue='\e[0;34m'         # Blue
Purple='\e[0;35m'       # Purple
Cyan='\e[0;36m'         # Cyan
White='\e[0;37m'        # White

totalProcessed=0
totalOriginalSize=0
totalNewSize=0

# The usage function is to print out the help when an error occurs.
usage() {
  echo -e "${Green}Usage: $0 [/path/to/input] [path/to/output] [ratio-or-sequence-of-ratio]${Color_Off}";
  echo -e "${Green}Example: ./batch_resize.sh ./input ./output '20 30 50'${Color_Off}" 1>&2; exit 1;
}

# Function to count number of files processed. Using a function due to subshells
# being created with awk commands.
processed() {
  totalProcessed=$((totalProcessed++))
  echo $totalProcessed
}

# Function to count total file size before processing. Using a function due to subshells
# being created with awk commands.
countOriginalSize() {
  totalOriginalSize=$((totalOriginalSize+$1))
}

# Function to count total file size after processing. Using a function due to subshells
# being created with awk commands.
countNewSize() {
  totalNewSize=$((totalNewSize+$1))
}

# This if/else checks for 3 arguments. Without 3 arguments it automatically
# prints the Usage.
if [[ $# -ne 3 ]]; then
  echo -e "\n"
  echo -e "${Red}Invalid instructions.${Color_Off}"
  usage
fi

# This checks for help and if help is found it runs usage, as long as help is
# the first parameter
if [[ "$1" == "help" ]]; then
  usage
fi

# This checks if input is a directory or not. if not a directory prints usage.
if [[ ! -d "$1" ]]; then
  echo -e "${Red}Input directory is not a valid path.${Color_Off}"
  usage
else
  input="$1"
fi

# This checks for output directory. If it doesn't exist, it creates a directory.
# If the directory exists, it spits a warning and exits.
if [[ ! -d "$2" ]]; then
  echo -e "${Yellow}Directory does not exist. Creating directory.${Color_Off}"
  mkdir "$2"
  output="$2"
else
  echo -e "${Red}Directory already exists. Exiting program.${Color_Off}" 1>&2; exit 1;
fi

# This section handles the array of ratios.
IFS=', ' read -a array <<< "$3"
index="${#array[@]}"
stuff="$3"

# This section handles all the work.
shopt -s nullglob
while read f;
do
  len="${#input}"
  slice="${d:$len}"
  newDirectory="$output$slice/"
  dir=$(dirname "${f}")
  mkdir -p "${newDirectory}${dir#$1/}"
  for (( i = 0; i < $index; i++ ))
  do
    sourceName=$f
    base=$(basename "${f}")
    filename="${base%.*}"
    extension="${base##*.}"

    t=${dir#$1/}

    r="-r"
    appendResize="${array[i]}"
    tailFilename=$r$appendResize
    headFilename=$filename$tailFilename
    slash='/'
    dot='.'
    newFilename=$slash$headFilename$dot$extension
    target=$newDirectory$t$newFilename
    printedFilename=$headFilename$dot$extension


    convert -resize ${array[i]}% $f $target

    basesize=`wc -c $sourceName | awk '{print $1;}'`
    newsize=`wc -c $target | awk '{print $1;}'`
    echo -e "Hitting processed"
    processed
    countOriginalSize basesize
    countNewSize newsize
    # basesize=$(stat -c%s "$sourceName")
    # newsize=$(stat -c%s "$target")

    echo -e "${Cyan}Original image:                       ${base}.${Color_Off}"
    echo -e "${Cyan}Original image size:                  ${basesize}.${Color_Off}"

    echo -e "${Purple}New image:                            ${printedFilename}.${Color_Off}"
    echo -e "${Purple}New image size:                       ${newsize}.${Color_Off}"

    totalProcessed=$((totalProcessed+1))
    totalOriginalSize=$((totalOriginalSize+$basesize ))
    totalNewSize=$((totalNewSize+$newsize))
  done
done < <(find $input -type f)
echo -e "${Green}Total files processed:                 ${totalProcessed}.${Color_Off}"
echo -e "${Green}Total original file size in bytes:     ${totalOriginalSize} bytes.${Color_Off}"
echo -e "${Green}Total new file size in bytes:          ${totalNewSize} bytes.${Color_Off}"