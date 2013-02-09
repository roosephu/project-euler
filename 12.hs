sigma :: Int -> Int
sigma x = 2 * (length $ filter (\t -> x `mod` t == 0) [1 .. m]) - (if m * m == x then 1 else 0)
    where m = round $ sqrt $ fromIntegral x

main = do
  print $ sigma 100
  print $ head $ filter (\v -> sigma v >= 500) [x * (x + 1) `div` 2 | x <- [1 .. ]]
