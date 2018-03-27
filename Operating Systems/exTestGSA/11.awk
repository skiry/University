BEGIN{ 
s = 0;
n = 0;
}
{
   s+=$2;
   n+=1; 
}
END{
print s/n;
}
