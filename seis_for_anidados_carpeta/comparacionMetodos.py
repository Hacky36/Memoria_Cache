import pylab as pl
import numpy as np
x = np.array([50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240])
primerMetodoClasico = np.array([0.053284,0.095632,0.228539,0.262711,0.389281,0.510562,0.563238,0.893769,0.960043,1.36546,1.89162,1.9298,2.5129,3.00164,2.91885,3.68045,4.1077,5.43796,6.16074,6.83509])
segundoMetodoBloques = np.array([0.12733,0.188706,0.218171,0.556996,0.561352,0.682528,1.0655,1.35979,1.54534,1.93789,2.24095,3.31843,3.76477,4.27919,4.97823,5.42447,5.9252,7.42392,7.42961,8.83851])
pl.plot(x,primerMetodoClasico, linewidth=1.0, linestyle="-",label="primerMetodoClasico")
pl.plot(x,segundoMetodoBloques, linewidth=1.0, linestyle="-",label="segundoMetodoBloques")
pl.legend(loc='upper left')
pl.title('repeticiones=20 incremento=10')

pl.show()