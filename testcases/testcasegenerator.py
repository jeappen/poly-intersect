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
    xcen,ycen=0,0
    centroids=[]

   ''' for i in xrange(numvert):
        x=x+100**(i/9.6); 
        y=10000*(1-2**(i/(-13.0)))
        x=int(x)
        y=int(y)
        if(i==0):
            x,y=0,0
        xlist.append(x);ylist.append(y)
        print x,y;
    vert=zip(xlist,ylist)
    vert.append((9999,9999));
    vert.append((0,9999));
    vert.append(vert[0]);
    vertR=vert[:]
    vertR.reverse();
    for v in vertR[1:]:
        x1,y1=v
        fop.write("%d %d " % (x1,y1))
    clrspace(fop)

    fop.write("\n")'''




    
    verts = [
        (0., 0.), # left, bottom
        (0., 1e3), # left, top
        (1e3, 1e3), # right, top
        (1e3, 0.), # right, bottom
        (0., 0.), # ignored
        ]
    for v in verts[1:]:
        x1,y1=v
        xcen,ycen=0,0
        xcen=xcen+x1
        ycen=ycen+y1
        fop.write("%d %d " % (x1,y1))
    numsides=4.0
    xcen=xcen/numsides
    ycen=ycen/numsides
    centroids.append((xcen,ycen))
    clrspace(fop)

    fop.write("\n")
    vert5 = [
        (6.5e3, 3.5e3), # left, bottom
        (6.6e3, 3.5e3), # left, top
        (6.6e3, 0), # right, top
        (6.5e3, 0), # right, bottom
        (6.5e3, 3.5e3), # ignored
        ]
    for v in vert5[1:]:
        x1,y1=v
        fop.write("%d %d " % (x1,y1))
    clrspace(fop)


    vert2 = [
        (5e3, 1e3), # left, bottom
        (6e3, 5.8e3), # left, top
        (7e3, 1e3), # right, top
        (8e3, 5.8e3), # right, bottom
        (9e3, 1e3), # ignored
        (9e3, 0),
        (8e3, 5.3e3),
        (7e3, 0),
        (6e3, 5.3e3),
        (5e3, 0),
        ]
    fop.write("\n")
    for v in vert2:
        x1,y1=v
        fop.write("%d %d " % (x1,y1))
    clrspace(fop)

    vert2.append((5e3, 1e3));

    vert4 = [
        (1.8e3, 4.4e3), # left, bottom
        (1.8e3, 4.702e3), # left, top
       # (3e3, 1e3), # right, top
        (4.2e3, 4.702e3), # right, bottom
        (4.2e3, 4.4e3), # ignored
        (4e3, 4.701e3),
        (3e3, 1.1e3),
        (2e3, 4.701e3),
     #   (2e3, 4.6e3),
      #  (1e3, 0),
        ]
    fop.write("\n")
    for v in vert4:
        x1,y1=v
        fop.write("%d %d " % (x1,y1))
    clrspace(fop)

    vert4.append((1.8e3, 4.4e3));




    vert3 = [
        (1e3, 1e3), # left, bottom
        (2e3, 4.7e3), # left, top
        (3e3, 1e3), # right, top
        (4e3, 4.7e3), # right, bottom
        (5e3, 1e3), # ignored
        (5e3, 0),
        (4e3, 4.6e3),
        (3e3, 0),
        (2e3, 4.6e3),
        (1e3, 0),
        ]
    fop.write("\n")
    for v in vert3:
        x1,y1=v
        fop.write("%d %d " % (x1,y1))
    clrspace(fop)

    vert3.append((1e3, 1e3));




    print centroids

    fop.close()



 #   print len(vert)
 #   print list(vert)
    codes = [Path.MOVETO]
    for i in xrange(numvert+1):
        codes.append(Path.LINETO)
    codes.append(Path.CLOSEPOLY)
    path = Path(vert, codes)

    fig = plt.figure()
    ax = fig.add_subplot(111)
    patch = patches.PathPatch(path, facecolor='orange', lw=2)
    ax.add_patch(patch)
    ax.set_xlim(0,1e4)
    ax.set_ylim(0,1e4)


    
    codes = [Path.MOVETO,
             Path.LINETO,
             Path.LINETO,
             Path.LINETO,
             Path.CLOSEPOLY,
             ]

    path1 = Path(verts, codes)
    patch1 = patches.PathPatch(path1, facecolor='orange', lw=2)
    ax.add_patch(patch1)


    numvert1=8

    codes = [Path.MOVETO]
    for i in xrange(numvert1+1):
        codes.append(Path.LINETO)
    codes.append(Path.CLOSEPOLY)
    path2 = Path(vert2, codes)
    patch2 = patches.PathPatch(path2, facecolor='orange', lw=2)
    ax.add_patch(patch2)

    codes = [Path.MOVETO]
    for i in xrange(numvert1+1):
        codes.append(Path.LINETO)
    codes.append(Path.CLOSEPOLY)
    path3 = Path(vert3, codes)
    patch3 = patches.PathPatch(path3, facecolor='orange', lw=2)
    ax.add_patch(patch3)

    numvert2=5

    codes = [Path.MOVETO]
    for i in xrange(numvert2+1):
        codes.append(Path.LINETO)
    codes.append(Path.CLOSEPOLY)
    path4 = Path(vert4, codes)
    patch4 = patches.PathPatch(path4, facecolor='orange', lw=2)
    ax.add_patch(patch4)

    numvert3=2

    codes = [Path.MOVETO]
    for i in xrange(numvert3+1):
        codes.append(Path.LINETO)
    codes.append(Path.CLOSEPOLY)
    path5 = Path(vert5, codes)
    patch5 = patches.PathPatch(path5, facecolor='orange', lw=2)
    ax.add_patch(patch5)


    plt.show()
    
    
    
if __name__ == "__main__": main()