import Data.Numbers.Primes

dvs :: Int -> Int
dvs n = (sum $ map (\t -> t + (n `div` t)) $ filter (\t -> n `mod` t == 0) [1 .. m]) - (if n == m * m then m else 0) - n
    where m = floor $ sqrt $ fromIntegral n

main = do
  print $ sum $ filter (\n -> dvs n /= n && dvs (dvs n) == n) [1 .. 10000]