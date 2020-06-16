function table=DivDiffTable(nodes, values)
%nodes: x1, x2, ..., xn
%values: f(x1), f(x2), ..., f(xn)
%table: divided differences
n=length(nodes);
table=NaN(n);
table(:,1)=values';
for j=2:n
    nt = nodes';
    table(1:n-j+1,j)=diff(table(1:n-j+2,j-1))./...
        (nt(j:n)-nt(1:n-j+1));
end
end