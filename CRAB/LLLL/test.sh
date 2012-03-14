for f in `ls /hdfs/store/data/Run2011A/DoubleElectron/AOD/05Jul2011ReReco-ECAL-v1/0000/*.root`
do
	echo $f
	edmFileUtil -e $f | grep -v -e "[a-zA-Z]" | grep -e "[0-9]" | awk -v variable=${f} '{printf "%s: %i %i %i\n",variable,$1,$2,$3}' | grep 876658967
done
