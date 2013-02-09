import Data.Array 
import Data.List

isSqr n = (floor $ sqrt $ fromIntegral n) ^ 2 == n

main = do
  let x = group $ sort $ [a + b + (round $ sqrt $ fromIntegral (a * a + b * b)) | a <- [1 .. 1000], b <- [1 .. 1000], isSqr (a * a + b * b)]
  print $ maximum $ filter (\(a, b) -> b <= 1000) $ map (\x -> (length x, head x)) x