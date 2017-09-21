

from math import pi
import mymodule


N = 8
for wk in range(N):
	print("sin(%iº) = %.4f" % (wk/N*360, mymodule.mysin(2*pi*wk/N)) )
	print("cos(%iº) = %.4f" % (wk/N*360, mymodule.mycos(2*pi*wk/N)) )
