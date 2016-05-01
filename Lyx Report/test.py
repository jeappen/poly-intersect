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
    (0., 5.), # left, top
    (5., 5.), # right, top
    (5., 0.), # right, bottom
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
patch1 = patches.PathPatch(path, facecolor='none',hatch='|', lw=2)

ax.set_xlim(0,6)
ax.set_ylim(0,6)

verts = [
    (0., 0.), # left, bottom
    (0., 3.), # left, top
    (3., 3.), # right, top
    (3., 0.), # right, bottom
    (0., 0.), # ignored
    ]

codes = [Path.MOVETO,
         Path.LINETO,
         Path.LINETO,
         Path.LINETO,
         Path.CLOSEPOLY,
         ]
path = Path(verts, codes)
patch = patches.PathPatch(path, facecolor='blue',hatch='/', lw=2)
ax.add_patch(patch)
ax.add_patch(patch1)
 
         
plt.show()
#fig.savefig()