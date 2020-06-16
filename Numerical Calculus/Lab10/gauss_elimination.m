function x=gauss_elimination(A, b)
    A=[A, b];
    n=length(b);
    for k=1:n-1
        [maxval, maxpos]=max(abs(A(k:n, k)));
        maxpos=maxpos + k - 1;
        if maxval > 0 && maxpos > k
            A([k, maxpos], k:end) = A([maxpos, k], k:end);
        elseif maxval == 0
            disp('No unique solution');
        end
        
        for i=k+1:n
            A(i,k:end)=A(i,k:end)-A(k,k:end)*A(i,k)/A(k,k);
        end
    end
    x=backward_substitution(A(:, 1:n), A(:, end));
end