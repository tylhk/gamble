#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>


int start_num = 100;//初始资金
int win_rate = 51;//胜率
int loop_num = 1000;

void gamble();
int payout(int wager);
void menu();
void image(int num);
void HideCursor();
void menu_jump(int num);
int scan_num(int num);
void mode_menu1();

int main()
{

    HideCursor();
    menu();

}

void gamble()
{
    srand((unsigned)time(NULL));
    int max_num = 0;//收入最大值
    int round = 1;//轮次
    for(; start_num>=0 && round < loop_num; round++)
    {
        //以10元为赌注
        if(payout(10)>0)
        {
            start_num += 10;
            if(max_num < start_num) max_num = start_num;
            printf("Round%d:本轮获胜,剩余资金%d\n",round,start_num);
        }
        else
        {
            start_num -= 10;
            printf("Round%d:本轮失败,剩余资金%d\n",round,start_num);
        }
    }
    printf("--------------------模拟结束--------------------\n");
    printf("最高记录为%d\n",max_num);
}

//每次赌博的收益
int payout(int wager)
{
    int a;
    a = rand() %100;
    //51%胜率的前提下 单倍输赢
    if(a >= 100-win_rate) return wager;
    else return -wager;
}

void menu()
{
    int menu_num = 1;
    int menu_total = 3;//总选项数
    int ch1=0;
    int ch2=0;

    while(1)
    {
        image(menu_num);
        ch1=getch();
        if(ch1 == 224)
        {
             ch2=getch();
             switch (ch2)
             {
                 case 72:
                     menu_num--;
                     if(menu_num == 0)menu_num=menu_total;
                     break;
                 case 80:
                     menu_num++;
                     if(menu_num >menu_total)menu_num=1;
                     break;
                 default:
                     printf("\n无效按键 \n");
                     Sleep(1000);
                     break;
             }
        }
        else
        {
            switch (ch1)
            {
                case 13:
                    menu_jump(menu_num);
                    break;

                case 119:
                case 87:
                    menu_num++;
                    if(menu_num >menu_total)menu_num=1;
                break;

                case 115:
                case 83:
                    menu_num--;
                    if(menu_num == 0)menu_num=menu_total;
                break;

                default:
                    printf("\n无效按键 \n");
                    Sleep(1000);
                break;
            }
        }

    }

}

void image(int num)
{
    //存放菜单的数组
    char *str_menu[] ={
        "------------------------------",
        "进入模拟1",
        "进入模拟2",
        "退出程序",
        "------------------------------\n使用方向键和回车键进行选择",
        };

    system("cls");
    for(int num_temp = 0;num_temp < sizeof(str_menu)/sizeof(str_menu[0]);num_temp++)
    {
        if (num_temp == num) printf("·");
        else if((num_temp!=0) && (num_temp!=sizeof(str_menu)/sizeof(str_menu[0])-1))printf("  ");
        printf("%s\n", str_menu[num_temp]);
    }
}

void HideCursor() // 隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void menu_jump(int num)
{
    switch(num)
    {
        case 1:
            system("cls");
            mode_menu1();
            return 0;
            break;
        case 2:
            system("cls");
            printf("Test mode");
            Sleep(1000);
            return 0;
            break;
        case 3:
            exit(0);
            break;
    }
}
//模式1
void mode_menu1()
{
    int ch1=0;
    while(1)
    {
        printf("------------------------------\n");
        printf("模拟名称：最小定投\n");
        printf("模拟规则：每次均以10元为赌注，获胜得20元，失败得0元。\n");
        printf("------------------------------\n");
        printf("1.初始资金:%d\n",start_num);
        printf("2.胜率:%d%%\n",win_rate);
        printf("3.循环次数:%d\n",win_rate);
        printf("------------------------------\n");
        printf("按下序号对应的数字键以修改数值\n按下Y键开始测试\n按下N键返回菜单\n");
        ch1=getch();
        //key N
        if(ch1 == 78 || ch1 == 110) return 0;
        //key Y
        else if(ch1 == 89 || ch1 == 121)
        {
            system("cls");
            printf("开始模拟\n");
            Sleep(1000);
            gamble();
            system("pause");
        }
        //key 1
        else if(ch1 == 49)
        {
            printf("------------------------------\n");
            printf("修改胜率为");
            win_rate = scan_num(win_rate);
        }
        else if(ch1 == 50)
        {
            printf("------------------------------\n");
            printf("修改循环次数为");
            loop_num = scan_num(loop_num);
        }
        Sleep(1000);
        system("cls");
    }
}
int scan_num(int num)
{
    int num_temp;
    if (scanf("%d", &num_temp) != 1) {
        printf("无效输入");
        while (getchar() != '\n');
        num_temp = num;
    }
    else printf("修改成功");
    return num_temp;
}
