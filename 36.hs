import Data.Char
bin x
    | x == 0 = ""
    | otherwise = (intToDigit $ x `mod` 2):bin (x `div` 2)

palin s = s == reverse s

main = do
  print $ sum $ filter (\x -> (palin $ show x) && (palin $ bin x)) [1 .. 10^6]