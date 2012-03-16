for f in `ls /hdfs/store/user/iross/MM_2011Bv1_skim/*.root`
do
	echo $f
	edmFileUtil -e $f | grep -v -e "[a-zA-Z]" | grep -e "[0-9]" | awk -v variable=${f} '{printf "%s: %i %i %i\n",variable,$1,$2,$3}' | grep -E "178866|140063742"
done
