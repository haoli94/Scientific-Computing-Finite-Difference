
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import os
import sys
import matplotlib.animation as animation
if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} <input file> <prefix>'.format(sys.argv[0]))
    sys.exit(0)
input_file = sys.argv[1]
soln_prefix = sys.argv[2]
# read the arguments from console and prompt usage information if not enough arguments are given
number = ""
for i in input_file:
    if i.isdigit():
        number = i
soln_prefix += number
name_list = []
# create the right solution file prefix with the number in input_file
with open(input_file,"r") as fin:
    plot_width,plot_height,h = fin.readline().split()
    plot_width,plot_height,h = float(plot_width),float(plot_height),float(h)
    tc, th = (float(x) for x in fin.readline().split());
# get important parameters form the input_file
for i in list(os.walk("./"))[0][2]:
    if soln_prefix in i:
        name_list.append(i)
# find the right solution files and store them in a namelist
fig2 = plt.figure()
y, x = np.mgrid[0.:plot_height+h:h, 0.:plot_width+h:h]
#create the x,y axis ticks with np.mgrid
ims = []
for name in name_list:
    with open(name, "r") as f:
        rows, cols = f.readline().split()
        rows = int(rows) + 2
        cols = int(cols)
        data = f.readlines()
    matrix = np.zeros(rows*cols).reshape(rows,cols)
    for i in range(len(data)):
        row = i // cols
        col = i % cols
        v = data[i].strip()
        matrix[row][col] = float(v)
    ims.append((plt.pcolor(x, y,matrix,vmin=tc, vmax=th),))
    #read the data from each solution file and store them in the ims list
im_ani = animation.ArtistAnimation(fig2, ims, interval=300, repeat_delay=1000,
    blit=True)
# create the animation
plt.colorbar()
plt.show()
