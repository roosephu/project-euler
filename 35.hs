import Data.Numbers.Primes
import qualified Data.Set as S

rot n = read ((last s):init s) where s = show n

main =
    let x = S.fromList $ takeWhile (<= 1000000) primes
        chk n = f $ rot n
            where f t
                      | t == n = True
                      | not $ S.member t x = False
                      | otherwise = f $ rot t
    in  print $ length $ filter chk $ S.toAscList x
