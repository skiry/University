%ex 1
function area=reprectangle(f,a,b,n)
  h=(b-a)/n; 
  %x=a+h/2:h:b-h/2;
  x = linspace(a + h/2, b - h/2, n);
  area=h*sum(f(x));
end