#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include <cassert>
using namespace std;

#define VNAME(value) (#value)


struct ListNode{
//用链表来存储节点和边，这一部是为了表示图，同时链表的路径搜索应该是比较简单的，用递归就可以做出来
    int crossNumber;//交叉路口的序号/id

    //四条相连路的id,顺时针方向，上右下左
    int UpRoadId;//上面路的id
    int RightRoadId;//右边路的id
    int DownRoadId;//下面路的id
    int LeftRoadId;//左边路的id

    //四条相连路的长度
    int UpRoadLength;
    int RightRoadLength;
    int DownRoadLength;
    int LeftRoadLength;

    //四条相连路的最快速度
    int UpRoadMaxSpeed;
    int RightRoadMaxSpeed;
    int DownRoadMaxSpeed;
    int LeftRoadMaxSpeed;

    //四个相连的节点
    ListNode* UpCross;
    ListNode* RightCross;
    ListNode* DownCross;
    ListNode* LeftCross;
};

void CreatRoadMap(vector<vector<int> > RoadData,vector<vector<int> > CrossData, ListNode* MapHead,vector<ListNode*  > *CrossNodeVector){
//建立一个图来表示交通路线
    //首先对每个路口建立一个节点
    //cross #(id,roadId,roadId,roadId,roadId) 路口是从1开始编号的
    //road #(id,length,speed,channel,from,to,isDuplex)
    int crossNum = CrossData.size();
    (*CrossNodeVector).resize(crossNum);
    for(int i=0;i<crossNum;i++){
        ListNode *TempNode = new ListNode();//新建一个节点
        //存储相连的路
        TempNode->crossNumber = CrossData[i][0];
        TempNode->UpRoadId = CrossData[i][1];
        TempNode->RightRoadId = CrossData[i][2];
        TempNode->DownRoadId = CrossData[i][3];
        TempNode->LeftRoadId = CrossData[i][4];
        //相邻的路口先置空
        TempNode->UpCross = NULL;
        TempNode->RightCross = NULL;
        TempNode->DownCross = NULL;
        TempNode->LeftCross = NULL;
        //将节点指针存储下来
       // printf("this is the %dth iter\n",i);
        (*CrossNodeVector)[CrossData[i][0]-1] = TempNode;//存放位置与路口id有关
        //指针初始化
        TempNode = NULL;
    }
    //接着借助路的信息把节点连接起来
}

void carPathSearch(int startCross,int endCross,vector<int> Path){
//搜索从一个路口到另一个路口的所有可行路径，这里只给出路径，时间的计算根据具体的车来确定，这样可以节省很大一部分时间

}


void carPlanSearch(vector<vector<int> > carData, vector<vector<vector<int> > >* AvaiablePath){
//搜索所有车的所有可行路径，用一个三维向量表示，第一维是carId，第二维是可行路线，第三维是路径。


}

void PlanSelectRandom(vector<vector<vector<int> > > AvaiablePath){
//选择最后的方案，直接随机
}

void PlanSelectIndivual(vector<vector<vector<int> > > AvaiablePath, vector<vector<int> >* PlanPath){
//选择最后的方案，不考虑整体，只考虑每辆车的最短时间
}

int PlanEvaluate(vector<vector<int> >* PlanPath){

}



bool txtDataRead(string carPath, vector<vector<int> > &carData, int cols){
// 参数carPath为文件的路径，一开始想对每一个car，path、cross，每一个txt都写一个函数读取，但是发现其实是同一个函数
//cols即为txt文件里的列数，对于car，cross列数为5，对于road列数为7
//car  #(id,from,to,speed,planTime)
//cross #(id,roadId,roadId,roadId,roadId)
//road #(id,length,speed,channel,from,to,isDuplex)

//目前代码总是会多读一行数据不知道为什么,
//在原先循坏停止条件为指针走到文件结束的情况下，会多读一行数据
//目前先计算行数，再读文件

    std::cout << "Path is " << carPath << std::endl;

    ifstream infile;
    infile.open(carPath.data());
    assert(infile.is_open());
    //遍历文件，确定行数
    string temp;
    int rows = 0;
    while(getline(infile,temp)){
        rows++;
    }
    carData.resize(rows-1);//减去第一行注释，剩下的就是数据的总行数
    printf("the rows is:%d\n",rows);
    infile.clear(std::ios::goodbit);
    infile.seekg(std::ios::beg);
    //
    string s;
    getline(infile,s);
    cout<<s<<endl;
    //从括号开始读取有用内容
    char c;
    int number;
    int i=0;
    while(i<rows-1){
        carData[i].resize(cols);
        infile>>c;//读取开头的括号
        for(int j=0;j<cols;j++){
            infile>>number;//读取一个数
            infile>>c;//读数后面的逗号或者右括号
            carData[i][j] = number;
        }
        i++;
    }
    printf("i = %d\n",i);
    infile.close();
    printf("(%d,%d)\n",carData.size(), carData[0].size());
}


void dataShow(vector<vector<int> > arr){
//用于查看二维向量内容
    if(arr.empty()){
        return;
    }
    int row = arr.size();
    printf("the content of %s is:\n",VNAME(arr));
    printf("(%d,%d)\n",row, arr[0].size());
    for(int i=0;i<row;i++){
        for(int j=0;j<arr[i].size();j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }
}




int main()
{
    //输入文件的路径，包括车辆，道路，交叉口信息，以及输出文件
    string carPath = "F:\\比赛\\19年华为软件精英挑战赛\\config\\car.txt";
    string roadPath = "F:\\比赛\\19年华为软件精英挑战赛\\config\\road.txt";
    string crossPath = "F:\\比赛\\19年华为软件精英挑战赛\\config\\cross.txt";
    string answerPath = "..\\config\\answer.txt";

    //建立二维数组存储汽车信息，路口信息，交叉口信息，以及规划的路线
    vector<vector<int> > carData;
    vector<vector<int> > roadData;
    vector<vector<int> > crossData;
    vector<vector<int> > plannedPath;
    //读取输入文件
    //(id,from,to,speed,planTime)
    bool carDataReadStatus = txtDataRead( carPath,  carData,5);
    //(id,roadId,roadId,roadId,roadId)
    bool roadDataReadStatus = txtDataRead( roadPath,  roadData,7);
    //(id,length,speed,channel,from,to,isDuplex)
    bool crossDataReadStatus = txtDataRead( crossPath, crossData,5);
    dataShow(crossData);
    //将数据转换成图和节点矩阵，双向图，有环图

    vector<int> isVisted;//记录节点是否被访问过，避免在遍历图的时候因为环构成死循环。
    vector<ListNode*> crossNodeVector;// 用于存储每一个节点的指针，用于寻找路径，也可能其实用不着，
                                    //根据路口的序号就可以判断是不是到达目的地
    ListNode* mapHead = NULL;
    CreatRoadMap(roadData,crossData, mapHead, &crossNodeVector);
    printf("the size of crossNodeVector is:%d\n",crossNodeVector.size());
    for(int i=0;i<crossNodeVector.size();i++){
        printf("%d\t",(crossNodeVector[i])->crossNumber);
    }
    //根据图寻找可行路径，Dijstra找最短路径。






	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	//将规划的路径进行输出
//    bool answerDataWriteStatus = answerDataWrite( answerPath, plannedPath);

	return 0;
}
