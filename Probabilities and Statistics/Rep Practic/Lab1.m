%Lab 1. 1)
A = [1 0 -2; 2 1 3; 0 1 0];
B = [2 1 1; 1 0 -1; 1 1 0];
fprintf("A-B: %d\n", A-B);
fprintf("A*B: %d\n", A*B);
fprintf("A.*B: %d\n", A.*B);

%Lab 1. 2)
x = linspace(0,3);
f1 = x.^4/10;
f2 = x.*sin(x);
f3 = cos(x);

%All in one
plot(x, f1, '+', x, f2, '*', x, f3, 'ro'), grid on
title('Graph for X from (0, 3)')
legend('X^4/10', 'X*SIN(X)', 'COS(X)')

%Three subplots
ax1 = subplot(3,1,1);
plot(ax1,x,f1)
title(ax1,'X^4/10')

ax2 = subplot(3,1,2);
plot(ax2,x,f2)
title(ax2,'X*SIN(X)')

ax3 = subplot(3,1,3); 
plot(ax3,x,f3)
title(ax3,'COS(X)')