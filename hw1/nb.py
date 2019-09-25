email=[]#标记邮件是否是垃圾邮件
num=0#邮件数量
jab=0#垃圾邮件数量
a={}#每个词在多少封邮件出现过
f=open("/Users/dongchenyu/Documents/VScode/labels.txt",'r',True)
while(True):
    line=f.readline()
    if not line:break
    num+=1
    temp=int(line)
    if(temp==1):
        jab+=1
    email.append(temp)
p=open("/Users/dongchenyu/Documents/VScode/train.txt",'r',True)
for i in range(0,3000):
    a[i]=0
while(True):
    line=p.readline()
    if not line:break
    list1=line.split()
    word=int(list1[1])
    a[word]+=1
choose=input()
i=int(choose)
if(i<0 or i>3000):
    print("the input is wrong")
    exit()
count=0
if(a[i]!=0):
    t=open("/Users/dongchenyu/Documents/VScode/train.txt",'r',True)
    while(True):
        line=t.readline()
        if not line:break
        list1=line.split()
        no=int(list1[0])
        word=int(list1[1])
        if(i==word and email[no-1]==1):
            count+=1
    t.close()
pna=jab/num
pb=a[i]/num
pbna=count/jab
pappear=count/jab
if(jab==0 or count ==0):
    print("0")
if(pb!=0 and jab!=0 and count!=0):
    pres1=(pna*pbna)/pb#贝叶斯公式
    pres2=pappear
    temp1=1/pres1
    temp2=1/pres2
    pres=2/(temp1+temp2)
    s=str(i)+" possible is "
    s+=str(pres)
    print(s)
p.close()
f.close()


