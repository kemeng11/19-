#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include<cassert>
#include<stdlib.h>
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

    //四条相连路的最快速度
    int UpRoadChannel;
    int RightRoadChannel;
    int DownRoadChannel;
    int LeftRoadChannel;

    //四个相连的节点
    ListNode* UpCross;
    ListNode* RightCross;
    ListNode* DownCross;
    ListNode* LeftCross;
};

void CreatRoadMap(vector<vector<int> > RoadData,vector<vector<int> > CrossData,vector<ListNode*  > *CrossNodeVector){
//建立一个图来表示交通路线
    //首先对每个路口建立一个节点
    //cross #(id,roadId,roadId,roadId,roadId) 路口是从1开始编号的
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

    //接着借助路的信息把节点连接起来,同时补充路的长度和限速，要在这里考虑单向双向的问题
    int roadNum = RoadData.size();
    //road #(id,length,speed,channel,from,to,isDuplex)
    for(int i=0;i<roadNum;i++){
        int RoadId = RoadData[i][0];
        int RoadStart = RoadData[i][4];
        int RoadEnd = RoadData[i][5];
        int isDuplex = RoadData[i][6];
        // 在起始点的路口里查找id相同的路
        ListNode* StartNode = (*CrossNodeVector)[RoadStart-1];//取去起始节点
        ListNode* EndNode = (*CrossNodeVector)[RoadEnd-1];//取去终点节点
        if(StartNode->UpRoadId == RoadId){
            StartNode->UpCross = EndNode;//节点
            StartNode->UpRoadLength = RoadData[i][1];//路长
            StartNode->UpRoadMaxSpeed = RoadData[i][2];//限速
            StartNode->UpRoadChannel = RoadData[i][3];//车道数
            if(isDuplex==1){//对于双向道而言上下关系，左右关系互为颠倒
                EndNode->DownCross = StartNode;
                EndNode->DownRoadLength = RoadData[i][1];
                EndNode->DownRoadMaxSpeed = RoadData[i][2];
                EndNode->DownRoadChannel = RoadData[i][3];
            }
        }else if(StartNode->RightRoadId == RoadId){
            StartNode->RightCross = EndNode;//节点
            StartNode->RightRoadLength = RoadData[i][1];//路长
            StartNode->RightRoadMaxSpeed = RoadData[i][2];//限速
            StartNode->RightRoadChannel = RoadData[i][3];//车道数
            if(isDuplex==1){//对于双向道而言上下关系，左右关系互为颠倒
                EndNode->LeftCross = StartNode;
                EndNode->LeftRoadLength = RoadData[i][1];
                EndNode->LeftRoadMaxSpeed = RoadData[i][2];
                EndNode->LeftRoadChannel = RoadData[i][3];
            }
        }else if(StartNode->DownRoadId == RoadId){
            StartNode->DownCross = EndNode;
            StartNode->DownRoadLength = RoadData[i][1];
            StartNode->DownRoadMaxSpeed = RoadData[i][2];
            StartNode->DownRoadChannel = RoadData[i][3];
            if(isDuplex==1){//对于双向道而言上下关系，左右关系互为颠倒
                EndNode->UpCross = StartNode;
                EndNode->UpRoadLength = RoadData[i][1];
                EndNode->UpRoadMaxSpeed = RoadData[i][2];
                EndNode->UpRoadChannel = RoadData[i][3];
            }
        }else{
            StartNode->LeftCross = EndNode;//节点
            StartNode->LeftRoadLength = RoadData[i][1];//路长
            StartNode->LeftRoadMaxSpeed = RoadData[i][2];//限速
            StartNode->LeftRoadChannel = RoadData[i][3];//车道数
            if(isDuplex==1){//对于双向道而言上下关系，左右关系互为颠倒
                EndNode->RightCross = StartNode;
                EndNode->RightRoadLength = RoadData[i][1];
                EndNode->RightRoadMaxSpeed = RoadData[i][2];
                EndNode->RightRoadChannel = RoadData[i][3];
            }
        }

    }
}

void carPathSearch(int startCross, int endCross,vector<ListNode*  > *CrossNodeVector,
                   vector<vector<int> > *Path, int *CurrentPathSum,vector<int > *isVisted, vector<int > *isReachable){//这里不需要改变链表，传形参,isVisted,CurrentPahtSum也只用形参
//注意传进来的isVisted必须为全零，也就是初始状态
//搜索从一个路口到另一个路口的所有可行路径，这里只给出路径，时间的计算根据具体的车来确定，这样可以节省很大一部分时间
//可行路径的数量不确定，同时在递归的过程中需要记录路线或者说是记录经过的节点
//为了避免死循环还需要记录节点是否访问过的状态数组，在单条路径中不能重复访问，访问完成后要重置状态，代码目前陷入了死循环
//！！！！！！！也可能是递归栈爆了。是找到新的路径之后新的vector被重置，push——back出栈
//需要提前给Path分配空间，也就是resize一下，不然直接调用(*Path)[0]会崩
//cross从1开始计数！！！
    int CurrentPathSumTemp = (*CurrentPathSum);
    (*Path)[(*CurrentPathSum)].push_back(startCross);
    (*isVisted)[startCross-1] = 1;//设置节点为已经访问

    //如果两个路口相连，找到一条路径,需要先判断节点存在在进行条件
    if(((*CrossNodeVector)[startCross-1]->UpCross&&(*CrossNodeVector)[startCross-1]->UpCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->RightCross&&(*CrossNodeVector)[startCross-1]->RightCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->DownCross&&(*CrossNodeVector)[startCross-1]->DownCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->LeftCross&&(*CrossNodeVector)[startCross-1]->LeftCross->crossNumber == endCross)){

        (*isVisted)[endCross-1] = 1;//终点也设为被访问过，避免后面判断麻烦
        (*CurrentPathSum)++;
        (*Path).resize((*CurrentPathSum)+1);//需要多分配一个来存储下一条路线，但是需要将之前的路径给复制下来
        for(int i=0;i<(*Path)[(*CurrentPathSum-1)].size();i++){//在新的路径序列里拷贝之前的节点路线
            (*Path)[*CurrentPathSum].push_back((*Path)[*CurrentPathSum-1][i]);
        }
        (*Path)[*CurrentPathSum-1].push_back(endCross);//在之前的路线中放入终点
       // printf("one path is found\n");

    }

    if(((*CrossNodeVector)[startCross-1]->UpCross!=NULL)&&
       (!(*isVisted)[(*CrossNodeVector)[startCross-1]->UpCross->crossNumber-1])&&(*isReachable)[startCross-1]){
        carPathSearch((*CrossNodeVector)[startCross-1]->UpCross->crossNumber, endCross, CrossNodeVector, Path, CurrentPathSum, isVisted,isReachable);
    }
    if(((*CrossNodeVector)[startCross-1]->RightCross!=NULL)&&
       (!(*isVisted)[(*CrossNodeVector)[startCross-1]->RightCross->crossNumber-1])&&(*isReachable)[startCross-1]){
        carPathSearch((*CrossNodeVector)[startCross-1]->RightCross->crossNumber, endCross, CrossNodeVector, Path, CurrentPathSum, isVisted,isReachable);
    }
    if(((*CrossNodeVector)[startCross-1]->DownCross!=NULL)&&
       (!(*isVisted)[(*CrossNodeVector)[startCross-1]->DownCross->crossNumber-1])&&(*isReachable)[startCross-1]){
        carPathSearch((*CrossNodeVector)[startCross-1]->DownCross->crossNumber, endCross, CrossNodeVector, Path, CurrentPathSum, isVisted,isReachable);
    }
    if(((*CrossNodeVector)[startCross-1]->LeftCross!=NULL)&&
       (!(*isVisted)[(*CrossNodeVector)[startCross-1]->LeftCross->crossNumber-1])&&(*isReachable)[startCross-1]){
        carPathSearch((*CrossNodeVector)[startCross-1]->LeftCross->crossNumber, endCross, CrossNodeVector, Path, CurrentPathSum, isVisted,isReachable);
    }
    //完成当前节点的搜索后,如果可行路径的数量没变那么这两个节点之间是不可行的
    if((*CurrentPathSum)==CurrentPathSumTemp){//如果没找到新的路径
        (*isReachable)[startCross-1]=0;
       // printf("this cross cannot come to end %d\n",startCross);
    }
    //如果找到一条路径了就不要再乱pop了！！！！！！！！！！，没找到路径的情况下才需要pop，但是需要继承之前的路径信息
    (*Path)[(*CurrentPathSum)].pop_back();
    (*isVisted)[startCross-1] = 0;
    return;
}

void carPlanSearch(vector<vector<int> > carData, vector<ListNode*  > crossNodeVector, vector<vector<vector<int> > >* AvaiablePath){
//搜索所有车的所有可行路径，用一个三维向量表示，第一维是carId，第二维是可行路线，第三维是路径。
//考虑到实际车的数量可能会比节点数量的平方n^2更多，很有可能存在重复的路线，那么就存下来每次计算过的节点对之间的可行路径
//下一次出现重复路线就直接调用，现在还没有实现所以运算效率堪忧
//(id,from,to,speed,planTime)
    int carNum = carData.size();
    (*AvaiablePath).resize(carNum);
    int SatrtCross = 0;
    int EndCross = 0;

    vector<int> isVisted;//记录节点是否被访问过，避免在遍历图的时候因为环构成死循环。
    vector<int> isReachable;
    isVisted.resize(crossNodeVector.size());
    isReachable.resize(crossNodeVector.size());
    for(int i=0;i<isVisted.size();i++){
        isVisted[i] = 0;
        isReachable[i] = 1;
    }
    vector<vector<int > > Path;
    Path.resize(1);
    int CurrentPathSum = 0;

    for(int i=0;i<carNum;i++){
        SatrtCross = carData[i][1];
        EndCross = carData[i][2];
        carPathSearch(SatrtCross, EndCross, &crossNodeVector, &Path, &CurrentPathSum, &isVisted, &isReachable);
        //需要把Path里多余的一行给踢掉，或者用CurrentPathSum来控制选择那些元素，是不是pop_back就好了
       // printf("the CurrentPathSum of %dth inter is :%d\n",i,CurrentPathSum);
        if(Path.size()>CurrentPathSum){
            Path.pop_back();
        }
        (*AvaiablePath)[i] = Path;//这样赋值会不会出问题
        //用完之后需要把Path给删掉，CurrentPathSum，isVisted，isReachable都需要初始化
        Path.clear();//clear不够，需要给他resize
        Path.resize(1);
        CurrentPathSum = 0;
        for(int ii=0;ii<isVisted.size();ii++){
            isVisted[ii] = 0;
            isReachable[ii] = 1;
        }
    }

}

void crossPath2RoadPath(vector<ListNode*  > crossNodeVector, vector<int > CrossPath,vector<int> *RoadPath){
//将节点形式的路线转换为道路ID形式的路线
    int RoadId = 0;
    int CrossId = 0;
    for(int i=0;i<CrossPath.size()-1;i++){
        CrossId = CrossPath[i];
        if((crossNodeVector[CrossId-1]->UpCross)&&(crossNodeVector[CrossId-1]->UpCross->crossNumber == CrossPath[i+1])){
            RoadId = crossNodeVector[CrossId-1]->UpRoadId;
        }else if((crossNodeVector[CrossId-1]->RightCross)&&(crossNodeVector[CrossId-1]->RightCross->crossNumber == CrossPath[i+1])){
            RoadId = crossNodeVector[CrossId-1]->RightRoadId;
        }else if((crossNodeVector[CrossId-1]->DownCross)&&(crossNodeVector[CrossId-1]->DownCross->crossNumber == CrossPath[i+1])){
            RoadId = crossNodeVector[CrossId-1]->DownRoadId;
        }else{
            RoadId = crossNodeVector[CrossId-1]->LeftRoadId;
        }
        (*RoadPath).push_back(RoadId);
    }
}


void PlanSelectRandom(vector<ListNode*  > crossNodeVector, vector<vector<int> > carData,
                      vector<vector<vector<int> > > AvaiablePath,vector<vector<int > > *PlanPath){
//选择最后的方案，直接随机
    int carNum = carData.size();
    (*PlanPath).resize(carNum);
    int carId = 0;
    int PlanTime = 0;
    int choose = 0;
    vector<int> CrossPath;
    vector<int> RoadPath;
    for(int i=0;i<carNum;i++){
        carId =carData[i][0];
        PlanTime = carData[i][4];
        (*PlanPath)[i].push_back(carId);
        (*PlanPath)[i].push_back(PlanTime+3*(i/8));
        //开始随机选路径
        choose = rand()%AvaiablePath[i].size();
        //CrossPath.insert(CrossPath.begin(),AvaiablePath[i][choose].begin(),AvaiablePath[i][choose].end());
        CrossPath = AvaiablePath[i][choose];
        //将路径由节点形式转换为边的形式
        crossPath2RoadPath(crossNodeVector, CrossPath, &RoadPath);
        (*PlanPath)[i].insert((*PlanPath)[i].end(), RoadPath.begin(), RoadPath.end());
        vector<int>().swap(RoadPath);
    }
}

void PlanSelectIndivual(vector<vector<int> > carData, vector<vector<vector<int> > > AvaiablePath, vector<vector<int> >* PlanPath){
//选择最后的方案，不考虑整体，只考虑每辆车的最短时间
}
//将路线转换为期待的输出格式
int PlanEvaluate(vector<vector<int> >* PlanPath){
    return 0;
}



bool txtDataRead(string carPath, vector<vector<int> > &carData, int cols){
// 参数carPath为文件的路径，一开始想对每一个car，path、cross，每一个txt都写一个函数读取，但是发现其实是同一个函数
//cols即为txt文件里的列数，对于car，cross列数为5，对于road列数为7
//car  #(id,from,to,speed,planTime)
//cross #(id,roadId,roadId,roadId,roadId)
//road #(id,length,speed,channel,from,to,isDuplex)

//在原先循坏停止条件为指针走到文件结束的情况下，会多读一行数据 目前先计算行数，再读文件

    //std::cout << "Path is " << carPath << std::endl;

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
   // printf("the rows is:%d\n",rows);
    infile.clear(std::ios::goodbit);
    infile.seekg(std::ios::beg);
    //
    string s;
    getline(infile,s);
    //cout<<s<<endl;
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
   // printf("i = %d\n",i);
    infile.close();
    //printf("(%d,%d)\n",carData.size(), carData[0].size());
}

bool txtDataWrite(string answerPath,vector<vector<int > > PlanPath){
    int carNum = PlanPath.size();
    ofstream ofile;
    ofile.open(answerPath.data(),ios::out);
    ofile<<"#carId, starttime, RoadId...\n";
    for(int i=0;i<carNum;i++){
        ofile<<"(";
        for(int j=0;j<PlanPath[i].size();j++){
            ofile<<PlanPath[i][j];
            if(j!=PlanPath[i].size()-1){
                ofile<<", ";
            }
        }
        ofile<<")";
        if(i!=carNum-1){
            ofile<<"\n";//不是最后一行就输出回车
        }
    }
    ofile.close();
    return true;
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
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
    }
}

void dataShow3D(vector<vector<vector<int > > > arr){
//用于查看二维向量内容
    if(arr.empty()){
        return;
    }
    int row = arr.size();
    printf("the content of %s is:\n",VNAME(arr));
    printf("(%d,%d)\n",row, arr[0].size());
    for(int i=0;i<row;i++){
        for(int j=0;j<arr[i].size();j++){
            for(int k=0;k<arr[i][j].size();k++){
                printf("%d ",arr[i][j][k]);
            }
            printf("\n");
        }
    }
}



int main()
{
    //输入文件的路径，包括车辆，道路，交叉口信息，以及输出文件
    string carPath = "F:\\比赛\\19年华为软件精英挑战赛\\1-map-training-1\\car.txt";
    string roadPath = "F:\\比赛\\19年华为软件精英挑战赛\\1-map-training-1\\road.txt";
    string crossPath = "F:\\比赛\\19年华为软件精英挑战赛\\1-map-training-1\\cross.txt";
    string answerPath = "F:\\比赛\\19年华为软件精英挑战赛\\1-map-training-1\\answer.txt";

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
    //dataShow(carData);
    //将数据转换成图和节点矩阵，双向图，有环图
    vector<ListNode*> crossNodeVector;// 用于存储每一个节点的指针，用于寻找路径，也可能其实用不着，
                                    //根据路口的序号就可以判断是不是到达目的地
    //ListNode* mapHead = NULL;
//建立图
    CreatRoadMap(roadData,crossData, &crossNodeVector);
//寻找可行路径
    vector<vector<vector<int> > > AvaiablePath;
    carPlanSearch(carData, crossNodeVector, &AvaiablePath);
//进行路径规划
	vector<vector<int > > PlanPath;
	PlanSelectRandom(crossNodeVector, carData, AvaiablePath, &PlanPath);
   dataShow(PlanPath);

	// TODO:write output file
	//将规划的路径进行输出
//输出txt
    bool answerDataWriteStatus = txtDataWrite(answerPath,PlanPath);
	return 0;
}
