#!/bin/bash

#########################      COLORS CODE     ##########################

PATH_EXEC="../miniRT"
EXPAND_BG="\033[K"
RED="\033[38;5;203m"
RED_B="\033[40;1;38;2;255;65;65m"
RED_E="\033[48;5;203;1;38;5;16m"
ORANGE="\033[38;5;215m"
YELLOW="\033[38;5;229m"
GREEN="\033[38;5;121m"
GREEN_B="\033[40;1;38;5;83m"
LIGHT_BLUE="\033[38;5;123m"
BLUE="\033[1;38;5;33m"
BLUE_B="\033[40;1;38;5;33m"
WHITE_B="\033[40;1;37m"
RESET="\033[0m"

#########################     INITIALISATION    ##########################

sum=0
right=0
false=0
COLS=$(tput cols)
SEP="..................................................................................."
TITLE=".............................  START TEST  ............................"
END="..............................  END TEST  ............................."
COLS=$(tput cols)

###########################   TEST FUNCTION   ###########################

function execute_test()
{
	$PATH_EXEC/miniRT $@ 2> result.txt
	# if [ "$(head -1 result.txt)" = "$(head -1 files/ref.txt)" ]
	if [[ $(head -1 result.txt) == "$(head -1 files/ref.txt)" ]]
	then
		echo -e "${GREEN}   ✔  $1${RESET}"
		right=`expr $right + 1`
	else
		echo -e "${RED}   ✘  $1${RESET}"
		false=`expr $false + 1`
	fi
	rm result.txt
}

function run_test()
{
	ERROR_MAP=$(find files/error_map -type f -name "*.rt" -print | sort -n)
	for FILE in $ERROR_MAP
	do
		execute_test $FILE
		sum=`expr $sum + 1`
	done
		
	ERROR_FILES=$(find files/error_file -type f -name "wrong_ext*" -print | sort -n)
	for FILE in $ERROR_FILES
	do
		execute_test $FILE
		sum=`expr $sum + 1`
	done

	CORRECT_FILES=$(find files/correct_file -type f -name "*.rt" -print | sort -n)
	for FILE in $CORRECT_FILES
	do
		execute_test $FILE
		sum=`expr $sum + 1`
	done
}

#############################       MAIN      ############################

make -C ../miniRT
if [ -f "$PATH_EXEC/miniRT" ]
then
	printf "\n${BLUE}%*s${RESET}\n" $(((${#TITLE} + $COLS) / 2)) "$TITLE"
	printf "\n"
	run_test
	printf "\n${BLUE}%*s${RESET}\n\n" $(((${#END} + $COLS) / 2)) "$END"
	RESULT=`echo -e "${GREEN_B}  $right passed,${RESET}${RED_B}  $false failed,${RESET}${WHITE_B}  $sum total  ${RESET}"`
	printf "\n%*s\n\n" $(((${#RESULT} + $COLS) / 2 + 29)) "$RESULT"
	# rm $PATH_EXEC//miniRT
else
	PROBLEM=`echo -e "${RED}------ Problem compilation ------${RESET}"`
	printf "\n%*s\n\n" $(((${#PROBLEM} + $COLS) / 2)) "$PROBLEM"
fi
