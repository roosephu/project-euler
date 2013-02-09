factor 1 = []
factor n =
    let x = head $ filter (\x -> n `mod` x == 0) [2 .. ]
    in  x : (factor $ n `div` x)

main = do
  let n = 600851475143 
  print $ factor n