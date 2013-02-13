import Data.Array
import Data.Numbers.Primes
import qualified Data.Set as S

main = do
  let lmt = 1000000
      p = takeWhile (<= lmt) primes
      ps = S.fromList p
      phi = listArray (1, lmt) $ map fPhi [1 .. lmt]
      fPhi 1 = 1
      fPhi n
          | S.member n ps = n - 1
          | otherwise = 
              let x = head $ filter ((0 == ) . (n `mod`)) p
                  y = n `div` x
                  vx = phi ! y
              in  if y `mod` x == 0 then vx * x else vx * (x - 1)
  -- print $ phi
  print $ sum [phi ! x | x <- [1 .. lmt]] - 1
