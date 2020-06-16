function Lx=NewtonInterpolation(nodes, values, x)
%x=the point(s) where we compute L
%L is the Lagrange polynomial
table=DivDiffTable(nodes, values);
Lx=x;
for i=1:length(x)
prods=[1 cumprod(x(i)-nodes(1:end-1))];
%1 pentru ca prima valoare nu se inmulteste cu niciun produs
%cumprod(..) = (x-x1)*(x-x2)*...(x-xn)
Lx(i)=table(1,:)*prods';
end
end