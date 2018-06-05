BEGIN{print start}
{
  for (i = 1; i <= NF; ++i)
    if (index($i,":") > 0) {
      split($i, a, ":"); 
      print a[2];
    }
}
END{
  print stop
}

