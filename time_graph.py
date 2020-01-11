import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

filenames = ["e_coli_10_1", "e_coli_10_1,5", "e_coli_10_2"]
fig = plt.figure()
plt.xlabel('Length')
plt.ylabel('Time (s)')

#Add a graph for each epsilon
for filename in filenames:
	csv_file = open('data/' + filename + '.csv', mode='r')
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

#Add a graph for Dynprog
csv_file = open('data/' + filenames[0] + '.csv', mode='r')
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
plt.setp(line, label='Dynprog')
plt.legend(loc='upper left')
    
plt.show()    
fig.savefig('figures/' + "e_coli_" + str(k) + '.png', dpi=fig.dpi, bbox_inches='tight')
