function ex1()
f=@(x) sin(x);
nodes=[0, pi/2, pi, 3*pi/2, 2*pi];
values=nodes;
for i=1:length(nodes)
    values(i)=f(nodes(i));
end
clf; hold on;
value=pi/4;
%point x
plot(value, f(value),'r*')
%(x, f(x))
sp=spline(nodes, values, value);
plot(value, sp, 'b*')
%(x, natural spline)
clamped_sp=spline(nodes, [1 values 1], value);
%am adaugat capetele nodurilor
plot(value, clamped_sp, 'g*')
%(x, clamped spline)
end