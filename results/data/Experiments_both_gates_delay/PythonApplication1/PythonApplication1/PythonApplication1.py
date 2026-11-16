from re import M
import numpy as np
import matplotlib.pyplot as plt

#timpul pleaca de la M la N
M=1
N=8848
# Citește datele din fișierul text
file_path = '2GatesDelay.txt'

# Citim fișierul text
with open(file_path, 'r') as file:
    lines = file.readlines()

# Procesăm datele
data = []
for line in lines:
    # Împărțim fiecare linie în funcție de spații
    parts = line.strip().split()
    # Excludem ultima coloană (frecvența)
    data.append(parts[:-4])

# Convertim datele într-un array NumPy
data_array = np.array(data, dtype=float)

# Verificăm datele
#print("Primele 5 linii ale datelor:")
#print(data_array[:5])

# Definire variabile
n_timp = data_array.shape[0]  # Numărul de măsurători în timp
n_senzori = data_array.shape[1]  # Numărul de senzori (fără frecvență)

# Extragem timpul (prima coloană) și înălțimile (coloanele 2-ultima)
time = data_array[M-1:N, 0]  # timpul pe axa Oy
height_data = data_array[M-1:N, 1:17]  # înălțimile în funcție de x
height_data_reverse= height_data[:, ::-1] 
height_data_total = np.hstack((height_data_reverse, height_data[:,1:16]))
coloana = 1
h = np.mean(height_data, axis = 0)
h_total=np.mean(height_data_total, axis = 0)
height_data_mean = height_data - h


for i in range(len(height_data_total)):
    for j in range(len(height_data_total[i])):
        height_data_total[i][j]=250-height_data_total[i][j]
         
sum = 0
Amplitudine = []
for row in height_data_mean:
    sum=0
    for element in row:
        sum=sum+element
    if(sum<=0):
            Amplitudine.append(sum)
    else:
            Amplitudine.append(0)
""""i=0
max = 0
maxime = []
perioada = 6000
while i<perioada:   
    if(Amplitudine[i] > max):
        max = Amplitudine[i]
    i+=1
print(max)"""
     


#print(Amplitudine)
# Verificăm dimensiunile datelor
#print("Dimensiunile datelor:")
#print(f"Dimensiune height_data: {height_data.shape}")

# Verificăm valorile din height_data pentru eventuale probleme
#print("Valorile minime și maxime din height_data:")
#print(f"Min: {height_data.min()}, Max: {height_data.max()}")

# Definirea pozițiilor pe axa Ox pentru fiecare senzor
x_positions = np.linspace(-2.37, 2.37, 31)  # 564 este lungimea totală pe axa Ox (poate fi ajustată)

# Creare grafic heatmap
plt.figure(figsize=(5, 10))
plt.imshow(height_data, aspect='auto', extent=[x_positions.min(), x_positions.max(), time.min(), time.max()], origin='lower', cmap='plasma', interpolation='nearest')
lev =np.linspace(np.min(height_data_total),np.max(height_data_total))
plt.contourf(x_positions, time, height_data_total)
plt.colorbar(label='Înălțimea apei (mm)')
plt.xlabel('Poziția senzorului (mm)')
plt.ylabel('Timp (s)')
plt.title('Heatmap al înălțimii apei în funcție de poziție și timp')
plt.ylim([7471.26, 7564.94])

#plt.plot(time,height_data_total[: ,15:16])
#plt.plot(time,height_data_mean[: ,1:18])
plt.show() 
    
