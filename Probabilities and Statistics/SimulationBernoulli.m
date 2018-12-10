%Simulate Bern(p) r. var.

p = input('p (in(0,1)) = ');

%Generate 1 variable

U = rand;
X = (U<p);

%Generate a sample of variables

N = input('Nr. of simulations=');   %10,1e2
for i=1:N
    U = rand;
    X(i) = (U<p);

%Compare it to the Bern(p) distr.
UX = unique(X); %distinct values
nX = hist(X,length(UX)); %number of each distinct value
reffr = nX/N;
reffr