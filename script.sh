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

teamname1="EPK"
teamname2="Spy vs Spy"
port=8000

count1=0
count2=0
total_score1=0
total_score2=0

for (( c=0; c<$3; c++ ))
do
	isodate=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
	logfile="${team1}-${team2}-log-$c.log"

	(sleep 0 ; cd $1 ; ./agent 127.0.0.1 $port | sed -e 's/^/[p0] /' ) & > /dev/null 2>&1
	(sleep 0 ; cd $2 ; ./agent 127.0.0.1 $port | sed -e 's/^/[p1] /' ) & > /dev/null 2>&1

	bin/arena $port $logfile > /dev/null 2>&1
	winner=$(cat $logfile | grep "# Winner:" | cut -d "(" -f 2 | cut -d ")" -f 1)
	if [ "$(cat $logfile | grep "# Player 0:" | cut -d " " -f 4-)" == $teamname1 ]; then
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
		echo "$teamname1 win!"
	elsei
		let "count2=count2+1"
		echo "$teamname2 win!"
	fi
done
printf "\nResults:\n"
echo "$teamname1 $count1  -  $teamname2 $count2"
printf "Scores:\n"
echo "$teamname1 $total_score1  -  $total_score2 $teamname2"
printf "\nDo you want remove log files? (yes/no)\n"
read remove_log
if [ "$remove_log" == "yes" ]; then
	rm -f *.log
	rm -f *.log.*
fi
