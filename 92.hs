import qualified Data.IntSet as S

nextNum :: Int -> Int
nextNum n
    | n == 0 = 0
    | otherwise = nextNum (n `div` 10) + (n `mod` 10) ^ 2

endNum n
    | n == 1 || n == 89 = n
    | otherwise = endNum $ nextNum n

main = do
  print $ endNum 145
  let tab  = S.fromList $ filter (\n -> endNum n == 89) [1 .. 1000]
  print $ length $ filter (\n -> S.member (nextNum n) tab) [1 .. 10000000]