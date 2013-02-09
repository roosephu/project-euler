
calc n arr dp
    | null arr = maximum dp
    | otherwise = 
        let (x, xs) = splitAt n arr
        in  calc (n + 1) xs [max (val (x - 1)) (val x) + (arr !! x) | x <- [0 .. n - 1]]
            where val x
                      | x < 0 = 0
                      | x >= length dp = 0
                      | otherwise = dp !! x

main = do
  input <- fmap (map read . words) getContents
  print $ calc 1 input []
