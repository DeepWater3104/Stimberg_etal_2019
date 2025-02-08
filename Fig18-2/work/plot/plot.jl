using Plots
using DelimitedFiles
using LaTeXStrings

trace = readdlm("../data/output.dat")

p1 = plot(trace[:, 1], trace[:, 2], label="", xaxis=false)
plot!(p1, trace[:, 1], trace[:, 3], ylabel=L"\Gamma_{A}", label="", xaxis=false)
p2 = plot(trace[:, 1], trace[:, 4], label="", xaxis=false)
plot!(p2, trace[:, 1], trace[:, 5], ylabel=L"I[\textrm{\mu M}]", label="", xaxis=false)
p3 = plot(trace[:, 1], trace[:, 6], label="", xaxis=false)
plot!(p3, trace[:, 1], trace[:, 7], ylabel=L"C[\textrm{\mu M}]", label="", xaxis=false)
p4 = plot(trace[:, 1], trace[:, 8], label="", xlabel="Time[s]")
plot!(p4, trace[:, 1], trace[:, 9], ylabel="h", label="")

plot(p1, p2, p3, p4, layout=(4,1))
savefig("../figure/output.png")
