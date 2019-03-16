#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include <cassert>
using namespace std;

#define VNAME(value) (#value)

bool txtDataRead(string carPath, vector<vector<int> > &carData,int cols){
//目前代码总是会多读一行数据不知道为什么,
//在原先循坏停止条件为指针走到文件结束的情况下，会多读一行数据
//目前先计算行数，再读文件
    std::cout << "carPath is " << carPath << std::endl;

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
    dataShow(carData);
    //将数据转换成图和节点矩阵，双向图，有环图


    //根据图寻找可行路径，Dijstra找最短路径。






	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	//将规划的路径进行输出
//    bool answerDataWriteStatus = answerDataWrite( answerPath, plannedPath);

	return 0;
}
