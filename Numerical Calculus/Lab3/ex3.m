function ex3()
f=@(x) (1+cos(pi*x))./(1+x)
clf
hold on
fplot(f, [0, 10])
hold on
a=linspace(0,10,21);
b=f(a);
% for i=1:21
% b(i)=f(a(i));
% end
Lx=@(x) LagrangeBary(a,b,x);
fplot(Lx, [0, 10])
plot(a,b,'r*')
end