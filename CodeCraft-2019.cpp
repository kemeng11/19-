#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include <cassert>
using namespace std;

#define VNAME(value) (#value)


struct ListNode{
//���������洢�ڵ�ͱߣ���һ����Ϊ�˱�ʾͼ��ͬʱ�����·������Ӧ���ǱȽϼ򵥵ģ��õݹ�Ϳ���������
    int crossNumber;//����·�ڵ����/id

    //��������·��id,˳ʱ�뷽����������
    int UpRoadId;//����·��id
    int RightRoadId;//�ұ�·��id
    int DownRoadId;//����·��id
    int LeftRoadId;//���·��id

    //��������·�ĳ���
    int UpRoadLength;
    int RightRoadLength;
    int DownRoadLength;
    int LeftRoadLength;

    //��������·������ٶ�
    int UpRoadMaxSpeed;
    int RightRoadMaxSpeed;
    int DownRoadMaxSpeed;
    int LeftRoadMaxSpeed;

    //�ĸ������Ľڵ�
    ListNode* UpCross;
    ListNode* RightCross;
    ListNode* DownCross;
    ListNode* LeftCross;
};

void CreatRoadMap(vector<vector<int> > RoadData,vector<vector<int> > CrossData, ListNode* MapHead,vector<ListNode*  > *CrossNodeVector){
//����һ��ͼ����ʾ��ͨ·��
    //���ȶ�ÿ��·�ڽ���һ���ڵ�
    //cross #(id,roadId,roadId,roadId,roadId) ·���Ǵ�1��ʼ��ŵ�
    //road #(id,length,speed,channel,from,to,isDuplex)
    int crossNum = CrossData.size();
    (*CrossNodeVector).resize(crossNum);
    for(int i=0;i<crossNum;i++){
        ListNode *TempNode = new ListNode();//�½�һ���ڵ�
        //�洢������·
        TempNode->crossNumber = CrossData[i][0];
        TempNode->UpRoadId = CrossData[i][1];
        TempNode->RightRoadId = CrossData[i][2];
        TempNode->DownRoadId = CrossData[i][3];
        TempNode->LeftRoadId = CrossData[i][4];
        //���ڵ�·�����ÿ�
        TempNode->UpCross = NULL;
        TempNode->RightCross = NULL;
        TempNode->DownCross = NULL;
        TempNode->LeftCross = NULL;
        //���ڵ�ָ��洢����
       // printf("this is the %dth iter\n",i);
        (*CrossNodeVector)[CrossData[i][0]-1] = TempNode;//���λ����·��id�й�
        //ָ���ʼ��
        TempNode = NULL;
    }
    //���Ž���·����Ϣ�ѽڵ���������
}

void carPathSearch(int startCross,int endCross,vector<int> Path){
//������һ��·�ڵ���һ��·�ڵ����п���·��������ֻ����·����ʱ��ļ�����ݾ���ĳ���ȷ�����������Խ�ʡ�ܴ�һ����ʱ��

}


void carPlanSearch(vector<vector<int> > carData, vector<vector<vector<int> > >* AvaiablePath){
//�������г������п���·������һ����ά������ʾ����һά��carId���ڶ�ά�ǿ���·�ߣ�����ά��·����


}

void PlanSelectRandom(vector<vector<vector<int> > > AvaiablePath){
//ѡ�����ķ�����ֱ�����
}

void PlanSelectIndivual(vector<vector<vector<int> > > AvaiablePath, vector<vector<int> >* PlanPath){
//ѡ�����ķ��������������壬ֻ����ÿ���������ʱ��
}

int PlanEvaluate(vector<vector<int> >* PlanPath){

}



bool txtDataRead(string carPath, vector<vector<int> > &carData, int cols){
// ����carPathΪ�ļ���·����һ��ʼ���ÿһ��car��path��cross��ÿһ��txt��дһ��������ȡ�����Ƿ�����ʵ��ͬһ������
//cols��Ϊtxt�ļ��������������car��cross����Ϊ5������road����Ϊ7
//car  #(id,from,to,speed,planTime)
//cross #(id,roadId,roadId,roadId,roadId)
//road #(id,length,speed,channel,from,to,isDuplex)

//Ŀǰ�������ǻ���һ�����ݲ�֪��Ϊʲô,
//��ԭ��ѭ��ֹͣ����Ϊָ���ߵ��ļ�����������£�����һ������
//Ŀǰ�ȼ����������ٶ��ļ�

    std::cout << "Path is " << carPath << std::endl;

    ifstream infile;
    infile.open(carPath.data());
    assert(infile.is_open());
    //�����ļ���ȷ������
    string temp;
    int rows = 0;
    while(getline(infile,temp)){
        rows++;
    }
    carData.resize(rows-1);//��ȥ��һ��ע�ͣ�ʣ�µľ������ݵ�������
    printf("the rows is:%d\n",rows);
    infile.clear(std::ios::goodbit);
    infile.seekg(std::ios::beg);
    //
    string s;
    getline(infile,s);
    cout<<s<<endl;
    //�����ſ�ʼ��ȡ��������
    char c;
    int number;
    int i=0;
    while(i<rows-1){
        carData[i].resize(cols);
        infile>>c;//��ȡ��ͷ������
        for(int j=0;j<cols;j++){
            infile>>number;//��ȡһ����
            infile>>c;//��������Ķ��Ż���������
            carData[i][j] = number;
        }
        i++;
    }
    printf("i = %d\n",i);
    infile.close();
    printf("(%d,%d)\n",carData.size(), carData[0].size());
}


void dataShow(vector<vector<int> > arr){
//���ڲ鿴��ά��������
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
    //�����ļ���·����������������·���������Ϣ���Լ�����ļ�
    string carPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\config\\car.txt";
    string roadPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\config\\road.txt";
    string crossPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\config\\cross.txt";
    string answerPath = "..\\config\\answer.txt";

    //������ά����洢������Ϣ��·����Ϣ���������Ϣ���Լ��滮��·��
    vector<vector<int> > carData;
    vector<vector<int> > roadData;
    vector<vector<int> > crossData;
    vector<vector<int> > plannedPath;
    //��ȡ�����ļ�
    //(id,from,to,speed,planTime)
    bool carDataReadStatus = txtDataRead( carPath,  carData,5);
    //(id,roadId,roadId,roadId,roadId)
    bool roadDataReadStatus = txtDataRead( roadPath,  roadData,7);
    //(id,length,speed,channel,from,to,isDuplex)
    bool crossDataReadStatus = txtDataRead( crossPath, crossData,5);
    dataShow(crossData);
    //������ת����ͼ�ͽڵ����˫��ͼ���л�ͼ

    vector<int> isVisted;//��¼�ڵ��Ƿ񱻷��ʹ��������ڱ���ͼ��ʱ����Ϊ��������ѭ����
    vector<ListNode*> crossNodeVector;// ���ڴ洢ÿһ���ڵ��ָ�룬����Ѱ��·����Ҳ������ʵ�ò��ţ�
                                    //����·�ڵ���žͿ����ж��ǲ��ǵ���Ŀ�ĵ�
    ListNode* mapHead = NULL;
    CreatRoadMap(roadData,crossData, mapHead, &crossNodeVector);
    printf("the size of crossNodeVector is:%d\n",crossNodeVector.size());
    for(int i=0;i<crossNodeVector.size();i++){
        printf("%d\t",(crossNodeVector[i])->crossNumber);
    }
    //����ͼѰ�ҿ���·����Dijstra�����·����






	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	//���滮��·���������
//    bool answerDataWriteStatus = answerDataWrite( answerPath, plannedPath);

	return 0;
}
