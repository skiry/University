function error=ex2()
clf; hold on;
nodes=[0 10 20 30 40 60 80 100];
values=[0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];

coefs_lsq2=polyfit(nodes, values, 2);
%lsq method for x, f(x) and degree 2

poly_lsq2=@(x) polyval(coefs_lsq2, x);
%fct that computes polynomial with unknowns x with coefs_lsq2

coefs_lsq6=polyfit(nodes, values, 6);
%Am incercat si cu 4, 5, 7, 8 dar cu 6 da cea mai mica eroare
%lsq method for x, f(x) and degree 6

poly_lsq6=@(x) polyval(coefs_lsq6, x);
%fct that computes polynomial with unknowns x with coefs_lsq6

coefs_lsq7=polyfit(nodes, values, 7);
%sunt 8 puncte, deci grad 7=>interpolation polynomial

poly_lsq7=@(x) polyval(coefs_lsq7, x);
%fct that computes polynomial with unknowns x with coefs_lsq6

fplot(poly_lsq2, [0, 100], 'g');
fplot(poly_lsq6, [0, 100], 'b','LineWidth',3);
fplot(poly_lsq7, [0, 100], 'y','LineWidth',1.5);
%error=norm(values-poly_lsq(nodes));
%distanta dintre valorile functiei si valorile polinomului
plot(nodes, values, 'r*');
deg2_45=poly_lsq2(45)
deg6_45=poly_lsq6(45)
error_deg2=abs(0.095848-deg2_45)
error_deg6=abs(0.095848-deg6_45)
end