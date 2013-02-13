import Data.Array

data Date = Date Int Int Int Int

days = listArray (1, 12) [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

nextYear (Date y m d s)
    | m == 13 = Date (y + 1) 1 d s
    | otherwise = Date y m d s

nextDay :: Date -> Date
nextDay (Date y m d s)
    | d == end = nextYear $ Date y (m + 1) 1 ns
    | otherwise = Date y m (d + 1) ns
    where end = if m == 2 then
                    if y `mod` 4 == 0 && (y `mod` 100 /= 0 || y `mod` 400 == 0) then 29 
                    else 28 
                else days ! m
          ns = (s + 1) `mod` 7

main = do
  print $ length $ filter (\ (Date y m d s) -> s == 6 && d == 1 && y >= 1901) $ takeWhile (\ (Date y m d s) -> y <= 2000) $ iterate nextDay $ Date 1900 1 1 0
