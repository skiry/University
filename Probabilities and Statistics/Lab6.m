%Tests for 1 Pop

alfa = input('sign. level( in (0, 1) small = ');
% a)
m0 = input('test value = ');

%H0 : niu = m0 ( 9 ) also niu >= m0
%H1 : niu < m0 ( 9 ) left tailed test

X = [7 7 4 5 9 9 ...
    4 12 8 1 8 7 ...
    3 13 2 1 17 7 ...
    12 5 6 2 1 13 ...
    14 10 2 4 9 11 ...
    3 5 12 6 10 7] ; %sample data

sigma = 5; % case sigma known
[H, P, CI, ZVAL]= ztest(X, m0, sigma, alfa, 'left');
%H: 0(not rej), 1(rej) H0
%P: Pval
%CI: conf intervals
%ZVAL: the observed value of the TestStatistic, TS0=Z0

if H == 0
    fprintf('H0 is not rejected, i.e., the computer system meets the efficiency standard and does not need to be replaced\n');
else
    fprintf('H0 is rejected, i.e., the computer system does not meet the efficiency standard and has to be replaced\n');
end

fprintf('Observed value of test statistic is %3.5f\n', ZVAL);
fprintf('P value is %1.5f\n', P);

q1 = norminv(alfa, 0, 1);
fprintf('Rejection Region RR is (-inf, %3.5f)\n', q1);

%b)
m0 = input('test value = ');

%H0 : niu = m0 ( 5.5 ) also niu >= m0
%H1 : niu > m0 ( 5.5 ) right tailed test

X = [7 7 4 5 9 9 ...
    4 12 8 1 8 7 ...
    3 13 2 1 17 7 ...
    12 5 6 2 1 13 ...
    14 10 2 4 9 11 ...
    3 5 12 6 10 7] ; %sample data


[H, P, CI, STATS]= ttest(X, m0, alfa, 'right'); %vartest FOR VARIANCE
%H: 0(not rej), 1(rej) H0
%P: Pval
%CI: conf intervals
%STATS: 'tstat' -- TS : the value of the test statistic
       %'df'    -- T(df) : the degrees of freedom of the test
       %'sd'    -- the estimated population standard deviation.  For a
       %           paired test, this is the std. dev. of X-Y.

if H == 0
    fprintf('H0 is not rejected, i.e., the number of files stored does not exceed 5.5\n');
else
    fprintf('H0 is rejected, i.e., the number of files stored exceeds 5.5\n');
end

fprintf('Observed value of test statistic is %3.5f\n', STATS.tstat);
fprintf('P value is %1.5f\n', P);

q1 = tinv(1 - alfa, STATS.df);
fprintf('Rejection Region RR is (%3.5f, inf)\n', q1);