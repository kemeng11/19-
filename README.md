# 19-
19年华为软件精英挑战赛<br>
2019/03/16  21:00<br>
****最外面的CodeCraft-2019.cpp是在windows下编写调试的，与官方给的文件的区别在于去掉了主函数的参数，直接在主函数里指定文件路径<br>
19-文件夹里也有一个CodeCraft-2019.cpp，是准备往ubuntu上移植的，在ubuntu上文件的路径是作为主函数的参数传递进来的<br>
Codes文件夹里的代码没用<br>
2019/03/16  22:51<br>
****增加了函数注释，以及链表定义，每个链表节点代表一个路口，存储了该路口的序号与该路口上下左右相连的路的长度最大限速，以及上下左右节点的指针<br>
2019/03/16 23:10<br>
****写了很多空函数，目前的思路是用临接链表建立图，用DFS搜索两个节点之间的可行路径，然后用一个三维向量存储每辆车的所有可行路线，最后是选择每辆车的路线以及方案的评估，现在规划路线的时候不考虑调度时间的问题，直接用随机的方法进行选择，只要随机的次数足够多，总能选到一个相对不错的值，以及为每一辆车选择最短路径作为一个baseline<br>
2019/03/17 14:36<br>
****实现了CreatRoadMap的部分功能：将节点数据CrossData完全存储到ListNode里，但是ListNode之间并没有相互连接，每个ListNode的指针都存储到了vector CrossNodeVector里，由于Cross的命名是从1到N，所有对应到CCrossNodeVector第0个元素存储的是1个路口的 信息，以此类推，接下来需要将roadData存储到ListNode里，也就是每条路的长度，限速，以及节点之间的连接需要完成<br>
2019/03/17 16:37<br>
****完善了函数CreatRoatMap的后一部分，读取路的数据文件，完善节点的信息，同时将节点之间连接起来<br>
2019/03/17 23:33<br>
****删除了函数CreatRoatMap的一个多余参数MapHead，增加了查找两个路口之间所有可行路线的部分代码，但是在递归的细节上没写完<br>
2019/03/18 22:333<br>
****完成了寻找两个路口之间所有路径的函数，但是函数的参数特别多，暂时凑活用<br>目前找到的路径很可能或多一行空的，需要确认可行路径CurrentPathSum的大小后确认是否删除最后一行<br>
2019/3/19 20:59<br>
****完成了选择路径以及输出答案的函数，目前选择路径直接通过rand()选择，出发时间直接按照计划时间来<br>
2019/3/19 21:25<br>
****去掉了测试用的printf准备用linux测试<br>
2019/3/19  22:18<br>
****增加了一个函数，将节点到节点型的路线改成了路——路——路连接型的格式，将路线按照要求格式进行输出（题目要求）<br>
2019/3/22  20:54<br>
****将源代码复制了一份重新命名为CodeCraft2019-2准备进行路径规划优化算法<br>
