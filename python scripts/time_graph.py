import matplotlib.pyplot as plt
import numpy as np
import glob,os,sys
from scipy import stats

# usage : python time_graph.py <prefix of the files we want for the graph> <name of the figure>
# example : python time_graph.py random_10 random_10
#           selects all the files in 'results/raw/' starting with random_10, builds the 
#           figure and saves it in 'results/time graphs/random_10.png'
to_process = sys.argv[1]
figure = sys.argv[2]

filenames = [ os.path.splitext(os.path.basename(name))[0]
        for name in glob.glob('../results/raw/' + to_process + '_*')]

filenames = sorted(filenames)

fig = plt.figure()
plt.xlabel('Length')
plt.ylabel('Time (s)')

#Add a graph for Dynprog
csv_file = open('../results/raw/' + filenames[0] + '.csv', mode='r')
data = np.genfromtxt(csv_file, delimiter=',')
n = int((np.size(data, 0) - 1) / 10)
k = int(data[1][0])
length = np.array([data[i * 10 + 1][2] for i in range(n)])
time = np.array([np.mean(data[i * 10 + 1 : (i + 1) * 10, 4]) for i in range(n)])
time_std = np.array([np.std(data[i * 10 + 1 : (i + 1) * 10, 4]) for i in range(n)])
line,caps,bars = plt.errorbar(
	length, 
	time, 
	time_std, 
	fmt='o--',
	markersize=5,
	elinewidth=0.5,
	capsize=2,    
	capthick=0.5 
	)
plt.setp(line, label='FGKU')

#Add a graph for each epsilon
for filename in filenames:
	csv_file = open("../results/raw/" + filename + ".csv", mode='r')
	data = np.genfromtxt(csv_file, delimiter=',')
	n = int((np.size(data, 0) - 1) / 10)
	eps = data[1][1]
	length = np.array([data[i * 10 + 1][2] for i in range(n)])
	time = np.array([np.mean(data[i * 10 + 1 : (i + 1) * 10, 6]) for i in range(n)])
	time_std = np.array([np.std(data[i * 10 + 1 : (i + 1) * 10, 6]) for i in range(n)])
	line,caps,bars = plt.errorbar(
		length, 
		time, 
		time_std, 
		fmt='s--',
		markersize=5, 
		elinewidth=0.5,
		capsize=2,    
		capthick=0.5
		)
	plt.setp(line, label=r'$\varepsilon = $' + str(eps))

plt.legend(loc='upper left')    
plt.show()    
fig.savefig("../results/time graphs/" + figure + ".png", dpi=fig.dpi, bbox_inches='tight')
