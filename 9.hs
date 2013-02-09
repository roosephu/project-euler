x = 20
y = 5

main = do
  let c = x * x + y * y
      a = x * x - y * y
      b = 2 * x * y
  print $ a * b * c