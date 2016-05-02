#include<stdio.h>
int main()
{
    /*
     *__DATE__在源代码中插入当前编译日期
     __TIME__在源代码中插入当前编译时间
     * */
    printf("compile time:%s %s\n",__DATE__,__TIME__);
    return 0;
}
