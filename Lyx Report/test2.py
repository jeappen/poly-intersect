import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.path as mpath
import matplotlib.lines as mlines
from matplotlib.collections import PatchCollection
plt.rcdefaults()

x=[0,0,10,10]
y=[0,10,10,0]
verts = [
    (0., 0.), # left, bottom
    (0., 10.), # left, top
    (10., 10.), # right, top
    (10., 0.), # right, bottom
    (0., 0.), # ignored
    ]

codes = [Path.MOVETO,
         Path.LINETO,
         Path.LINETO,
         Path.LINETO,
         Path.CLOSEPOLY,
         ]

path = Path(verts, codes)

fig = plt.figure()
ax = fig.add_subplot(111)
patch = patches.PathPatch(path, facecolor='none',hatch='|', lw=2)

ax.set_xlim(0,11)
ax.set_ylim(0,11)

verts = [
    (5., 0.), # left, bottom
    (0., 5.), # left, top
    (5., 10.), # right, top
    (10., 5.), # right, bottom
    (5., 0.), # ignored
    ]

codes = [Path.MOVETO,
         Path.LINETO,
         Path.LINETO,
         Path.LINETO,
         Path.CLOSEPOLY,
         ]
path = Path(verts, codes)
patch1 = patches.PathPatch(path, facecolor='green',hatch='/', lw=2)
ax.add_patch(patch1)
ax.add_patch(patch)
 
         
plt.show()
#fig.savefig()