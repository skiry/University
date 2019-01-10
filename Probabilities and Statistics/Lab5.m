%Lab5, Part B, Probl 1
conflevel = input('conf. level(in(0,1))='); %1-alfa
alfa = 1-conflevel;

X = [7 7 4 5 9 9 ...
    4 12 8 1 8 7 ...
    3 13 2 1 17 7 ...
    12 5 6 2 1 13 ...
    14 10 2 4 9 11 ...
    3 5 12 6 10 7] ; %sample data

n = length(X);

xbar = mean(X);

%a) sigma known
sigma = 5;
q1 = norminv(1-alfa/2,0,1);
q2 = norminv(alfa/2,0,1); % q2 = -q1 sym N(0,1)
confint1 = xbar-(sigma/sqrt(n))*q1;
confint2 = xbar-(sigma/sqrt(n))*q2;
fprintf('C.I. for the population mean, niu, case sigma known is (%3.5f,%3.5f)\n',confint1,confint2);

%b) sigma unknown
s = std(X);
t1 = tinv(1-alfa/2,n-1);
t2 = tinv(alfa/2,n-1); % t2 = -t1 sym T(n-1)
confint1 = xbar-(s/sqrt(n))*t1;
confint2 = xbar-(s/sqrt(n))*t2;
fprintf('C.I. for the population mean, niu, case sigma unknown is (%3.5f,%3.5f)\n',confint1,confint2);

%c)
sampleVariance = var(X); %s patrat; the sample variance
q1 = chi2inv(1-alfa/2,n-1);
q2 = chi2inv(alfa/2,n-1); % NOT sym
confint1 = (n-1)*sampleVariance/q1;
confint2 = (n-1)*sampleVariance/q2;
fprintf('C.I. for the population variance, sigma squared, is (%3.5f,%3.5f)\n',confint1,confint2);
fprintf('C.I. for the population std. dev., sigma, is (%3.5f,%3.5f)\n',sqrt(confint1),sqrt(confint2));