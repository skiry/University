%ex 2
%quad(f,a,b) - rezultatul integralei
function T=romberg(f,a,b,n)
T=NaN(n);
for i=1:n
   T(i, 1) = reptrap(f,a,b,2^(i-1));
   for j=2:i
       T(i, j) = (4^(1-j)*T(i-1, j-1) - T(i, j-1)) / (4^(1-j) - 1)
   end
end

end