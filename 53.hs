main = 
  let fac = 1 : scanl1 (*) [1 .. 100]
  in  print $ length $ [1 | x <- [1 .. 100], y <- [0 .. x], (fac !! x) >= (fac !! y) * (fac !! (x - y)) * 10^6]