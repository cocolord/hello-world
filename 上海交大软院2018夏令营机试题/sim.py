import numpy as np
def sim(a,b):
    n = len(a)
    m = len(b)
    size = n * m
    w = 1
    s = np.ones((n)*(m)).reshape(int(n),int(m))
    for i in range(0,n):
        for j in range(0,m):
            if(i>m or j>n):
                s[i][j] = w
            elif a[i]==b[j]:
                s[i,j] = 3
            elif a[i]!=b[j]:
                s[i][j] = -1
    h = np.zeros((n+1)*(m+1)).reshape(int(n+1),int(m+1))
    for i in range(1,n+1):
        for j in range(1,m+1):
            h[i,j] = max(h[i-1,j-1]+s[i-1,j-1],h[i-1,j]-w,0,h[i][j-1]-w)
    h = h.transpose()
    print(h)
    return h
#测试
# a=['T', 'G', 'T', 'T', 'A', 'C', 'G', 'G']
# sim(['T','G','T','T','A','C','G','G'],['G','G' ,'T', 'T', 'G', 'A'])
# A=TGTTACGG, B=GGTTGA
# [[ 0.  0.  0.  0.  0.  0.  0.  0.  0.]
#  [ 0.  0.  3.  2.  1.  0.  0.  3.  2.]
#  [ 0.  0.  3.  2.  1.  0.  0.  3.  4.]
#  [ 0.  3.  2.  6.  5.  4.  3.  2.  4.]
#  [ 0.  3.  2.  5.  9.  8.  7.  6.  5.]
#  [ 0.  2.  6.  5.  8.  8.  7. 10.  9.]
#  [ 0.  1.  5.  5.  7. 11. 10.  9. 11.]]