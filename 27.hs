import Data.Numbers.Primes
import Data.Set

main = do
  let ps = fromList $ takeWhile (< 100000) primes
      find a b = length $ takeWhile (\x -> member x ps) [n * n + a * n + b | n <- [0 .. ]]
  print $ maximum [(find a b, a, b) | a <- [-1000 .. 1000], b <- [-1000 .. 1000]]
