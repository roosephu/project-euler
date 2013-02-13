import Data.Vector((!))
import qualified Data.Vector as V
import Data.Ratio
import Math.NumberTheory.Primes

pow b e m
    | e == 0 = 1
    | even e = pow (b * b `mod` m) (e `div` 2) m
    | otherwise = pow b (e - 1) m * b `mod` m

getVal n mo = 
    let mul a b = a * b `mod` mo
        fac = V.fromList $ scanl mul 1 [1 .. mo - 1]
        ifac = V.fromList $ scanr mul (pow (fac ! (mo - 1)) (mo - 2) mo) [1 .. mo - 1]

        cb nv mv
            | mv == 0 = 1
            | n < m = 0
            | otherwise = fac ! n * ifac ! m * ifac ! (n - m) * cb (nv `div` mo) (mv `div` mo) `mod` mo
            where n = nv `mod` mo
                  m = mv `mod` mo

        getFac n
            | n >= mo = 0
            | otherwise = fac ! n

        len = (mo * mo - mo)
        dp = V.fromList $ map f [0 .. len - 1]
        f n = (sum $ [(dp ! i + mo - getFac i) * cb n i | i <- [0 .. n - 1]]) `mod` mo
    in dp ! (n `mod` len)

main = do
  let fac x = facT ! x
          where facT = V.fromList $ scanl (*) 1 [1 .. 1000]

      n = 10^9
      mo = 137
      globalMod = 77777777
      -- a = listArray (0, n) $ map f [0 .. n]
      --     where 
      --           -- f x = fac x + (sum $ [a ! (x - i) * fac x `div` fac i `div` fac (x - i) | i <- [1 .. x]])
      --           f x = (1 % 1) + (sum $ [a ! (x - i) / fac i | i <- [1 .. x]])
      -- b = V.fromList $ map f [0 .. n]
      --     where f x = (sum $ [(b ! i - fac i) * fac x `div` fac (x - i) `div` fac i | i <- [0 .. x - 1]]) `mod` mo
      prs = map (fromIntegral . fst) $ factorise 77777777

      rmd = map (getVal n) prs
      coef = map (\ x -> pow (globalMod `div` x `mod` x) (x - 2) x * (globalMod `div` x)) prs
 
  -- print $ and [xs ! i == xs ! (i + mo * mo - mo) | i <- [0 .. mo * mo]]
  print $ rmd
  print $ coef
  print $ (sum $ zipWith (\ a b -> toInteger a * toInteger b) rmd coef) `mod` (toInteger globalMod)
  -- print $ map (\ (a, b) -> b `mod` a) $ zip prs coef
  -- print $ -1 `mod` 7
