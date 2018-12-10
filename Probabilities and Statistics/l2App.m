%c) P(X=0)
P1c=binopdf(0,3,1/2);

fprintf('Prob 1 in c)=%1.4f \n', P1c)

%c) P(x!=1) = 1-P(X=1)
P2c=1-binopdf(1,3,1/2);

fprintf('Prob 1 in c)=%1.4f \n', P2c)

%d) cdf F(x) = P(X<=x) 
% P(X<=2)
P1d=binocdf(2,3,1/2);

fprintf('Prob 1 in d)=%1.4f \n', P1d)

% P(X<2) = P(X<=1,1.5,1.9,1.999) but they are integers, so X<=1
P2d=binocdf(1,3,1/2);

fprintf('Prob 1 in d)=%1.4f \n', P2d)

%e) P(X>=1) = 1-P(X<1) = 1-P(X<=0)
P1e=1-binocdf(0,3,1/2);

fprintf('Prob 1 in d)=%1.4f \n', P1e)

%e) P(X>1) = 1-P(X<=1)
P1e=1-binocdf(1,3,1/2);

fprintf('Prob 1 in d)=%1.4f \n', P1e)