% Lab 3. 1)
%Normal Distribution
miu = input( 'Miu from R = ');
sigm = input( 'Sigma greater than 0 = ');

% a) P( X <= 0 ) & P( X >= 0 )
v1 = normcdf(0, miu, sigm);
fprintf('Normal P( X <= 0 ) = %1.4f \n', v1)

v2 = 1 - v1 + normpdf(0,miu,sigm);
fprintf('Normal P( X >= 0 ) = %1.4f \n', v2)

% b) P( -1 <= X <= 1 ) & P( X <= -1 or X >= 1 ) == F(b) - F(a)
v1 = normcdf(1, miu, sigm) - normcdf(-1, miu, sigm);
fprintf('Normal P( -1 <= X <= 1 ) = %1.4f \n', v1)

v2 = 1 - v1;
fprintf('Normal P( X <= -1 or X >= 1 ) = %1.4f \n', v2)

%c) quantile of alpha : P( X < xalpha ) = alpha. rez = xalpha
myAlpha = input('Quantile of: alpha (0, 1) = ');
q = norminv(myAlpha, miu, sigm);
fprintf('Quantile of order %1.4f is %1.4f \n', myAlpha, q)

%d) quantile of beta : P( X > xbeta ) = beta. rez = xbeta
myBeta = input('Quantile of: beta (0, 1) = ');
q = norminv(1 - myBeta, miu, sigm);
fprintf('Quantile of order 1 - %1.4f is %1.4f \n', myBeta, q)

%Chi Squared Distribution
n = input( 'n from N = ');

% a) P( X <= 0 ) & P( X >= 0 )
v1 = chi2cdf(0, n);
fprintf('Chi Squared P( X <= 0 ) = %1.4f \n', v1)

v2 = 1 - v1;
fprintf('Chi Squared P( X >= 0 ) = %1.4f \n', v2)

% b) P( -1 <= X <= 1 ) & P( X <= -1 or X >= 1 ) == F(b) - F(a)
v1 = chi2cdf(1, n) - chi2cdf(-1, n);
fprintf('Chi Squared P( -1 <= X <= 1 ) = %1.4f \n', v1)

v2 = 1 - v1;
fprintf('Chi Squared P( X <= -1 or X >= 1 ) = %1.4f \n', v2)

%c) quantile of alpha : P( X < xalpha ) = alpha. rez = xalpha
myAlpha = input('Quantile of: alpha (0, 1) = ');
q = chi2inv(myAlpha, n);
fprintf('Quantile of order %1.4f is %1.4f \n', myAlpha, q)

%d) quantile of beta : P( X > xbeta ) = beta. rez = xbeta
myBeta = input('Quantile of: beta (0, 1) = ');
q = chi2inv(1 - myBeta, n);
fprintf('Quantile of order 1 - %1.4f is %1.4f \n', myBeta, q)

%2) Poisson approximation of the binomial distribution: 
%If n >= 30 and p <= 0.05, then Bino(n,p) =aprox= Poisson(lambda = np)
n = input('Number of trials greater than 30 = ');
p = input('P less than 0.05 = ')
x = 0:n
plot(x, binocdf(x,n,p), '*', x, poisscdf(x,n*p) , 'ro')
legend('Binomial', 'Poisson')