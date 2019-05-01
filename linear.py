import statistics

n  = int(input("Enter the no. of inputs: "))
x = []
y = []

for i in range(0,n):
	xi = int(input("Enter x%d: " % (i+1)))
	yi = int(input("Enter y%d: " % (i+1)))
	x.append(xi)
	y.append(yi)

xmean = statistics.mean(x)
ymean = statistics.mean(y)

xx = []
yy = []
xx2 = []
xy = []

for i in range(0,n):
	a = x[i] - xmean
	b = y[i] - ymean
	c = a ** 2
	d = a * b
	xx.append(a)
	yy.append(b)
	xx2.append(c)
	xy.append(d)

b1 = sum(xy)/sum(xx2)
b0 = ymean - b1 * xmean

xpred = int(input("Enter value of x for which y is to be predicted: "))

ypred = b0 + b1*xpred
print("Prediction is: %.2f" % (ypred))su
