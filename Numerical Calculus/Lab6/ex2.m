function ex2()
f=@(x) sin(x);
nodes=[0, pi/2, pi, 3*pi/2, 2*pi];
values=nodes;
for i=1:length(nodes)
    values(i)=f(nodes(i));
end
clf; hold on;

fplot(f, [0, 2*pi], 'r')
%function graph

sp=@(x) spline(nodes, values, x);
fplot(sp, [0, 2*pi], 'g')
%cubic natural spline graph

clamped_sp=@(x) spline(nodes, [1 values 1], x);
%am adaugat capetele nodurilor
fplot(clamped_sp, [0, 2*pi], 'm')
%clamped spline graph
end