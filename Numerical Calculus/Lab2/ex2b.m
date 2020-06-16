function ex2(n)
clf; axis square; hold on;

T0 = @(x) ones(1, length(x));
T1 = @(x) x;

for i=1:n
    fplot(T0, [-1, 1]);
    
    Tc = @(x) 2 * x .* T1(x) - T0(x);
    T0 = T1;
    T1 = Tc;
end