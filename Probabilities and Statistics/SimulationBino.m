%Simulate Bino(p) r. var.

n = input('nr. of trials (max 10) = ');
p = input('prob. of succes = ');

%Generate 1 variable

U = rand(n,1);
X = sum(U<p);

%Generate a sample of variables

N = input('Nr. of simulations (high nr) =');   %10,1e2
for i=1:N
    U = rand(n,1);
    X(i) = sum(U<p);
end

%Compare it to the Bino(n,p) graphically distr.
UX = unique(X); %distinct values
nX = hist(X,length(UX)); %number of each distinct value
reffr = nX/N;

%Graph
k = 0:n;
pk = binopdf(k,n,p);

clf

plot(k,pk,'*',UX,reffr,'ro')
legend('Binomial distribution', 'Simulation')