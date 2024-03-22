set term png 

set out "s(it).png"
set xl "it"
set yl "S"

set title "S(it)"
p "s_16.txt" u 1:2 w l lw 4 t "k = 16","s_8.txt" u 1:2 w l lw 4 t "k=8","s_4.txt" u 1:2 w l lw 4 t "k=4","s_2.txt" u 1:2 w l lw 4 t "k=2","s_1.txt" u 1:2 w l lw 4 t "k=1"


