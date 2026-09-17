import pylab as pl
import numpy as np
x = np.array([20,70,120,170,220,270,320,370,420,470,520,570,620,670,720,770,820,870,920,970])
primerMetodo = np.array([0.001157,0.00136,0.008538,0.008094,0.024816,0.041086,0.030656,0.088817,0.091254,0.08148,0.079987,0.136517,0.109863,0.167402,0.148314,0.185625,0.192002,0.239321,0.308549,0.31382])
segundoMetodo = np.array([0.000831,0.001772,0.004506,0.008533,0.014748,0.021728,0.065488,0.060695,0.05337,0.10368,0.084575,0.120487,0.122971,0.152366,0.201495,0.178153,0.206271,0.299628,0.294004,0.323755])
pl.plot(x,primerMetodo, linewidth=1.0, linestyle="-",label="primerMetodo")
pl.plot(x,segundoMetodo, linewidth=1.0, linestyle="-",label="segundoMetodo")
pl.legend(loc='upper left')
pl.title('repeticiones=20 incremento=50')

pl.show()