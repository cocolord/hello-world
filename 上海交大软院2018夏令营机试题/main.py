# encoding:utf-8
import csv
import re
import math
from tkinter import *
import tkinter.filedialog
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt

#Smith-Waterman algorithm
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

#gui
name = ''
root = Tk()
def xz():
    filename = tkinter.filedialog.askopenfilename()
    if filename.endswith('.csv'):
        lb.config(text="您选择的文件是：" + filename);
    else:
        lb.config(text="您需要重新选择一个csv文件");
lb = Label(root, text='')
lb.pack()
btn = Button(root, text="弹出选择文件对话框", command=xz)
btn.pack()

root.mainloop()
# plt.figure()
# x = range(0, 90, 15)
# y = range(75, 165, 15)
# plt.plot(x, y)
# plt.xlabel('X')
# plt.ylabel('Y')
# plt.show()

res = set()
if __name__ =='__main__':
    #read file
    with open('data.csv', 'r') as dt:
        f_csv = csv.reader(dt, delimiter=' ')
        time = 0
        r = 0
        similar = False
        rev_similar = False
        seq1 = []
        seq2 = []
        rev_seq2 = []
        copy_count = 0
        rev_copy_count = 0
        #直接二分法
        for line in f_csv:
            if(time<75 and time>=0):
                temp = ''
                for i in line:
                    temp = temp + i + ' '
                # seq1.append(line)
                seq1.append(temp)
                time = time + 1
            elif(time>=75 and time<150):
                temp = ''
                for j in line:
                    temp = temp + j + ' '
                # seq1.append(line)
                seq2.append(temp)
                time = time + 1
            if(time==150):
                time = time % 150
                mat = sim(seq1,seq2)
                # for i in range(len(seq2)):
                #     rev_seq2[i] = seq2[len(seq2)-1-i]
                rev_seq2 = seq2
                rev_mat = sim(seq1,rev_seq2)
                plt.figure()
                plt.title(str(r*150)+" "+str((r+1)*150))
                plt.plot(seq1,seq2,'o')
                plt.xlabel('X')
                plt.ylabel('Y')
                plt.show()
                plt.figure()
                plt.title(str(r*150)+" "+str((r+1)*150))
                plt.plot(seq1,rev_seq2,'o')
                plt.xlabel('rev_X')
                plt.ylabel('rev_Y')
                plt.show()
                susp1 = []
                susp2 = []
                rev_susp1 = []
                rev_susp2 = []
                for i in range(0,75):
                    for j in range(0,75):
                        if(mat[i,j]>=5):
                            susp1.append(i+r*150)
                            susp2.append(j+r*150)
                            res.add(j+r*150)
                            print("直接复制的部分出现在"+str(j+r*150))
                            similar = True
                            copy_count += 1
                        elif(rev_mat[i,j]>=5):
                            rev_susp1.append(i+r*150)
                            rev_susp2.append(j + r * 150)
                            # print("逆序复制的部分出现在" + str(j + r * 150))
                            rev_copy_count += 1
                            similar = True
                if(similar):
                    # print("第"+ str(susp1[0]) + '行和')
                    # print("第" + str(susp2[0]) +  '行相似')
                    similar = False
                    rev_copy_count += 1
                r = r + 1
                seq1.clear()
                seq2.clear()
                susp2.clear()
                susp1.clear()
                rev_susp2.clear()
                rev_susp1.clear()
        asd = Tk()  # 创建窗口对象的背景颜色
        info = ["选取的threshold为10", str(math.ceil(copy_count)),'直接抄袭的次数为', str(math.ceil(copy_count)),'逆序复制的次数为' ]
        info.append('主要的抄袭出现在450-600条记录上')
        new_info = Listbox(asd)
        for item in info:
            new_info.insert(0, item)
        new_info.pack()
        asd.mainloop()