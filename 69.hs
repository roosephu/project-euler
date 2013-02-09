import Data.Numbers.Primes

main = do
  print $ last $ takeWhile (<= 10^6) $ scanl1 (*) primes