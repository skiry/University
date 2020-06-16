function [x2, i]=secant_method(x0, x1, err, f)
    for i=1:100
        x2 = (x0 * f(x1) - x1 * f(x0)) / (f(x1) - f(x0));
        if abs(f(x2)) < err || abs(x2 - x1) < err || abs(x2 - x1) / abs(x1) < err
            break
        end
        x0 = x1;
        x1 = x2;
    end
end