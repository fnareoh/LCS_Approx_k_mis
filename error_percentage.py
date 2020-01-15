import matplotlib.pyplot as plt
import numpy as np

filename = 'e_coli_25_2.000000'
csv_file = open('data/' + filename + '.csv', mode='r')
data = np.genfromtxt(csv_file, delimiter=',')
error = 0

dictionary = {}

for row in data[1:]:
	if row[5] > row[7]:
		error += 1
	if int(row[2]) in dictionary:
		dictionary[int(row[2])].append(float(row[7]) / row[5])
	else:
		dictionary[int(row[2])] = [float(row[7]) / row[5]]

output = open('data/' + filename + '_err.csv', mode='w')
output.write("k = %d, eps = %.2f\n" % (int(data[1][0]), data[1][1]))
for key in dictionary:
	output.write("%d \t %.2f \t %.2f\n" % (key, min(dictionary[key]), max(dictionary[key])))

output.write("Error percentage: %.2f\n" % (error / (np.size(data, 0) - 1)))





