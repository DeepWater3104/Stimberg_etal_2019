using Plots
using DelimitedFiles

trace = readdlm("../data/output.dat")

p1 = plot(trace[:, 1], trace[:, 2])
plot!(p1, trace[:, 1], trace[:, 3])
p2 = plot(trace[:, 1], trace[:, 4])
plot!(p2, trace[:, 1], trace[:, 5])
p3 = plot(trace[:, 1], trace[:, 6])
plot!(p3, trace[:, 1], trace[:, 7])
p4 = plot(trace[:, 1], trace[:, 8])
plot!(p4, trace[:, 1], trace[:, 9])

plot(p1, p2, p3, p4, layout=(4,1))
