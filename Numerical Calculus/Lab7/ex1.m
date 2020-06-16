function error=ex1()
clf; hold on;
nodes=[1 2 3 4 5 6 7];
values=[13 15 20 14 15 13 10];

coefs_lsq=polyfit(nodes, values, 1);
%lsq method for x, f(x) and degree 1

poly_lsq=@(x) polyval(coefs_lsq, x);
%fct that computes polynomial with unknowns x with coefs_lsq

fplot(poly_lsq, [1, 8]);
error=norm(values-poly_lsq(nodes));
%distanta dintre valorile functiei si valorile polinomului
plot(nodes, values, 'r*');
la_ora_8=poly_lsq(8)
end