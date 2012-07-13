import getopt
import sys
from math import sqrt

class eventClass:
	def __init__(self, mydata):
		self.mydata = mydata
	def __hash__(self):
		return hash( (self.mydata[0], self.mydata[1]))
	def __eq__(self,other):
		return self.mydata[0] == other.mydata[0] and self.mydata[1] and other.mydata[1]

def main():
	try:
		opts, args = getopt.getopt(sys.argv[1:], "ho:v", ["help", "output="])
	except getopt.GetoptError, err:
		# print help information and exit:
		print str(err) # will print something like "option -a not recognized"
		usage()
		sys.exit(2)
	if len(args)<4:
		print "Wrong number of parameters!"
		print "Try doing it right: python % (channel1) (channel2) (sample) (lumi) (do all? optional)"
		sys.exit(0)
	doall=False
	channel1=args[0]
	channel2=args[1]
	sample=args[2]
	if len(args) > 4:
		doall=args[4]
	lumi=1
	if sample.find("DATA")==-1:
		lumi=args[3]
	#overlap(channel1, channel2, sample, lumi)
	massMap = {}
	channel2=overlapChannelDef(channel1)
#	for mass in ("180","190","200","210","220","230","250","275","300","325","350","375","400","425","450","475","500","525","550","575","600"):
#		yieldz=overlap(channel1,channel2,sample+mass,lumi)
#		massMap[mass]=yieldz[0]-yieldz[1] #get yields - overlap
	#yieldz=overlap(channel1,channel2,sample,lumi)
	#print "corrected yield:",yieldz[0]-yieldz[1],"\pm",yieldz[2]
	#samples=["H200","H250","H300","H400","H500"]
	samples=["ZZ4L_pythia"]
	lines=[]
	for chan in ("muMuTauTau","eleEleTauTau","eleEleEleTau","muMuEleTau","muMuMuTau","eleEleMuTau","eleEleEleMu","muMuEleMu","eleEleEleEle","muMuEleEle","eleEleMuMu","muMuMuMu"):
		tableLine(chan,samples,lumi)
	yieldString=""
	for i in sorted(massMap):
		print i,massMap[i]
		if (i=="600"):
			yieldString += str(massMap[i])
		else:
			yieldString += str(massMap[i])+","
	print "%syields->set%s(%s);" % (channel1.swapcase(), sample, str(yieldString)) 
#	if doall==True:
#		for channelloop in ["eeet","eett","eeem","eemt","mmet","mmtt","mmem","mmmt"]:
#			table(channelloop,sample,lumi)

def overlap(channel1,channel2, sample, lumi):
	file1 = open("eventDumps/"+sample+"/"+channel1+sample)
	file2 = open("eventDumps/"+sample+"/"+channel2+sample)
	#file1 = open(""+channel1+sample)
	#file2 = open(""+channel2+sample)
	lumi = int( lumi)
	
	file1set = makeSet(file1,sample)
	file2set = makeSet(file2,sample)
	
	#overlap=file1set.intersection(file2set)
	overlap=[]
	overlap=checkOverlap(file1set,file2set)
	total=0.0
	totalErr=0.0
	for event in file1set:
		total+=event[2]*event[3]*lumi
		totalErr+=event[2]*event[2]*event[3]*event[3]*lumi*lumi
	#print channel1,"yield",total,"pm",sqrt(totalErr)
	channel1Tot=total
	channel1Err=sqrt(totalErr)
	total=0.0
	totalErr=0.0
	for event in file2set:
		total+=event[2]*event[3]*lumi
		totalErr+=event[2]*event[2]*event[3]*event[3]*lumi*lumi
	#print channel2,"yield",total,"pm",sqrt(totalErr)
	totalOverlap=0
	totalOverlapErr=0
	for overlapEvent in overlap:
		totalOverlap+=overlapEvent[2]*overlapEvent[3]*lumi
		totalOverlapErr+=overlapEvent[2]*overlapEvent[2]*overlapEvent[3]*overlapEvent[3]*lumi*lumi
	#for item in overlap:
	#	f.write("%s\n",item)
	#f.close()
	#print "Event set: ",channel1,":",len(file1set),channel2,":",len(file2set),"overlap:",len(overlap)
	return channel1Tot,totalOverlap,channel1Err 
#print overlap.difference(overlap)

def tableLine(channel,samples,lumi):
	tempYields=[]
	overlapChannel=overlapChannelDef(channel)
	for sample in samples:
		tempYields.append(overlap(channel,overlapChannel,sample,lumi))
		#print "-------"+sample+"--------"
		#print channel,"${0:.2f} \pm {1:.2f}$".format(tempYields[0][0]-tempYield[1],tempYield[2])
		#print "---------------"
	#print tempYields
	# print line in table form.
	line = ""
	line += rowLabel(channel)
	for samp in tempYields:
		line+="& $ {0:.2f} \pm {1:.2f} ({2:.2f}-{3:.2f})$".format(samp[0]-samp[1],samp[2],samp[0],samp[1])
		#line+="& $ {0:.2f} \pm {1:.2f}$".format(samp[0],samp[2]) # print raw values
		#print "overlap",samp[1]
	line+=" \\\\"
	print line
	return line

def overlapChannelDef(channel):
	if channel=="eleEleEleTau":
		return "eleEleEleEle"
	elif channel=="muMuEleTau":
		return "muMuEleEle"
	elif channel=="eleEleTauTau":
		return "eleEleEleTau"
	elif channel=="muMuTauTau":
		return "muMuEleTau"
	elif channel=="muMuMuTau":
		return "muMuMuMu"
	elif channel=="eleEleMuTau":
		return "muMuEleEle"
	elif channel=="muMuEleMu": #dummy -- overlap negligible, but needs to be defined
		return "muMuEleEle"
	elif channel=="eleEleEleMu":
		return "muMuEleEle"
	else:
		return "dummy"

def makeSet(file,sample): 
	tempSet = set([])
	tempList = []
	weight=1
	corr=1
	for line in file:
		li=line.strip()
		fields = line.split('*')
		try:
			event = int(fields[2])
			met = float(fields[3])
		except (IndexError,ValueError):
			continue
		#if not sample=='DATA' and not sample=='DATAfake': 
		try:
			weight = float(fields[4])
			corr = float(fields[5])
			corr = 1
		except (ValueError): #must be data... no weight or correction factor!
			weight=1
			corr=1
		
		tempList.append((event,met,weight,corr))
		tempSet.add((event,met,weight,corr))
	return tempList

def checkOverlap(list1,list2):
	overLapList=[]
	for entry in list1:
		for entry2 in list2:
			if entry[0]==entry2[0] and entry[1]==entry2[1]:
				overLapList.append(entry)
	return overLapList

def rowLabel(channel):
	if channel=="eleEleEleTau":
		return "$ee\\tau_{e}\\tau_{h}$ "
	elif channel=="muMuEleTau":
		return "$\mu\mu\\tau_{e}\\tau_{h}$ "
	elif channel=="eleEleTauTau":
		return "$ee\\tau_{h}\\tau_{h}$ "
	elif channel=="muMuTauTau":
		return "$\mu\mu\\tau_{h}\\tau_{h}$ "
	elif channel=="muMuMuTau":
		return "$\mu\mu\\tau_{\mu}\\tau_{h}$ "
	elif channel=="eleEleMuTau":
		return "$ee\\tau_{\mu}\\tau_{h}$ "
	elif channel=="muMuEleMu": 
		return "$\mu\mu\\tau_{e}\\tau_{\mu}$ "
	elif channel=="eleEleEleMu":
		return "$ee\\tau_{e}\\tau_{\mu}$ "
	else:
		return channel
if __name__ == "__main__":
	main()
