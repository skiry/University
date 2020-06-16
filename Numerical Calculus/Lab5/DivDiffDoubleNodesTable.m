function table=DivDiffDoubleNodesTable(nodes, values, derivatives)
%nodes: x1, x2, ..., xn
%values: f(x1), f(x2), ..., f(xn)
%derivatives: f'(x1), f'(x2), ..., f'(xn)
%table: divided differences
n=2 * length(nodes);
table=NaN(n);
double_nodes = repelem(nodes, 2)';
table(:,1)=repelem(values, 2)';
table(1:2:end-1,2)=derivatives';
%initializam cu derivatele ca sa evitam /0
table(2:2:end-2,2)=diff(values)'./diff(nodes)';
%completam si astea ca sa incepem direct de la 3 forul
for j=3:n
    nt = double_nodes;
    table(1:n-j+1,j)=diff(table(1:n-j+2,j-1))./...
        (nt(j:n)-nt(1:n-j+1));
end
end