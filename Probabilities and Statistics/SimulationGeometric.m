%Simulate Geo(p) r. var.

p = input('prob. of succes = ');

%Generate 1 variable

X = 0;
while rand>=p
    X = X + 1; %count the nr of failures
end
%Generate a sample of variables

N = input('Nr. of simulations (high nr) =');   %10,1e2
for i=1:N
        X(i) = 0;
    while rand>=p
        X(i) = X(i) + 1; %count the nr of failures
    end
end

%Compare it to the Geo(n,p) graphically distr.
UX = unique(X); %distinct values
nX = hist(X,length(UX)); %number of each distinct value
reffr = nX/N;

%Graph
k = 0:20; %infinite set of values
pk = geopdf(k,p);

clf

plot(k,pk,'*',UX,reffr,'ro')
legend('Geometric distribution', 'Simulation')