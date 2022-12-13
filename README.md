# An extremely simple ToDoList

制作MiniToDoList的初衷是想要一款**极简**的ToDoList。它不需要花里胡哨的功能，只需要记录事务和是否完成等基础信息，配合上一个简单的数据库功能即可。

注意：当前版本默认采用Redis后端，实现多端同步功能。本地数据库功能默认关闭。

<strong style="color:red;">使用：直接双击根目录下release-version文件夹内SimpleReminder.exe即可，依赖全部配好。</strong>

# 效果

## 基本功能

![demo](README.assets/demo.gif)

## 搜索字符串匹配功能

支持按时间或按事项内容子串搜索功能，基于Rabin Karp算法。

![search](README.assets/search.gif)

## 周期事项功能

可自行体验

# 简单架构

![structure](README.assets/structure.jpg)