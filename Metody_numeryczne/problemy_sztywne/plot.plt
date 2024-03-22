set term png 

set out "Rk2xt.png"

set xl "t"
set yl "x(t)"


set title "rk2"
p "rk2xt.txt" u 1:2 w l lw 4 t "TOL=10^-2","rk2xt1.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "rk2vt.png"

set xl "t"
set yl "v(t)"


set title "rk2"
p "rk2vt.txt" u 1:2 w l lw 4 t "TOL=10^-2","rk2vt2.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "rk2dt.png"

set xl "t"
set yl "d(t)"


set title "rk2"
p "rk2dt.txt" u 1:2 w l lw 4 t "TOL=10^-2","rk2dt3.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "rk2xv.png"

set xl "x"
set yl "v"


set title "rk2"
p "rk2v.txt" u 1:2 w l lw 4 t "TOL=10^-2","rk2v4.txt" u 1:2 w l lw 4 t "TOL=10^-5"


set out "trap2xt.png"

set xl "t"
set yl "x(t)"


set title "trapesoid"
p "trapxt.txt" u 1:2 w l lw 4 t "TOL=10^-2","trapxt1.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "trap2vt.png"

set xl "t"
set yl "v(t)"


set title "trapesoid"
p "trapvt.txt" u 1:2 w l lw 4 t "TOL=10^-2","trapvt2.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "trapdt.png"

set xl "t"
set yl "d(t)"


set title "trapesoid"
p "trapdt.txt" u 1:2 w l lw 4 t "TOL=10^-2","trapdt3.txt" u 1:2 w l lw 4 t "TOL=10^-5"

set out "trapxv.png"

set xl "x"
set yl "v"


set title "trapesoid"
p "trapv.txt" u 1:2 w l lw 4 t "TOL=10^-2","trapv4.txt" u 1:2 w l lw 4 t "TOL=10^-5"


