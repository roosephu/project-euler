import Math.NumberTheory.Primes
import Data.List
import Data.Ord

main = do
  let x = filter (>= 10^3) $ takeWhile (< 10^4) primes
      ys = groupBy (\ x y -> fst x == fst y) $ sort $ map (\ x -> (sort $ show x, x)) x
      arith x = f 0 0 0 $ sortBy (comparing snd) x
          where f a b c [] = c /= 0 && a - b == b - c
                f a b c ((r,x):xs) = f a b c xs || (f x b c xs && a == 0) || (f a x c xs && b == 0) || (f a b x xs && c == 0)
  print $ filter (\ x -> length x >= 3 && arith x) ys