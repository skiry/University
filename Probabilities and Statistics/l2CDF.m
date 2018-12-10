clf
n=input('no of trials=');
p=input('prob of succes=');

xcdf=0:0.01:n;
ycdf=binocdf(xcdf,n,p);

plot(xcdf,ycdf,'*-')
