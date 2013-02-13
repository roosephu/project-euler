import Math.NumberTheory.Primes
import qualified Data.Set as S

main = do
  let lmt = 10^8
      x = takeWhile (<= lmt) primes
      t = S.fromList x
      lwBnd x = S.size . fst . S.split x
  print $ (sum [lwBnd (lmt `div` v + 1) t | v <- x] + lwBnd ((floor $ sqrt $ fromInteger lmt) + 1) t) `div` 2
