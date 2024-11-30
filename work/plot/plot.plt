# Gnuplot script to create a layout with 1 plot on the left and 4 plots on the right

set terminal pngcairo size 1200, 600
set nokey
set output "../figure/fig.png'

loadfile1 = sprintf("../data/spike.dat");
loadfile2 = sprintf("../data/timeseries.bin");

# Set the layout: 2 rows, 3 columns
#set multiplot layout 2, 3 margins 0.1, 0.9 spacing 0.05
set multiplot layout 2, 3

# First plot on the left (spanning two rows)
set lmargin at screen 0.1
set rmargin at screen 0.45
set tmargin at screen 0.9
set bmargin at screen 0.45
set xtics 0, 500, 1000
set ytics 0, 500, 4000
set noxtics
plot loadfile1 u 1:($2<3200  ? $2 : 1/0) w d ,\
     loadfile1  u 1:($2>=3200 ? $2 : 1/0) w d 
#plot "spike.dat" using 1:2:(($2 < 3200) ? "blue" : "red") title "Neuron Group" with points pointtype 7 lc variable

set tmargin at screen 0.4
set bmargin at screen 0.1
set xtics
set ytics 0, 5, 10
filter(x,y)=floor(x/y)*y
plot loadfile1 u (filter($1,1)):(1) smooth frequency w l

# Reset margins for the four plots on the right
set lmargin at screen 0.5
set rmargin at screen 0.9

set noxtics
set tmargin at screen 0.9 - (0)*0.2
set bmargin at screen 0.73 - (0)*0.2
set ytics 0, 2.5, 5
plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:6 w l \
   , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:7 w l

set tmargin at screen 0.9 - (1)*0.2
set bmargin at screen 0.73 - (1)*0.2
set ytics -60, 5, -50
plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:2 w l

set tmargin at screen 0.9 - (2)*0.2
set bmargin at screen 0.73 - (2)*0.2
set ytics -0.5, 0.5, 1.5
plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:4 w l \
   , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:5 w l

set tmargin at screen 0.9 - (3)*0.2
set bmargin at screen 0.73 - (3)*0.2
set xtics
set ytics -0.5, 0.5, 1.5
plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:3 w l

set xtics

unset multiplot
