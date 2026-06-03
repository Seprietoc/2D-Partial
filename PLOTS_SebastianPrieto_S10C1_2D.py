import matplotlib.pylab as plt
import numpy as np
import matplotlib.animation as animation

files = ["evotemp.dat", "evotempperiod.dat", "evotempabierta.dat"] 
plots = ["evotemp.png", "evotempperiod.png", "evotempabierta.png"]

for i in range(3):
    datos = np.genfromtxt(files[i], delimiter=',')
    fig, ax = plt.subplots(2, 2)
    ax[0,0].imshow(datos[:101,:])
    ax[0,1].imshow(datos[101:201,:])
    ax[1,0].imshow(datos[201:301,:])
    ax[1,1].imshow(datos[301:,:])
    plt.savefig(plots[i])
    plt.close()
