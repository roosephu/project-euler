import Data.Numbers.Primes as N
import qualified Data.Set as S

main = 
    let tab = S.fromList $ take 10000 $ N.primes
        f n = all (\t -> not $ S.member t tab) $ takeWhile (> 0) [n - 2 * t * t | t <- [0 .. ]]
    in  print $ head $ filter (\n -> f n) [5, 7 .. ]