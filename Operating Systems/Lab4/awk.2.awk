BEGIN{
  n = 0
}
{
  split($5, a, " ");
  if(f[a[1]] == 0) m[++n] = a[1];
  f[a[1]]++;
}
END{
  for(i = 1; i <= n; i++)
  print m[i]  apare de  f[m[i]];
}

