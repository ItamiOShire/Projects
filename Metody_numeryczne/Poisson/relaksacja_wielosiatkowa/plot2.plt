set term png

unset key
set out "v_1.png"
set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
set cbrange [-1:1]

set xl "x"
set yl "y"

plot "v_1.txt" matrix with image

set out "v_2.png"
plot "v_2.txt" matrix with image

set out "v_4.png"
plot "v_4.txt" matrix with image

set out "v_8.png"
plot "v_8.txt" matrix with image

set out "v_16.png"
plot "v_16.txt" matrix with image