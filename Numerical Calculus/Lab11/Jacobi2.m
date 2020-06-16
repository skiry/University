function [x, iters]=Jacobi2(A, b, err)
    M=diag(diag(A));
    N=M-A;
    C=M\b;
    T=M\N;
    
    x_old=zeros(size(b));
    iters=1;
    x=x_old;
    while true
        x=c + T * x_old;
        if norm(x-x_old,inf)*norm(T,inf)/(1-norm(T,inf))<=err
            return
        end
        x_old=x;
        iters=iters+1;        
    end
end