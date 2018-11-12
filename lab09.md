# “自顶向下，逐步求精”——编程方法介绍

## 思想介绍

### 自顶向下

自顶向下（top-down）的分析算法通过在最左推导中描述出各个步骤来分析记号串输入。将大型的数字电路设计分割成大小不一的小模块来实现特定的功能，最后通过由顶层模块调用子模块来实现整体功能，这就是Top-Down的设计思想。

这种方法将复杂的大问题分解为相对简单的小问题，找出每个问题的关键、重点所在，然后用精确的思维定性、定量地去描述问题。其核心本质是"分解"。

### 逐步求精

逐步求精即将现实问题经过几次抽象（细化）处理，最后到求解域中只是一些简单的算法描述和算法实现问题。即将系统功能按层次进行分解，每一层不断将功能细化，到最后一层都是功能单一、简单易实现的模块。求解过程可以划分为若干个阶段，在不同阶段采用不同的工具来描述问题。在每个阶段有不同的规则和标准，产生出不同阶段的文档资料。

![](http://ww1.sinaimg.cn/large/006V6dRsgy1fx4gyzalmdj30ou0hf0wu.jpg)

## 思想应用

接下来，我们将以洗衣机为例，描述其控制程序，来向大家介绍“自顶向下，逐步求精”思想的具体应用步骤。

![](http://ww1.sinaimg.cn/large/006V6dRsgy1fx4zcghkk0j30e00ht0wr.jpg)

首先，我们要了解洗衣机的大致工作流程：注水、浸洗、洗涤、漂洗、脱水、停机。

接下来，我们根据工作流程写出每一步骤的伪代码：

1、注水：

```c
input 注水体积；
water_in_switch(open);
if(水体积>=注水体积)
    water_in_switch(close);
```

2、浸洗：

```c
开始计时；
if(time>=规定时间) {
    进入洗涤步骤；
    计时结束；
}
```

3、洗涤：

```c
开始计时；
while(time为2的倍数) {
    电机运转；
    if(电机正在左转)
        motor_run(right);
    else moter_run(left);
    if(time>=规定时间)
        break;
}
电机停止运转；
water_out_switch(open);
if(水体积=0)
    water_out_switch(close);
```

4、漂洗：

```c
water_in_switch(open);
开始计时；
if(time>=规定时间) {
    water_out_switch(open);
    if(水体积=0)
        water_out_switch(close);
}   
```

5、脱水：

```c
电机运转；
开始计时；
while(time为2的倍数) {
    电机运转；
    if(电机正在左转)
        motor_run(right);
    else moter_run(left);
    if(time>=规定时间)
        break;
}
电机停止；
```

6、停机：

```c
if(电机停止&&水体积=0)
    发出警报；
halt;
```

之后，我们根据伪代码将各个步骤逐步细化，例如，可以提取一些函数模块，简化洗衣机运行程序，使程序变得利于人类理解和修护。

例如：注水程序

```c
int water_in(体积，结束时间)
water_in_switch(open);
time_counter();
while(time=结束时间)
    water_in_switch(close)；
```

#### 通过介绍，相信你已经初步了解了“自顶向下，逐步求精”的编程方法，现在，观察生活中何处能够应用到这种方法并付诸实践吧！