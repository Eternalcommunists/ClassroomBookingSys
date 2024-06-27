这是什么？失忆喷雾喷一下！
哈咯大家好~
这是一个简单的 C++项目，主要用于教师预约和管理员管理。
中间也出现过不少困难，本来打算利用 GITHUB 完成多人项目开发，但是时间紧任务重，最后也就做了一半吧。
遇到 clion 和 mysql 链接报错，可以在这里找到答案：
[clion 安装](https://blog.csdn.net/qq_44723773/article/details/104698675)
[连接 Mysql](https://blog.csdn.net/Szyangc/article/details/122096343)
[找不到 sql.h](https://blog.csdn.net/flaystar/article/details/105768129)
[my.ini 文件配置](https://blog.csdn.net/Burnup_110/article/details/115079157)
[找不到 my.ini 文件](https://blog.csdn.net/jiangyu1013/article/details/79792708)
[mysql 命令行闪退](https://blog.csdn.net/weixin_47678894/article/details/122737182)

## 教室管理系统序列图

```mermaid
sequenceDiagram


    User->>U: 启动程序
    System->>U: 显示菜单选项
    U->>System: 选择登录
    System->>U: 请求登录凭证

    U->>System: 提供登录凭证
    System->>U: 验证登录信息
    System->>SQL:提供Systemql查询语句进行匹配
    SQL->>SQL:TERMINAL检查校验
    SQL->>System:返回查询信息
    System->>U: 身份失败重新验证
    U->>System:重新提供信息
    System->>U: 身份验证成功允许登录
    alt 普通老师登录
        U->>System: 请求查看教室预约情况
        System->>SQL:发出调用语句查询
        SQL->>SQL:TERMINAL检查校验
        SQL->>System:返回信息
        System->>U: 返回教室预约情况
        U->>System: 请求查看个人预约表单
        System->>SQL:发出调用语句查询
        SQL->>SQL:TERMINAL检查校验
        SQL->>System:返回信息
        System->>U: 返回个人预约表单
        U->>System: 请求取消或修改预约
        System->>SQL:发出调用语句查询
        SQL->>SQL:TERMINAL检查校验
        SQL->>System:返回信息
        System->>U: 处理取消或修改预约请求
    end
    alt
    U->>System: 继续其他操作或退出系统
    System->>SQL:发出涉及调用sql库语句
    SQL->>SQL:TERMINAL检查校验
    SQL->>System:返回信息
    System->>U: 响应操作或退出系统
    end
```
管理员这部分长度不让放了，所以删去了，有兴趣自己画
# 教室管理系统流程图

## 流程图

```mermaid
flowchart TD
    Start[主函数]
    ShowMenu[Show Menu]
    Option1[1. 登录]
    Option2[2. 管理员登录]
    Option3[3. 注册]
    Option4[4. Exit]

    Start --> ShowMenu
    ShowMenu -->|1. Login| Option1
    ShowMenu -->|2. Admin Login| Option2
    ShowMenu -->|3. Register| Option3
    ShowMenu -->|4. Exit| Option4

    Option1 -->|输入账号密码| CheckCredentials
    CheckCredentials[数据库核对账号信息]
    CheckCredentials -->|合法| TeacherOptions[实现以下函数View Classroom Bookings, View Personal Bookings, Cancel/Modify Bookings]
    CheckCredentials -->|非法返回| ShowMenu

    Option2 -->|输入管理员账号密码| CheckAdminCredentials
    CheckAdminCredentials[进行核对Check Admin Credentials]
    CheckAdminCredentials -->|Valid| AdminOptions[实现以下函数View All Bookings, Add/Remove/Modify Bookings, Add/Remove/Modify Teachers]
    CheckAdminCredentials -->|Invalid| ShowMenu

    Option3 --> RegisterTeacher[Enter Teacher Details]
    RegisterTeacher --> RegisterSuccess[Register Teacher in System]
    RegisterSuccess --> ShowMenu

    Option4 --> ExitSystem[Exit System]
    ExitSystem --> End

    subgraph TeacherActions [Teacher Actions]
        TeacherOptions
    end

    subgraph AdminActions [Admin Actions]
        AdminOptions
    end

    subgraph End [End]
        ExitSystem
    end

    %% 添加个人标记
    subgraph watermark [© 2000 - Unauthorized copying is prohibited.]
    end
```
