
'''GLOBAL VARIABLES'''
x,y=[],[]



def BAD():
    print("BAD")

def isNonNegInt(s):
    try: 
        i=int(s)
        if i>=0:
            return True
        else:
			return False
    except ValueError:
        return False

def isPolyProper(x,y):
	return True
    

def polycheck(line,xl,yl):
	l=len(line)
	is_y=False
	#return True
	if(l%2==1 or l>40):
		return True;
	x,y=[],[]
	for i in line:
		if isNonNegInt(i)==False:
#			print "non"
			return True
		else:
			coord=int(i);
			if is_y:
			    y.append(coord);
			    is_y=False
			else:
			    x.append(coord);
			    is_y=True
	if isPolyProper(x,y)==False:
#		print "polynot"
		return True;
	#xl=x[:];
	#yl=y[:];
	#print xl,yl
	return False,x,y
	# elif i<0:

    
    #elif(NotNonNegInt):
     #   return True

def main():    
	f= open('input.txt')
	fop= open('output.txt','w')
	i=0;    
	a=0;
	centroids=[]
	n=int(f.readline());
	checkBAD=False; BADPoly=0;
	polycentroids=[]
	for line in f: #for i in xrange(n):
	    #line=raw_input().split();
		i=i+1;
		xl,yl=[],[]
		polycheckop,xl,yl=polycheck(line.split(),xl,yl)
		if checkBAD==False and (polycheckop or '  ' in line):
			checkBAD=True; BADPoly=i;
		print xl,yl
		xcen,ycen=0,0
		for v in zip(xl,yl):
			x1,y1=v
			xcen=xcen+x1
			ycen=ycen+y1
		l=len(xl)*1.0;
		xcen=xcen/l;
		ycen=ycen/l;
	#print xcen,ycen;
		centroids.append((xcen,ycen))
	f.close()

	print centroids
	A=[]
	row=[]
	for c in centroids:
		x1,y1=c
		row=[]
		for c2 in centroids:
			x2,y2=c2;
			d=((x1-x2)**2+(y1-y2)**2)**(.5)
			#print d
			row.append(d)
		A.append(row)

	for row1 in A:
		print row1

	print '\n'
	
	print A[0][3],A[3][1],A[1][5],'6-7',A[5][6],'6-3',A[5][2],A[2][4],'6-8',A[5][7],A[7][9],A[9][8],A[8][5]
	if(checkBAD):
	    print "BAD",BADPoly
	    fop.write("BAD %d" % BADPoly)
	fop.close()

if __name__ == "__main__": main()

        