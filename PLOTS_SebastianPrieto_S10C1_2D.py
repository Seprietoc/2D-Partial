import matplotlib.pylab as plt
import numpy as np
import matplotlib.animation as animation

datos = np.genfromtxt("condini.dat", delimiter=',')
plt.imshow(datos)
plt.savefig("placa.png")
plt.close()