import Data.Numbers.Primes
import Data.List
import Data.Array as A

factor n (x:xs)
    | n == 1 = []
    | x * x > n = [n]
    | n `mod` x == 0 = x : factor (n `div` x) (x:xs)
    | otherwise = factor n xs

countFac n = length $ nub $ factor n primes  

main = do
  let mx = 1000000
      x = A.listArray (1, mx) $ map countFac [1 .. mx]

  print $ head $ filter (\n -> all (\t -> x ! (t + n) == 4) [0 .. 3]) [1 .. ]
