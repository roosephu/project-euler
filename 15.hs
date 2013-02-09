factorial 0 = 1
factorial n = n * factorial (n - 1)

main = do
  print $ (factorial 4) `div` (factorial 2 ^ 2)