function ex3()
clf; hold on;
f=@(x) exp(sin(x));
nodes=linspace(0, 6, 13);
values=nodes;
for i=1:length(nodes)
    values(i)=f(nodes(i));
end
fplot(f, [0, 6]);
plot(nodes, values, 'r*');
Lx=@(x) NewtonInterpolation(nodes, values, x);
fplot(Lx, [0, 6]);
end