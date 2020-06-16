function Lx=LagrangeBary(nodes, values, x)
%nodes: x1, x2, ..., xn
%values: f(x1), f(x2), ..., f(xn)
A=CoeffBary(nodes); %vector of coefficients
%now apply the Barycentric Formula (7)
%course 2, page 9
Lx=x;
for j=1:length(x)
    x_pos_node=find(nodes==x(j));
    %return the position of the node equal to x(j)
    %ca sa nu returneze NaN
    if x_pos_node
        Lx(j)=values(x_pos_node);
    else
    Lx(j)=sum(A.*values./(x(j)-nodes))/...
        sum(A./(x(j)-nodes));
    end
end
%...treat the next line as it was on the same
end

function A=CoeffBary(nodes)
A=nodes %A=NaN(size(nodes)) or whatever; initialize it
for i=1:length(nodes)
    A(i)=1/prod(nodes(i)-nodes(nodes~=nodes(i)));
end
end

