set term png 

set out "Euler.png"

set xl "t"
set yl "y(t)"


set title "Metoda Eulera - rozwiazanie"
p "euler1.txt" u 1:2 w p pt 6 t "dt=0.01","euler2.txt" u 1:2 w p pt 6 t "dt=0.1","euler3.txt" u 1:2 w p pt 6 t "dt=1","euler_an.txt" u 1:2 w l lw 4 t "analityczne"

set out "Euler_blad_globalny.png"

set xl "t"
set yl "y_num(t)-y_dok(t)"

set title "Metoda Eulera - błąd globalny"
p "euler1_gb.txt" u 1:2 w l lw 4 t "dt=0.01","euler2_gb.txt" u 1:2 w l lw 4 t "dt=0.1","euler3_gb.txt" u 1:2 w l lw 4 t "dt=1"


set out "RK2.png"

set xl "t"
set yl "y(t)"

set title "Metoda RK2"
p "rk2_1.txt" u 1:2 w p pt 6 t "dt=0.01","rk2_2.txt" u 1:2 w p pt 6 t "dt=0.1","rk2_3.txt" u 1:2 w p pt 6 t "dt=1","rk2_an.txt" u 1:2 w l lw 4 t "analityczne"


set out "RK2_blad_globalny.png"

set xl "t"
set yl "y_num(t)-y_dok(t)"

set title "Metoda RK2 - błąd globalny"
p "rk2_1_gb.txt" u 1:2 w l lw 4 t "dt=0.01","rk2_2_gb.txt" u 1:2 w l lw 4 t "dt=0.1","rk2_3_gb.txt" u 1:2 w l lw 4 t "dt=1"


set out "RK4.png"

set xl "t"
set yl "y(t)"

set title "Metoda RK4"
p "rk4_1.txt" u 1:2 w p pt 6 t "dt=0.01","rk4_2.txt" u 1:2 w p pt 6 t "dt=0.1","rk4_3.txt" u 1:2 w p pt 6 t "dt=1","rk4_an.txt" u 1:2 w l lw 4 t "analityczne"


set out "RK4_blad_globalny.png"

set xl "t"
set yl "y_num(t)-y_dok(t)"

set title "Metoda RK4 - błąd globalny"
p "rk4_1_gb.txt" u 1:2 w l lw 4 t "dt=0.01","rk4_2_gb.txt" u 1:2 w l lw 4 t "dt=0.1","rk4_3_gb.txt" u 1:2 w l lw 4 t "dt=1"


set out "Q.png"

set xl "t"
set yl "Q(t)"

set title "Metoda RK4, Q(t)"
p "Q_1.txt" u 1:2 w l lw 4 t "0.5 omg_0","Q_2.txt" u 1:2 w l lw 4 t "0.8 omg_0","Q_3.txt" u 1:2 w l lw 4 t "1.0 omg_0","Q_4.txt" u 1:2 w l lw 4 t "1.2 omg_0"


set out "I.png"

set xl "t"
set yl "I(t)"

set title "Metoda RK4, I(t)"
p "I_1.txt" u 1:2 w l lw 4 t "0.5 omg_0","I_2.txt" u 1:2 w l lw 4 t "0.8 omg_0","I_3.txt" u 1:2 w l lw 4 t "1.0 omg_0","I_4.txt" u 1:2 w l lw 4 t "1.2 omg_0"