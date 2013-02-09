data Part = Part Int Int Int deriving Show

instance Eq Part where
    (Part a b c) == (Part a' b' c') = (a, b, c) == (a', b', c')

sqrtInt n = floor $ sqrt $ fromIntegral n

invert (Part n a b) = 
    let r = floor ((fromIntegral b) / ((sqrt $ fromIntegral n) - (fromIntegral a)))
        nb = (n - a * a) `div` b
    in  (r, Part n (r * nb - a) nb)

find :: Part -> [Part] -> [Part]
find x hx
    | (not $ null hx) && head hx == x = hx
    | otherwise = let (a, b) = invert x in find b (hx ++ [x])

main = do
  let n = 6
  print $ length $ filter (\x -> not $ even $ length x) $ map (\n -> find (Part n (sqrtInt n) 1) []) $ filter (\n -> sqrtInt n ^ 2 /= n) [1 .. 10000]
