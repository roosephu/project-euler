import Data.Numbers.Primes
-- primes lmt (x:xs)
--     | x > lmt = xs
--     | otherwise = x : (primes lmt $ filter (\t -> t `mod` x /= 0) xs)

main = do
  print $ primes !! 5