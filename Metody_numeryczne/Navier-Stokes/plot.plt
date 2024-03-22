set term png enhanced size 600,300 

set size ratio -1
unset key
set o "v_4000.png"
set pm3d map
set palette
set cbrange [-2:5]
sp "v_4000.txt" with image 

unset key
set o "v_-1000.png"
set pm3d map
set palette
set cbrange [-6:1]
sp "v_-1000.txt" with image 

unset key
set o "v_-4000.png"
set pm3d map
set palette
set cbrange [-14:4]
sp "v_-4000.txt" with image 

unset key
set o "u_4000.png"
set pm3d map
set palette
set cbrange [-60:]
sp "u_4000.txt" with image 

unset key
set o "u_-1000.png"
set pm3d map
set palette
set cbrange [-2:16]
sp "u_-1000.txt" with image 

unset key
set o "u_-4000.png"
set pm3d map
set palette
set cbrange [-10:70]
sp "u_-4000.txt" with image 

