%Tests for 2 Populations

alfa = input('sign. level( in (0, 1) small = ');

%H0 : sigma1 = sigma 2
%H1 : sigma1 != sigma 2 two-tailed

X1 = [22.4 21.7 ...
      24.5 23.4 ...
      21.6 23.3 ...
      22.4 21.6 ...
      24.8 20.0 ] ; %sample data 1
  
X2 = [17.7 14.8  ...
      19.6 19.6  ...
      12.1 14.8  ...
      15.4 12.6  ...
      14.0 12.2  ] ; %sample data 2
%                  default:        0.05    0
[H, P, CI, STATS]= vartest2(X1, X2, alfa, 'both');
%H: 0(not rej), 1(rej) H0
%P: Pval
%CI: conf intervals
%STATS: 'fstat' -- TS : the value of the test statistic
       %'df1'    -- T(df1) : n1 - 1 the degrees of freedom of the test
       %'df2'    -- T(df2) : n2 - 1

if H == 0
    fprintf('H0 is not rejected, i.e., sigma 1 equals sigma 2\n');
else
    fprintf('H0 is rejected, i.e., sigma 1 is not equal to sigma 2\n');
end

fprintf('Observed value of test statistic is %3.5f\n', STATS.fstat);
fprintf('P value is %1.5f\n', P);

q1 = finv(alfa / 2, STATS.df1, STATS.df2);
q2 = finv(1 - alfa / 2, STATS.df1, STATS.df2);
fprintf('Rejection Region RR is (-inf, %3.5f) U (%3.5f, inf)\n', q1, q2);

%b)
alfa = input('sign. level( in (0, 1) small = ');

%H0 : niu 1 = niu 2
%H1 : niu 1 > niu 2 ( niu 1 - niu2 > 0 => right-tailed test )

X1 = [22.4 21.7 ...
      24.5 23.4 ...
      21.6 23.3 ...
      22.4 21.6 ...
      24.8 20.0 ] ; %sample data 1
  
X2 = [17.7 14.8  ...
      19.6 19.6  ...
      12.1 14.8  ...
      15.4 12.6  ...
      14.0 12.2  ] ; %sample data 2
%                  default:        0.05    0
[H, P, CI, STATS]= ttest2(X1, X2, alfa, 'right', 'equal'); %or unequal. Default is equal
%H: 0(not rej), 1(rej) H0
%P: Pval
%CI: conf intervals
%STATS: 'tstat' -- TS : the value of the test statistic
       %'df'    -- T(df) : n1 + n2 - 1 / n with the c and 1/n 
       %   the degrees of freedom of the test

if H == 0
    fprintf('H0 is not rejected, i.e., gas mileage does not seem to be higher when premium is used \n');
else
    fprintf('H0 is rejected, i.e., gas mileage seems to be higher when premium is used\n');
end

fprintf('Observed value of test statistic is %3.5f\n', STATS.tstat);
fprintf('P value is %e\n', P);

q1 = tinv(1 - alfa, STATS.df);
fprintf('Rejection Region RR is (%3.5f, inf)\n', q1);

