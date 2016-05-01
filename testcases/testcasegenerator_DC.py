import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches
import os

def clrspace(fop):
    fop.seek(-1, os.SEEK_END)
    fop.truncate()



def main():

  

    
	n=6; numvert=18


	fop= open('input1.txt','w')

	fop.write("%d\n" % n)
	i=0
	x,y=0,0
	xlist,ylist=[],[]
	n,f=9999,9998
	fop.write("%d %d" % (n,f))
	clrspace(fop)

	fop.write("\n")
	fop.write("%d %d\n" % (10,5));
	fop.write("%d %d\n" % (0,20));
	for i in xrange(997):
		x1,y1=120,20
		fop.write("%d %d " % (x1,y1))

	clrspace(fop)
	fop.close()


    
    
    
if __name__ == "__main__": main()