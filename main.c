#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>


int start_num = 100;//��ʼ�ʽ�
int win_rate = 51;//ʤ��
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
    int max_num = 0;//�������ֵ
    int round = 1;//�ִ�
    for(; start_num>=0 && round < loop_num; round++)
    {
        //��10ԪΪ��ע
        if(payout(10)>0)
        {
            start_num += 10;
            if(max_num < start_num) max_num = start_num;
            printf("Round%d:���ֻ�ʤ,ʣ���ʽ�%d\n",round,start_num);
        }
        else
        {
            start_num -= 10;
            printf("Round%d:����ʧ��,ʣ���ʽ�%d\n",round,start_num);
        }
    }
    printf("--------------------ģ�����--------------------\n");
    printf("��߼�¼Ϊ%d\n",max_num);
}

//ÿ�ζĲ�������
int payout(int wager)
{
    int a;
    a = rand() %100;
    //51%ʤ�ʵ�ǰ���� ������Ӯ
    if(a >= 100-win_rate) return wager;
    else return -wager;
}

void menu()
{
    int menu_num = 1;
    int menu_total = 3;//��ѡ����
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
                     printf("\n��Ч���� \n");
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
                    printf("\n��Ч���� \n");
                    Sleep(1000);
                break;
            }
        }

    }

}

void image(int num)
{
    //��Ų˵�������
    char *str_menu[] ={
        "------------------------------",
        "����ģ��1",
        "����ģ��2",
        "�˳�����",
        "------------------------------\nʹ�÷�����ͻس�������ѡ��",
        };

    system("cls");
    for(int num_temp = 0;num_temp < sizeof(str_menu)/sizeof(str_menu[0]);num_temp++)
    {
        if (num_temp == num) printf("��");
        else if((num_temp!=0) && (num_temp!=sizeof(str_menu)/sizeof(str_menu[0])-1))printf("  ");
        printf("%s\n", str_menu[num_temp]);
    }
}

void HideCursor() // ���ع��
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
//ģʽ1
void mode_menu1()
{
    int ch1=0;
    while(1)
    {
        printf("------------------------------\n");
        printf("ģ�����ƣ���С��Ͷ\n");
        printf("ģ�����ÿ�ξ���10ԪΪ��ע����ʤ��20Ԫ��ʧ�ܵ�0Ԫ��\n");
        printf("------------------------------\n");
        printf("1.��ʼ�ʽ�:%d\n",start_num);
        printf("2.ʤ��:%d%%\n",win_rate);
        printf("3.ѭ������:%d\n",win_rate);
        printf("------------------------------\n");
        printf("������Ŷ�Ӧ�����ּ����޸���ֵ\n����Y����ʼ����\n����N�����ز˵�\n");
        ch1=getch();
        //key N
        if(ch1 == 78 || ch1 == 110) return 0;
        //key Y
        else if(ch1 == 89 || ch1 == 121)
        {
            system("cls");
            printf("��ʼģ��\n");
            Sleep(1000);
            gamble();
            system("pause");
        }
        //key 1
        else if(ch1 == 49)
        {
            printf("------------------------------\n");
            printf("�޸�ʤ��Ϊ");
            win_rate = scan_num(win_rate);
        }
        else if(ch1 == 50)
        {
            printf("------------------------------\n");
            printf("�޸�ѭ������Ϊ");
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
        printf("��Ч����");
        while (getchar() != '\n');
        num_temp = num;
    }
    else printf("�޸ĳɹ�");
    return num_temp;
}
