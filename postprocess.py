import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import bisect
import sys
from scipy.interpolate import interp1d

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} <input file> <solution file>'.format(sys.argv[0]))
    sys.exit(0)
input_file = sys.argv[1]
soln_file = sys.argv[2]
# read the arguments from console and prompt usage information if not enough arguments are given
with open(input_file,"r") as fin:
    plot_width,plot_height,h = (float(x) for x in fin.readline().split())
# get important parameters form the input_file
print("Input file processed: "+input_file)
# print out input the file processed
with open(soln_file,"r") as f:
    rows,cols = f.readline().split()
    rows = int(rows)+2
    cols = int(cols)
    data = f.readlines()
data_matrix = [[0 for i in range(cols)]for j in range(rows)]
# read the solution from the solution file
for i in range(len(data)):
    row = i//cols
    col = i%cols
    v = data[i].strip()
    data_matrix[row][col] = float(v)
newdata = np.array(data_matrix).reshape(rows, cols)
# read the solution from the solution file and transform it into numpy data form
mean_temp = np.mean(newdata)
# compute the mean temperature
print("Mean Temperature: %.5f"%mean_temp)
# print out the mean temperature
mean_templine = []
for j in range(cols):
    mean_templine.append(bisect.bisect(newdata[:,j],mean_temp))
fig = plt.figure(figsize=(6,3),dpi=75,facecolor='#666666',edgecolor='#0000FF')
plt.xlim(0,cols-1)
plt.ylim(0,rows-1)
plt.imshow(data_matrix,origin ="lower")
temp = mean_templine[0]
# plot the temperature inside the pipe wall
x_index = [0]
y_values = [mean_templine[0]]
for i in range(1,len(mean_templine)):
    if mean_templine[i] != temp:
        x_index.append(i)
        y_values.append(mean_templine[i])
        temp = mean_templine[i]
x_index.append(len(mean_templine))
y_values.insert(len(y_values)//2,y_values[len(y_values)//2])
x_new = np.arange(0,cols,h)
f = interp1d(x_index,y_values,kind='cubic')
y_smooth= f(x_new)
# utilize scipy.interpolate to smooth the mean temperature line
x = np.linspace(0,cols-1,6)
adjusted_x = np.linspace(0,plot_width,6)
for i in range(len(adjusted_x)):
    adjusted_x[i] = np.round(adjusted_x[i],2)
y = np.linspace(0,rows-1,6)
adjusted_y = np.linspace(0,plot_height,6)
for i in range(len(adjusted_y)):
    adjusted_y[i] = np.round(adjusted_y[i],2)
# rescale the x,y labels and ticks
plt.colorbar()
# add the colorbar
plt.plot(x_new,y_smooth,color = "black",lw=2.5)
plt.xticks(x, adjusted_x,color='black')
plt.yticks(y, adjusted_y,color='black')
plt.show()
