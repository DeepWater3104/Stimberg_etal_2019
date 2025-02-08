set term png

set nokey
set output "../figure/output.png"
datfile = "../data/output.dat"
set multiplot layout 3,1
plot datfile u 1:2 w l, datfile u 1:3 w l
plot datfile u 1:4 w l, datfile u 1:5 w l
plot datfile u 1:6 w l, datfile u 1:7 w l
unset multiplot
