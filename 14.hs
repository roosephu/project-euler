step x
    | x == 1 = 1
    | even x = step (x `div` 2) + 1
    | otherwise = step (3 * x + 1) + 1

main = do
  print $ maximum $ map (\x -> (step x, x)) [1 .. 1000000]
