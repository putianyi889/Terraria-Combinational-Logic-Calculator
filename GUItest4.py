from tkinter import *
from tkinter.scrolledtext import ScrolledText
root = Tk()
root.geometry('600x600')

var1=StringVar()
var1.set("自动推断选项：")

Label1 = Label(root, textvariable=var1)
Label1.place(y=300, anchor=NW)

Label4 = Label(root, text="输入格式：")
Label4.place(y=120, anchor=NW)

Label5 = Label(root, text="逻辑门：")
Label5.place(y=20, anchor=NW)

var2=StringVar()
var3=StringVar()
var4=StringVar()


Label10086=Label(root, text="n,l:")
Label10086.place(x=120,y=10, anchor=NW)

Label2 = Label(root, textvariable=var2)
Label2.place(x=120,y=50, anchor=NW)

Label3 = Label(root, textvariable=var3)
Label3.place(x=120,y=300, anchor=NW)


t2 = ScrolledText(root,width=10,height=15)
t2.place(x=170,y=50)

t3 = ScrolledText(root,width=10,height=15)
t3.place(x=170,y=300)

t0 = ScrolledText(root,width=30,height=40)
t0.place(x=350,y=10)


kkk = Entry(root)
kkk.delete(0, END)
kkk.place(x=-100,y=-100,width=150)

v22=IntVar()
def setlb():
    if v22.get():
        var1.set("值域输入格式：")
        if v.get()==0:
            var3.set("sR:")
        if v.get()==-1:
            var3.set("ss:")
    else:
        var1.set("自动推断选项：")
        if v.get()==0:
            var2.set("s1:")
            var3.set("ss:")
        if v.get()==-1:
            var2.set("s1:")
            var3.set("s0:")
        if v.get()==1:
            var2.set("s0:")
            var3.set("ss:")



var4.set("s0")
v = IntVar()
rb1_1=Radiobutton(root,textvariable=var4,variable=v,value=0,command=setlb)
rb1_1.place(x=20,y=330, anchor=NW)
rb1_1.select()
rb1_2=Radiobutton(root, text="ss", variable=v, value=-1,command=setlb)
rb1_2.place(x=20,y=360, anchor=NW)
rb1_3=Radiobutton(root, text="s1", variable=v, value=1,command=setlb)
rb1_3.place(x=20,y=390, anchor=NW)
setlb()

def disb():
    var2.set("logic:")
    var3.set("ss:")
    var4.set("sR")
    rb1_3.place(x=-100,y=-100)
    kkk.delete(0, END)
    kkk.place(x=170,y=50)
    t2.place(x=-100,y=-100)
    rb1_1.select()
    setlb()

def ablb():
    var4.set("s0")
    kkk.place(x=-100,y=-100)
    t2.place(x=170,y=50)
    rb1_3.place(x=20,y=390)
    setlb()

def dab():
    if v22.get():
        disb()
    else:
        ablb()

v2 = IntVar()
tmprb=Radiobutton(root,text="二进制",variable=v2,value=2)
tmprb.place(x=20,y=150, anchor=NW)
tmprb.select()
Radiobutton(root, text="十进制", variable=v2, value=10).place(x=20,y=180, anchor=NW)
Radiobutton(root, text="十六进制", variable=v2, value=16).place(x=20,y=210, anchor=NW)
Radiobutton(root, text="单行", variable=v2, value=36).place(x=20,y=240, anchor=NW)


Checkbutton(root, text="表达式", variable=v22,command=dab).place(x=20,y=270, anchor=NW)

v3 = IntVar()
tmprb=Radiobutton(root,text="^",variable=v3,value=0)
tmprb.place(x=20,y=50, anchor=NW)
tmprb.select()
Radiobutton(root, text="&", variable=v3, value=1).place(x=20,y=80, anchor=NW)

v4=IntVar()
Checkbutton(root,text="准许输出取反",variable=v4).place(x=20,y=450, anchor=NW)

e = Entry(root)
e.delete(0, END)
e.insert(0, "4")
e.place(x=170,y=10,width=30)
f = Entry(root)
f.delete(0, END)
f.insert(0, "4")
f.place(x=215,y=10,width=30)



def work():
    n=int(e.get())
    m=int(f.get())
    l1=['~','a','b','c','d','e']
    s1=set()
    ss=set()
    s0=set()
    sR=set()
    anses=set()
    ans=[0 for i in range(m)]

    def xr(x):
        y=x^(x>>1)
        y=y^(y>>2)
        y=y^(y>>4)
        return y&1

    def rn(num):
        s=0
        if v3.get()==0:#xor
            for i in ans:
                t=num&i
                s+=(i>>n)^xr(t)
                if s>1:
                    return False
            if s==0:
                return False
            return True
        s=1
        for i in ans:
            t=num&i
            s&=(i>>n)^xr(t)
            if s==0:
                return False
        return True

    def chk():
        for i in s1:
            if not rn(i):
                return False
        for i in s0:
            if rn(i):
                return False   
        return True

    if not v22.get():
        if v2.get()==36:
            if v.get()==0:
                for i in t2.get('1.0',END):
                    try:
                        s1.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s1 and i not in ss:
                        s0.add(i)
            if v.get()==-1:
                for i in t2.get('1.0',END):
                    try:
                        s1.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END):
                    try:
                        s0.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s1 and i not in s0:
                        ss.add(i)
            if v.get()==1:
                for i in t2.get('1.0',END):
                    try:
                        s0.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s0 and i not in ss:
                        s1.add(i)
        else:
            if v.get()==0:
                for i in t2.get('1.0',END).split('\n'):
                    try:
                        s1.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END).split('\n'):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s1 and i not in ss:
                        s0.add(i)
            if v.get()==-1:
                for i in t2.get('1.0',END).split('\n'):
                    try:
                        s1.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END).split('\n'):
                    try:
                        s0.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s1 and i not in s0:
                        ss.add(i)
            if v.get()==1:
                for i in t2.get('1.0',END).split('\n'):
                    try:
                        s0.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in t3.get('1.0',END).split('\n'):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
                for i in range(2**n):
                    if i not in s0 and i not in ss:
                        s1.add(i)
    else:
        if v.get()==0:
            if v2.get()==36:
                for i in t3.get('1.0',END):
                    try:
                        sR.add(int(i,base=v2.get()))
                    except ValueError:
                            pass
            else:
                for i in t3.get('1.0',END).split('\n'):
                    try:
                        sR.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
        else:
            if v2.get()==36:
                for i in t3.get('1.0',END):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                            pass
            else:
                for i in t3.get('1.0',END).split('\n'):
                    try:
                        ss.add(int(i,base=v2.get()))
                    except ValueError:
                        pass
            for i in range(2**n):
                if i not in ss:
                    sR.add(i)

        lgc=[]
        s=kkk.get()
        flg0=False
        flg1=False
        flg2=0
        strt=0
        nd=-1
        for i in range(len(s)):
            if s[i]==')':
                nd=i
                break
            elif s[i]=='^':
                flg2=0
            elif s[i]=='&':
                flg2=1
            elif s[i]=='(':
                flg0=True
                strt=i
            elif not flg0 and s[i]=='~':
                flg1=not flg1
            
        lst=[i.replace(' ','') for i in s[strt+1:nd].split(',')]
        for i in lst:
            tmpnm=0
            for j in range(n+1):
                if l1[j] in i:
                    tmpnm+=1<<(n-j)
            lgc.append(tmpnm)
            
        def myrn(num):
            s=0
            if flg2==0:
                for i in lgc:
                    t=num&i
                    s+=(i>>n)^xr(t)
                    if s>1:
                        return False
                if s==0:
                    return False
                return True
            s=1
            for i in lgc:
                t=num&i
                s&=(i>>n)^xr(t)
                if s==0:
                    return False
            return True

        for i in sR:
            if flg1:
                if myrn(i):
                    s0.add(i)
                else:
                    s1.add(i)
            else:
                if myrn(i):
                    s1.add(i)
                else:
                    s0.add(i)
    

    def dfs(dgr):
        if dgr==m:
            for i in s1:
                if not rn(i):
                    return
            for i in s0:
                if rn(i):
                    return  
            anses.add(tuple(ans))
            return
        if dgr>0:
            for i in range(ans[dgr-1],2<<n):
                ans[dgr]=i
                dfs(dgr+1)
        else:
            for i in range(1,2<<n):
                ans[dgr]=i
                dfs(dgr+1)

    def atdfs(dgr):
        if dgr==m:
            for i in s0:
                if not rn(i):
                    return
            for i in s1:
                if rn(i):
                    return  
            anses.add(tuple(ans))
            return
        if dgr>0:
            for i in range(ans[dgr-1],2<<n):
                ans[dgr]=i
                atdfs(dgr+1)
        else:
            for i in range(1,2<<n):
                ans[dgr]=i
                atdfs(dgr+1)

    def prt(flag):
        oput=''
        for i in anses:
            if flag:
                pass
            else:
                oput+="~"
            if v3.get()==0:
                oput+="^("
            else:
                oput+="&("
            for j in range(m):
                for k in [5,4,3,2,1,0]:
                    if k> n:
                        continue
                    if (i[j]>>k)&1:
                        oput+=l1[n-k]
                if j!=m-1:
                    oput+=","
            oput+=")\n"
        return oput


    dfs(0)
    opts=prt(True)+'\n'
    anses=set()
    ans=[0 for i in range(m)]
    atdfs(0)
    if v4.get():
        opts+=prt(False)
    t0.delete('1.0',END)
    t0.insert(END,opts)
    #print('')
    #print(time.process_time()-a)




Button1=Button(root, text="求解", command=work)
Button1.place(x=210,y=560, anchor=CENTER)

root.mainloop()





