set term png

unset key
set out "v_1.png"
set pm3d map
set palette defined (0 "blue", 1 "white",2 "red")
set cbrange [-10:10]
set xrange[0:5]
set yrange[0:5]
set title "nx=ny=50, eps1=1, eps2=1"

set xl "x"
set yl "y"

splot "v_1.txt" u 2:1:3 with image

unset key
set out "v_2.png"
set palette defined (0 "blue", 1 "white",2 "red")
set cbrange [-10:10]
set xrange[0:10]
set yrange[0:10]

set xl "x"
set yl "y"

splot "v_2.txt" u 2:1:3 with image

unset key
set out "v_3.png"
set palette defined (0 "blue", 1 "white",2 "red")
set cbrange [-10:10]
set xrange[0:20]
set yrange[0:20]

set xl "x"
set yl "y"

splot "v_3.txt" u 2:1:3 with image

unset key
set out "vRho_1.png"
set palette defined (0 "blue", 1 "white",2 "red")
set cbrange [-0.8:0.8]
set xrange[0:10]
set yrange[0:10]
set title "nx=ny=100, eps1=1, eps2=1"

set xl "x"
set yl "y"

splot "vRho_1.txt" u 2:1:3 with image

set out "vRho_2.png"
set title "esp1=1, eps2=2
splot "vRho_2.txt" u 2:1:3 with image

set out "vRho_3.png"
set title "eps1=1, eps2=10"
splot "vRho_3.txt" u 2:1:3 with image




