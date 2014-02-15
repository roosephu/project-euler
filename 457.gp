forprime(p = 1, 10^4, if(kronecker(13, p) == 1, r = sqrt(Mod(13, p)); print(p)));
        \\ 
       \\ y2 = p^2 - y1;
       \\ x1 = min(component((3 + y1) / 2, 2), component((3 - y1) / 2, 2));
       \\ x2 = min(component((3 + y2) / 2, 2), component((3 - y2) / 2, 2));
       \\ cur = min(x1, x2);
      \\  print(p)
      \\ ));