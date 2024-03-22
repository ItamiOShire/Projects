set term png enhanced size 600,300 

set size ratio -1

set o "psi-1000.png"
set contour
set cbr [-55:-50]
set cntrparam levels increment -55,1,-50
unset surface
set view map
unset key
sp "psi_-1000.txt" w l lt -1 palette  t ''