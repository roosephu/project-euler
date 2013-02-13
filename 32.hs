import Data.List
import Data.Char

isValid a b c = read a * read b == read c
slice xs i j = take (j - i + 1) $ drop i xs
chkStr s = f 0 0 0 s
    where f a b c []
            | a * b == c && c /= 0 = [c]
            | otherwise = []
          f a b c (x:xs)
            | a == 0 = f v b c xs
            | b == 0 = f (a * 10 + v) b c xs ++ f a v c xs
            | c == 0 = f a (b * 10 + v) c xs ++ f a b v xs
            | otherwise = f a b (c * 10 + v) xs
            where v = digitToInt x

main = do
  let xs = permutations ['1' .. '9']
      ans = (concat [chkStr x | x <- xs]) :: [Int]
      unique x = map head $ group $ sort x
  print $ sum $ unique ans
