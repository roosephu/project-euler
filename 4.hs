isPalin n = let s = show n in s == reverse s

main = do
  print $ maximum $ filter isPalin [x * y | x <- [100 .. 999], y <- [100 .. 999]]