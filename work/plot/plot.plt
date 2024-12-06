# Gnuplot script to create a layout with 1 plot on the left and 4 plots on the right

set terminal pngcairo size 1200, 600
set nokey

do for [G_EXC_index=0:10:1]{
  do for [G_INH_index=0:10:1]{
    savefile = sprintf("../figure/%02d_%02d_fig.png", G_EXC_index, G_INH_index);
    set output savefile
    loadfile1 = sprintf("../data/%02d_%02d_spike.dat", G_EXC_index, G_INH_index);
    loadfile2 = sprintf("../data/%02d_%02d_timeseries.bin", G_EXC_index, G_INH_index);
    
    G_EXC=.02000*G_EXC_index
    G_INH=.40000*G_INH_index
    title_string = sprintf("G_EXC:%f G_INH:%f", G_EXC, G_INH);

    set title title_string
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
    plot loadfile1 u 1:($2<3200  ? $2 : 1/0) w d ,
         loadfile1 u 1:($2>=3200 ? $2 : 1/0) w d 
    
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
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:6 w l        , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:7 w l
    
    set tmargin at screen 0.9 - (1)*0.2
    set bmargin at screen 0.73 - (1)*0.2
    set ytics -60, 5, -50
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:2 w l
    
    set tmargin at screen 0.9 - (2)*0.2
    set bmargin at screen 0.73 - (2)*0.2
    set ytics -0.5, 0.5, 1.5
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:4 w l        , loadfile2 binary format="%double%double%double%double%double%double%double" u 1:5 w l
    
    set tmargin at screen 0.9 - (3)*0.2
    set bmargin at screen 0.73 - (3)*0.2
    set xtics
    set ytics -0.5, 0.5, 1.5
    plot loadfile2 binary format="%double%double%double%double%double%double%double" u 1:3 w l
    
    set xtics
    
    unset multiplot
  }
}
