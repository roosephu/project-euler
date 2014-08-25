partialSum x = x * (x - 1) * (2 * x - 1) `div` 6

main = do
  let n = 10^15
      itf y = n `div` (n `div` y) + 1
  let ps = takeWhile (<= n) $ iterate itf 1
      ans = sum $ map (\ (a, b) -> (partialSum b - partialSum a) * (n `div` a)) ps
  print $ ans `mod` 10^9
