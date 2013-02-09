import Data.Numbers.Primes
import qualified Data.Set as S
import Data.Array

main = do
  let ps = takeWhile (<= 1000000) primes
      lps = length ps
      arrP = listArray (0, lps) $ scanl1 (+) (0 : ps)
      sx = S.fromList ps
      find n = filter (\i -> S.member ((arrP ! (i + n)) - (arrP ! i)) sx) [0 .. lps - n]
  -- print $ filter (\x -> not $ null $ find x) [550, 549 .. 1] 
  print $ find 543
  print $ ((arrP ! (3 + 543)) - (arrP ! 3))