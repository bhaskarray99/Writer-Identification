mvmat=read.table("Mean_var.txt")    #replace by file location containing mean intra-author var-cov matrix
vmmat=read.table("Var_mean.txt")    #replace by file location containing inter-author var-cov matrix
pc=eigen(solve(as.matrix(mvmat),as.matrix(vmmat)))$vectors[,1]
pc=Re(pc)
parr=sort(abs(pc))
p=0
index=0
for (i in 1:length(parr))
{
  p=p+parr[i]*parr[i]
  if (p>0)
  {
    index=i
    break
  }
}
sel=sort(sort.list(abs(pc))[index:length(pc)])
pc=pc[sel]
write.table(length(sel),"PC.txt",append = F,row.names = F,col.names = F)    #replace by file location containing principal component values
write.table(t(sel),"PC.txt",append = T,row.names = F,col.names = F)         #replace by file location containing principal component values
write.table(t(pc),"PC.txt",append = T,row.names = F,col.names = F)          #replace by file location containing principal component values
