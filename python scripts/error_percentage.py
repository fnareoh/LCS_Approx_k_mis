import matplotlib.pyplot as plt
import numpy as np
import glob,os,sys

# usage : python error_percentage.py <dataset>
# example : python time_graph.py random 
#           selects all the files in 'results/raw/' starting with 'random', builds the 
#           table and saves it in 'results/error percentage/random.csv'
dataset = sys.argv[1]

filenames = [ os.path.splitext(os.path.basename(name))[0]
        for name in glob.glob('../results/raw/' + dataset + '_*')]
        
filenames = sorted(filenames)

output = open('../results/error percentage/' + dataset + '.csv', mode='w')
output.write('k, eps, min_factor, max_factor, error\n')

for filename in filenames:
	csv_file = open('../results/raw/' + filename + '.csv', mode='r')
	data = np.genfromtxt(csv_file, delimiter=',')
	
	error = 0
	for row in data[1:]:
		if row[5] > row[7]:
			error += 1

	min_factor = np.min(data[1:,7].astype(float)/data[1:,5])
	max_factor = np.max(data[1:,7].astype(float)/data[1:,5])

	k = data[1,0]
	eps = data[1,1]

	output.write("%d, %.2f, %.2f, %.2f, %.2f\n" % (k, eps, min_factor, max_factor, error / (np.size(data, 0) - 1)))





