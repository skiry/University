function x=Gauss_Seidel(A, b, iters)
    n=length(b);
    x_old=zeros(n, 1);
    for k=1:iters
        for i=1:n
            x(i)=(b(i)-A(i, 1:i-1) * x(1:i-1) - ...
                A(i, i+1:n) * x_old(i+1:n))/A(i, i);
        end
        x_old=x;
end