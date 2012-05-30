#for f in f4*.root; do python combTrees.py $f zz$coup_zz_$f True; done

coup=$1

echo "Making stuff for "+$coup+"couplings"

for f in zz$coup*.root; do mv $f ${f/combed/}; done
for f in zz$coup*.root; do mv $f ${f/p/.}; done
for f in zz$coup*.root; do mv $f ${f/p/.}; done
for f in zz$coup*.root; do mv $f ${f/p/.}; done
for f in zz$coup*.root; do mv $f ${f/m/-}; done
for f in zz$coup*.root; do mv $f ${f/m/-}; done
for f in zz$coup*.root; do mv $f ${f/m/-}; done

python aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=muMuMuMuEventTreeMerged --output=f$coup\_mmmm_aTGC.root zz$coup\_zz_f4_*.root --weightAsBranch
python aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleMuMuEventTreeMerged --output=f$coup\_eemm_aTGC.root zz$coup\_zz_f4_*.root --weightAsBranch
python aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleEleEleEventTreeMerged --output=f$coup\_eeee_aTGC.root zz$coup\_zz_f4_*.root --weightAsBranch

#python aTGC_MCTreeMerger.py --obsVar="z1Pt" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=muMuMuMuEventTreeMerged --output=mmmm_ptaTGC.root zz$coup_zz_f4_*.root --weightAsBranch
#python aTGC_MCTreeMerger.py --obsVar="z1Pt" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleMuMuEventTreeMerged --output=eemm_ptaTGC.root zz$coup_zz_f4_*.root --weightAsBranch
#python aTGC_MCTreeMerger.py --obsVar="z1Pt" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleEleEleEventTreeMerged --output=eeee_ptaTGC.root zz$coup_zz_f4_*.root --weightAsBranch

#python aTGCRooStats/aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=muMuMuMuEventTreeFinal --output=mmmm_aTGC.root zz$coup_zz_f4_*.root --weightAsBranch
#python aTGCRooStats/aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleMuMuEventTree --output=eemm_aTGC.root zz$coup_zz_f4_*.root --weightAsBranch
#python aTGCRooStats/aTGC_MCTreeMerger.py --obsVar="mass" --intLumi=5000 --inputLumi=1 --par1Name=f4 --par2Name=f5 --treeName=eleEleEleEleEventTreeFinal --output=eeee_aTGC.root zz$coup_zz_f4_*.root --weightAsBranch
