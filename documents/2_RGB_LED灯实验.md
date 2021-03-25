# RGB LED灯实验

[toc]

## 1.实验目的

本实验主要在rv-star的板子上点亮RGB灯。

![RGB_LED](figures/2/RGB_LED.png)

## 2.环境搭建

实验下载操作可以按照第一节环境搭建来实现

[1_环境安装](./1_环境安装.md)

首先导入工程

![import](figures/2/import.png)

然后选择工程

![select](figures/2/select.png)

调试选择openocd

![openocd](figures/2/openocd.png)

最后，直接下载即可。

## 3.实验结果与代码分析

```
int main(void)
{
    int state = 0;
    user_gpio_init();

    while(1)
    {
        state++;
        delay_1ms(1000);
        rgb_toggle(state);
    }
}

```

main函数首先初始化了gpio，然后每一秒钟进行设置led的亮和灭。

其中`user_gpio_init`可以看一下：

```
//gpio init
void user_gpio_init(void)
{
    gd_rvstar_led_init(LED_G);
    gd_rvstar_led_init(LED_B);
    gd_rvstar_led_init(LED_R);
}
```

这里初始化了三个gpio，通过这三个GPIO来控制LED的亮与灭。

最后就是状态灯的变化函数：

```
void rgb_toggle(int state)
{
    int cur_state = state % 3;
    if(cur_state == 0)
    {
        LED_G_ON;
        LED_B_OFF;
        LED_R_OFF;
    }

    if(cur_state == 1)
    {
        LED_G_OFF;
        LED_B_ON;
        LED_R_OFF;
    }

    if(cur_state == 2)
    {
        LED_G_OFF;
        LED_B_OFF;
        LED_R_ON;
    }
}
```


简单的说，就是LED绿灯对应的是PA1，LED蓝灯对应PA3，LED红灯对应PA2。

查看原理图

![RGB1](figures/2/RGB1.png)

对应芯片的引脚

![RGB2](figures/2/RGB2.png)

不难看出，操作一个gpio的流程主要是三部分

1.设置GPIO时钟

2.设置初始化设置GPIO

3.操作对应的GPIO位

## 4.调用层次分析

main-->gd32vf103_rvstar-->gd32vf103_xx.c-->寄存器操作

所以如果需要自己实现板子的定义，只需要修改`gd32vf103_rvstar`中间层即可。



