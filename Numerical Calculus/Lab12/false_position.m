function [c, i]=false_position(a, b, err, f)
    for i=1:100
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
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