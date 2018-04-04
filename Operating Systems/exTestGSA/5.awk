BEGIN{
}
{
split($3,a,"88");
  if( length(a) != 1 ){ #if there is no 88 in $3 then a == $3
      if( length(a[1]) + 2 == length($3) || length(a[1]) == length($3)) print $5;
          #if 88 is at the end, then len( $3 - '88' ) is len( $3 ) - 2, so the first condition in the if
          #if $3 == 88, from here the second condition
  }
}
END{
}
