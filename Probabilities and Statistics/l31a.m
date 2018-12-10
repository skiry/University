%Normal Distr.
mu=input('mu(in R)=');
sigmaa=input('sigma(>0)=');


%P(X<=0) this is a CDF F:R->R, F(x)=P(X<=x)
P1a=normcdf(0,mu,sigmaa);

fprintf('Prob 1 in a)=%1.4f \n', P1a)

%P(X>=0) = 1-P(X<0) ?
P2a=1-P1a;

%P(a<X<=b)=F(b)-F(a)
%b) P(-1<=X<=1) !!nu e nicio diferenta daca e inegalitatea stricta sau nu
P1b=normcdf(1,mu,sigmaa)-normcdf(-1,mu,sigmaa);

%P(X ??1 or X ? 1)
P2b=1-P1b;

%c) P(X < x?) = ?
alfa=input('alfa=');
xalpa=norminv(alfa,mu,sigmaa);
fprintf('Prob 1 in c)=%1.4f \n', P1a)

%d