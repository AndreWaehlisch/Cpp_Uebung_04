set terminal png
set output 'newton1000.png'
set zrange [0.9:1.1]
set view 0,0,1
set size square
splot 'newton.txt' with dots
