w | grep ^e | awk '{split(,a,); for(i = 1; i<=length(a);i++) if(match(a[i],[aeiouAEIOU]) == 1) printf(%s%s,a[i],a[i]); else printf(%s,a[i]);

