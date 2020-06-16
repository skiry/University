function error=least_squares(k)
clf; hold on;
axis equal;axis([0 3 0 5]);
xticks(0:0.5:3);
yticks(0:0.5:5);
[x, y]=ginput(1);
nodes=x; values=y;
i=1;
while ~isempty([x,y])
    plot(x,y,'*k', 'MarkerSize', 10);
    [x,y]=ginput(1);
    i=i+1;
    nodes=[nodes,x]; values=[values,y];
end
coefs_lsq=polyfit(nodes, values, k);
%lsq method for x, f(x) and degree k

poly_lsq=@(x) polyval(coefs_lsq, x);
%fct that computes polynomial with unknowns x with coefs_lsq

fplot(poly_lsq, [0, 3]);
error=norm(values-poly_lsq(nodes));
%distanta dintre valorile functiei si valorile polinomului
end