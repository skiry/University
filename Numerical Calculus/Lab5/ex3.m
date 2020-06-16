function ex3()
f=@(x) sin(2*x);
clf; hold on;
fplot(f, [-5, 5]);
nodes=linspace(-5, 5, 15);
values=nodes;
der_f=@(x) 2*cos(2*x);
derivatives=nodes;
for i=1:length(nodes)
    values(i)=f(nodes(i))
    derivatives(i)=der_f(nodes(i));
end
Hx=@(x) HermiteInterpolation(nodes, values, derivatives, x)
fplot(Hx, [-5, 5]);
plot(nodes, values, 'r*')
end