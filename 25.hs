fib = 1 : 1 : zipWith (+) fib (tail fib)

main = do
  let lmt = 10 ^ 999
  print $ take 10 fib
  print $ head $ filter (\(a, b) -> b >= lmt) $ zip [1 .. ] fib