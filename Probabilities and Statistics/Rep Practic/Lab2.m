%Lab 2. 2)
n = input('Enter the number of trials : ')
p = input('Enter the probability : ')

xpdf = 0:n
ypdf = binopdf(xpdf, n, p)

xcdf = 0:0.01:n
ycdf = binocdf(xcdf, n, p)

ax1 = subplot(2,1,1);
plot(ax1,xpdf, ypdf, '*')
title(ax1,'PDF')

ax2 = subplot(2,1,2);
plot(ax2,xcdf, ycdf, 'o')
title(ax2,'CDF')

%Lab 2. Application
%a)
pdfx = [ 0:3; binopdf(x, 3, 1/2) ]

%b)
cdfx = [ 0:3; binocdf(x, 3, 1/2) ]

%c) P( X = 0) & P(X != 1)
pdfxzero = binopdf(0, 3, 1/2)
pdfxdif1 = 1 - binopdf(1, 3, 1/2)

%d) P( X <= 2) & P( X < 2)
cdfxdoi = binocdf(2, 3, 1/2)
cdfxdois = binocdf(1, 3, 1/2)

%e) P( X >= 1) & P( X > 1)
cdfxunu = 1 - binocdf(1, 3, 1/2)
cdfxunus = 1 - binocdf(0, 3, 1/2)

%f) Simulate 3 coin tosses and compute X
Tosses = randi([0 1], 1, 3) %interval, lines, columns
X = sum(Tosses)