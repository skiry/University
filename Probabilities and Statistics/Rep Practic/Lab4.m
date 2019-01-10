% Lab4. 1)
rand % Uniformly distributed random numbers
randn % Normally distributed random numbers

% 2)
%Simulate Bern(p) r. var.
p = input('p (in(0,1)) = ');
N = input('simulations (big nr) = ');

for i = 1:N
    U = rand;
    X(i) = (U < p);
end

%Compare it to the Bern(p) graphically distribution
UX = unique(X); % the unique values
nX = hist(X, length(UX)); % number of each distinct value
reffr = nX / N;

%Graph
k = 0:20;
pk = binopdf(k, 1, p);

clf

plot(k, pk, '*', UX, reffr, 'ro')
legend('Bernoulli distribution', 'Simulation')

%Simulate Bino(n, p) r. var.
n = input('trials (max 10) = ');
p = input('p (in(0,1)) = ');
N = input('simulations (big nr) = ');

for i = 1:N
    U = rand(1, n);
    X(i) = sum(U < p);
end

%Compare it to the Bern(p) graphically distribution
UX = unique(X); % the unique values
nX = hist(X, length(UX)); % number of each distinct value
reffr = nX / N;

%Graph
k = 0:n;
pk = binopdf(k, n, p);

clf

plot(k, pk, '*', UX, reffr, 'ro')
legend('Bernoulli distribution', 'Simulation')

%Simulate Geo(p) r. var.
p = input('p (in(0,1)) = ');
N = input('simulations (big nr) = ');

for i = 1:N
    X(i) = 0;
    while rand >= p
        X(i) = X(i) + 1; %until we get the first correct ans, count the failures
    end
end

%Compare it to the Geo(p) graphically distribution
UX = unique(X);
nX = hist(X, length(UX)); % count the number of each unique value
reffr = nX / N;

%Graph
k = 0:20;
geopdfis = geopdf(k, p);

clf

plot(k, geopdfis, '*', UX, reffr, 'ro')
legend('Geometric Distribution', 'Simulation')

%Simulate N B(, p) r. var.
n = input('trials (max 10) = ');
p = input('p (in(0,1)) = ');
N = input('simulations (big nr) = ');

for i = 1:N
    X(i) = 0;
    for j = 1:n
        while rand >= p
            X(i) = X(i) + 1; %until we get the first correct ans, count the failures
        end
    end
end

%Compare it to the Pascal(n, p) graphically distribution
UX = unique(X);
nX = hist(X, length(UX)); % count the number of each unique value
reffr = nX / N;

%Graph
k = 0:n;
pascal = nbinpdf(k, n, p);

clf

plot(k, pascal, '*', UX, reffr, 'ro')
legend('Pascal Distribution', 'Simulation')