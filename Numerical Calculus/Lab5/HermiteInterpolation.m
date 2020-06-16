function [Hx, der_Hx]=HermiteInterpolation(nodes, values, derivatives, x)
%x=the point(s) where we compute L
%H is the Hermite polynomial
table=DivDiffDoubleNodesTable(nodes, values, derivatives);
coefs=table(1, :);
double_nodes = repelem(nodes, 2);
Hx=x;
der_Hx=x;
for i=1:length(x)
Hx(i)=coefs(1);
P=1;
der_Hx(i)=0;
der_P=0;
    for k=2:length(coefs)
        der_P=der_P*(x(i)-double_nodes(k-1))+P;
        %(AB)' = A'B + AB' 
        P=P*(x(i)-double_nodes(k-1));
        Hx(i)=Hx(i)+coefs(k)*P;
        der_Hx(i)=der_Hx(i)+coefs(k)*der_P;
    end
end
end