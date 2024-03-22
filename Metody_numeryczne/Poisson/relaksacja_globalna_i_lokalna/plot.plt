set term png 

set out "s(it)_rg.png"

set logscale x 10
unset logscale y

set title "Relaksacja globalna"
p "sit1.txt" u 1:2 w l lw 4 t "omg = 0.6, 36887 it","sit2.txt" u 1:2 w l lw 4 t "omg = 0.6, 23090 it"

set out "s(it)_rl.png"

set logscale x 10
unset logscale y

set title "Relaksacja lokalna"
p "sitl1.txt" u 1:2 w l lw 4 t "omg = 1.0, 12194 it","sitl2.txt" u 1:2 w l lw 4 t "omg = 1.4, 5541 it","sitl3.txt" u 1:2 w l lw 4 t "omg = 1.8, 1544 it","sitl4.txt" u 1:2 w l lw 4 t "omg = 1.9, 738 it"

set out "err1_rg.png"
unset logscale x
set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
set xrange [0:14.5]
set yrange [0:9.5]
set cbrange [0:0.003]

plot "err1.txt" u 1:2:3 with image
