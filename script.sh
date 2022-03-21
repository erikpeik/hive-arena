#!/usr/bin/env bash

set -e

if [ $# -ne 3 ]; then
    echo "Usage: ./script.sh [agent0_directory] [agent1_directory] [how many rounds]"
    exit 1
fi

make -C src
make -C $1
make -C $2

team1=$(basename $1)
team2=$(basename $2)

teamname1="Eerikin Pippuri Kebab"
teamname2="Triangle"
port=8000

count1=0
count2=0
total_score1=0
total_score2=0

RED='\033[0;31m'
LRED='\033[1;31m'
LGREEN='\033[1;32m'
LGRAY='\033[0;37m'
LBLUE='\033[1;34m'
YELLOW='\033[1;33m'
NOCOL='\033[0m'


for (( c=0; c<$3; c++ ))
do
	isodate=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
	logfile="${team1}-${team2}-log-$c.log"

	(sleep 0.3 ; cd $1 ; ./agent 127.0.0.1 $port | sed -e 's/^/[p0] /' ) & > /dev/null 2>&1
	(sleep 0.3 ; cd $2 ; ./agent 127.0.0.1 $port | sed -e 's/^/[p1] /' ) & > /dev/null 2>&1

	bin/arena $port $logfile > /dev/null 2>&1
	winner=$(cat $logfile | grep "# Winner:" | cut -d "(" -f 2 | cut -d ")" -f 1)
	if [ "$(cat $logfile | grep "# Player 0:" | cut -d " " -f 4-)" == "$teamname1" ]; then
		score1=$(tail -n2 $logfile | head -n1 | cut -d "," -f 4)
		score2=$(tail -n2 $logfile | head -n1 | cut -d "," -f 5)
	else
		score2=$(tail -n2 $logfile | head -n1 | cut -d "," -f 4)
		score1=$(tail -n2 $logfile | head -n1 | cut -d "," -f 5)
	fi
	let "total_score1=total_score1+score1"
	let "total_score2=total_score2+score2"
	printf "GAME ${c}: $teamname1 $score1 - $score2 $teamname2\n"
	if [ "$winner" == "$teamname1" ];
	then
		let "count1=count1+1"
		printf "${LGREEN}$teamname1 win!${NOCOL}\n"
	elif [ "$winner" == "$teamname2" ]; then
		let "count2=count2+1"
		printf "${LRED}$teamname2 win!${NOCOL}\n"
	else
		printf "${YELLOW}DRAW${NOCOL}\n"
	fi
done
printf "\n${LBLUE}Results:${NOCOL}\n"
echo "$teamname1	VS  $teamname2"
echo "$count1	-  $count2"
let "total_count=count1+count2"
PERCENT1=$(echo "$count1/$total_count * 100" | bc -l)
PERCENT2=$(echo "$count2/$total_count * 100" | bc -l)
printf %.2f $PERCENT1
printf "%%	-  "
printf %.2f $PERCENT2
printf "%%\n"
printf "${LBLUE}Scores:${NOCOL}\n"
echo "$teamname1	VS $teamname2"
echo "$total_score1	-  $total_score2"
let "total_max=total_score1+total_score2"
PERCENT1=$(echo "$total_score1/$total_max * 100" | bc -l)
PERCENT2=$(echo "$total_score2/$total_max * 100" | bc -l)
printf %.2f $PERCENT1
printf "%%	-  "
printf %.2f $PERCENT2
printf "%%\n"
printf "\nDo you want remove log files? (yes/no)\n"
read remove_log
if [ "$remove_log" == "yes" ]; then
	rm -f *.log
	rm -f *.log.*
fi
