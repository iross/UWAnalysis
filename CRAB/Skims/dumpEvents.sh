mkdir -p $1
for state in "eleEleEleTau" "eleEleEleMu" "eleEleTauTau" "eleEleMuTau" "eleEleMuMu" "eleEleEleEle"
	do root -l -x -q dumpEventsTemp.C\(\"$1\",\"$state\"\) &> $1/$state$1 &
done
#wait for a bit to let the other guys finish
sleep 10
for state in "muMuEleTau" "muMuEleMu" "muMuTauTau" "muMuMuTau" "muMuMuMu" "muMuEleEle"
	do root -l -x -q dumpEventsTemp.C\(\"$1\",\"$state\"\) &> $1/$state$1 &
done
