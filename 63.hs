
main = do
  print $ sum $ takeWhile (> 0) $ [length $ filter (>= 10^(x - 1)) $ map (^x) [1 .. 9] | x <- [1 .. ]]