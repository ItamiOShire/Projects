set term png 

set out "Picard.png"

set xl "t"
set yl "u(t), v(t)"


set title "Metoda Picarda"
p "picard_u.txt" u 1:2 w l lw 4 t "u(t)","picard_v.txt" u 1:2 w l lw 4 t "v(t)"

set out "Newton.png"

set xl "t"
set yl "u(t), v(t)"

set title "Iteracja Newtona"
p "newton_u.txt" u 1:2 w l lw 4 t "u(t)","newton_v.txt" u 1:2 w l lw 4 t "v(t)"


set out "RK2.png"

set xl "t"
set yl "y(t)"

set title "Niejawna RK2"
p "rk2_u.txt" u 1:2 w l lw 4 t "u(t)","rk2_v.txt" u 1:2 w l lw 4 t "v(t)"


