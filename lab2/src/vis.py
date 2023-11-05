import matplotlib.pyplot as plt
import csv

X = []
Y = []

with open('data.csv', 'r') as datafile:
    plotting = csv.reader(datafile, delimiter=';')

    for ROWS in plotting:
        X.append(float(ROWS[0]))
        Y.append(float(ROWS[1]))

plt.plot(X, Y)
plt.xlim([0, 16])
plt.ylim([0, 3500])
plt.ylabel(r'Время, мc', fontsize = 14)
plt.xlabel(r'Количество потоков', fontsize = 14)
plt.title(r'Время / число потоков. Матрица 1000 на 1001', fontsize = 15)
plt.grid(True)
plt.show()