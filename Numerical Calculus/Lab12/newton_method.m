function [x1, i]=newton_method(x0, err, f, fd)
    for i=1:100
        x1 = x0 - f(x0) / fd(x0);
        if abs(f(x1)) < err || abs(x0 - x1) < err || abs(x0 - x1) / abs(x1) < err
            break
        end
        x0 = x1;
    end
end