for k, v of require 'prelude-ls'
  global[k] = v 

a = for i from 1 to 100
  for j from 1 to i
    if (i * j - 1) % (i + j) == 0 
#      console.log i, j
#      (i * j - 1) / (i + j) * i * j
      i + j
a
  |> flatten
  |> unique
#  |> (.length)
  |> sort
#  |> at 124
  |> console.log
