function c=bisection(a, b, err, f)
    for i=1:100
        c = (a + b) / 2;
        if abs(f(c)) < err || abs(a - b) < err || abs(a - b) / abs(b) < err
            break
        end
        if f(a) * f(c) < 0
            b = c;
        else
            a = c;
        end
    end
end