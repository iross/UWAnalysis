'''
File: Selector.py
Author: Ian Ross
Description: Simple class to put together cut strings from lists.
'''

#from ROOT import *

class Selector:
    def __init__(self, arg1):
        self.cutsIn = arg1
    def cuts(self,accessor=""):
        cutS=""
        for i in self.cutsIn:
            cutS=cutS+accessor+i+"&&"
        #trim last &&
        if cutS.endswith("&&"):
            cutS=cutS[:-len("&&")]
        return cutS

def defineCuts(*args):
    cutS=""
    for i in args:
        cutS=cutS+i+"&&"
    #trim last &&
    if cutS.endswith("&&"):
        cutS=cutS[:-len("&&")]
    return cutS
