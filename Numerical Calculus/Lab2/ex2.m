function ex2(n)
clf; axis square; hold on;

for i=1:n
Ti = @(x) cos(i * acos(x));
fplot(Ti, [-1, 1])
end