function ex3(n)
clf; axis square; hold on;

T = @(x) ones(size(x));
for i=1:n    
    fplot(T, [-1, 3]);
    T = @(x) T(x) + ((x .^ i) / factorial(i));
end