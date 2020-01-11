import matplotlib.pyplot as plt
import numpy as np

filename = 'rand_10_2'
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

print("k = %d, eps = %.2f" % (int(data[1][0]), data[1][1]))
for key in dictionary:
	print("%d \t %.2f \t %.2f" %(key, min(dictionary[key]), max(dictionary[key])))

print("Error percentage: ", error / (np.size(data, 0) - 1))





