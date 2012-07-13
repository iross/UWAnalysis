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
	if len(args)<2:
		sys.exit(0)
		print "Try again! python checkEvents.py (fileName) (event type)"
	fileName = args[0]
	type = args[1]
	set = makeSet(fileName)
	num = 0
	numOnShell = 0
	for entry in set:
		#print entry
		if entry[3]==type:
			num = num+1
			if entry[4]>60 and entry[4]<120 and entry[5]>60 and entry[5]<120:
				numOnShell = numOnShell+1
			print entry
	print num,type,"events,",numOnShell,"on shell"

def makeSet(fileName): 
	tempList = []
	file = open(fileName)
	for line in file:
		li=line.strip()
		fields = line.split()
		#print fields
		try:
			name = str(fields[0])
			run = int(fields[1])
			event = int(fields[2])
			type = str(fields[3])
			z1m = float(fields[4])
			z2m = float(fields[5])
		except (IndexError,ValueError):
			continue
		try:
			weight = float(fields[4])
			corr = float(fields[5])
			corr = 1
		except (ValueError): #must be data... no weight or correction factor!
			weight=1
			corr=1
		tempList.append((name,run,event,type,z1m,z2m))
		#print tempList
	return tempList

if __name__ == "__main__":
	main()
