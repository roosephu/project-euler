main = do
  let f x = x * (x + 1) `div` 2
      lmt = 2 * 10^6
  print $ minimum [(abs (f x * f y - lmt), x * y) | x <- [1 .. 1000], y <- [1 .. 1000]]