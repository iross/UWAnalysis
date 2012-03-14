for f in `ls /hdfs/store/user/iross/EE_2011B*skim/*.root`
do
	echo $f
	edmFileUtil -e $f | grep -v -e "[a-zA-Z]" | grep -e "[0-9]" | awk -v variable=${f} '{printf "%s: %i %i %i\n",variable,$1,$2,$3}'
done
