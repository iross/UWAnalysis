mkdir -p $1
for state in "eleEle"
	do root -l -x -q dumpEventsTemp.C\(\"$1\",\"$state\"\) &> $1/$state$1 &
done
