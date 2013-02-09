-- gcd a b
--     | a > b = gcd b a
--     | a == 0 = b
--     | otherwise = gcd a $ b `mod` a

main = do
  print $ foldl lcm 1 [1 .. 20]