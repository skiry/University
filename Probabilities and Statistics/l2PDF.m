%Binomial Distr.
clf
n=input('nr. of trials=');
p=input('prob. of success=');

xpdf=0:n;
ypdf=binopdf(xpdf,n,p);

plot(xpdf,ypdf,'*')
