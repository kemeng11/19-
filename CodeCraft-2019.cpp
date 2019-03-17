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

    //��������·������ٶ�
    int UpRoadChannel;
    int RightRoadChannel;
    int DownRoadChannel;
    int LeftRoadChannel;

    //�ĸ������Ľڵ�
    ListNode* UpCross;
    ListNode* RightCross;
    ListNode* DownCross;
    ListNode* LeftCross;
};

void CreatRoadMap(vector<vector<int> > RoadData,vector<vector<int> > CrossData,vector<ListNode*  > *CrossNodeVector){
//����һ��ͼ����ʾ��ͨ·��
    //���ȶ�ÿ��·�ڽ���һ���ڵ�
    //cross #(id,roadId,roadId,roadId,roadId) ·���Ǵ�1��ʼ��ŵ�
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

    //���Ž���·����Ϣ�ѽڵ���������,ͬʱ����·�ĳ��Ⱥ����٣�Ҫ�����￼�ǵ���˫�������
    int roadNum = RoadData.size();
    //road #(id,length,speed,channel,from,to,isDuplex)
    for(int i=0;i<roadNum;i++){
        int RoadId = RoadData[i][0];
        int RoadStart = RoadData[i][4];
        int RoadEnd = RoadData[i][5];
        int isDuplex = RoadData[i][6];
        // ����ʼ���·�������id��ͬ��·
        ListNode* StartNode = (*CrossNodeVector)[RoadStart-1];//ȡȥ��ʼ�ڵ�
        ListNode* EndNode = (*CrossNodeVector)[RoadEnd-1];//ȡȥ�յ�ڵ�
        if(StartNode->UpRoadId == RoadId){
            StartNode->UpCross = EndNode;//�ڵ�
            StartNode->UpRoadLength = RoadData[i][1];//·��
            StartNode->UpRoadMaxSpeed = RoadData[i][2];//����
            StartNode->UpRoadChannel = RoadData[i][3];//������
            if(isDuplex==1){//����˫����������¹�ϵ�����ҹ�ϵ��Ϊ�ߵ�
                EndNode->DownCross = StartNode;
                EndNode->DownRoadLength = RoadData[i][1];
                EndNode->DownRoadMaxSpeed = RoadData[i][2];
                EndNode->DownRoadChannel = RoadData[i][3];
            }
        }else if(StartNode->RightRoadId == RoadId){
            StartNode->RightCross = EndNode;//�ڵ�
            StartNode->RightRoadLength = RoadData[i][1];//·��
            StartNode->RightRoadMaxSpeed = RoadData[i][2];//����
            StartNode->RightRoadChannel = RoadData[i][3];//������
            if(isDuplex==1){//����˫����������¹�ϵ�����ҹ�ϵ��Ϊ�ߵ�
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
            if(isDuplex==1){//����˫����������¹�ϵ�����ҹ�ϵ��Ϊ�ߵ�
                EndNode->UpCross = StartNode;
                EndNode->UpRoadLength = RoadData[i][1];
                EndNode->UpRoadMaxSpeed = RoadData[i][2];
                EndNode->UpRoadChannel = RoadData[i][3];
            }
        }else{
            StartNode->LeftCross = EndNode;//�ڵ�
            StartNode->LeftRoadLength = RoadData[i][1];//·��
            StartNode->LeftRoadMaxSpeed = RoadData[i][2];//����
            StartNode->LeftRoadChannel = RoadData[i][3];//������
            if(isDuplex==1){//����˫����������¹�ϵ�����ҹ�ϵ��Ϊ�ߵ�
                EndNode->RightCross = StartNode;
                EndNode->RightRoadLength = RoadData[i][1];
                EndNode->RightRoadMaxSpeed = RoadData[i][2];
                EndNode->RightRoadChannel = RoadData[i][3];
            }
        }

    }
}

void carPathSearch(int startCross, int endCross,vector<ListNode*  > CrossNodeVector,
                   vector<vector<int> > *Path, int CurrentPathSum,vector<int > isVisted){//���ﲻ��Ҫ�ı��������β�,isVisted,CurrentPahtSumҲֻ���β�
//ע�⴫������isVisted����Ϊȫ�㣬Ҳ���ǳ�ʼ״̬
//������һ��·�ڵ���һ��·�ڵ����п���·��������ֻ����·����ʱ��ļ�����ݾ���ĳ���ȷ�����������Խ�ʡ�ܴ�һ����ʱ��
//����·����������ȷ����ͬʱ�ڵݹ�Ĺ�������Ҫ��¼·�߻���˵�Ǽ�¼�����Ľڵ�
//Ϊ�˱�����ѭ������Ҫ��¼�ڵ��Ƿ���ʹ���״̬���飬�ڵ���·���в����ظ����ʣ�������ɺ�Ҫ����״̬
//��Ҫ��ǰ��Path����ռ䣬Ҳ����resizeһ�£���Ȼֱ�ӵ���(*Path)[0]���

    (*Path)[CurrentPathSum].push_back(startCross);
    isVisted[startCross] = 1;
    //�������·������
    if(CrossNodeVector[startCross]->UpCross->crossNumber == endCross){
        CurrentPathSum++;
        (*Path).resize(CurrentPathSum+1);//��Ҫ�����һ�����洢��һ��·��
    }
    //ֱ��������������費��Ҫ���ǹո�������ӣ�



    (*Path)[CurrentPathSum].pop_back();
    isVisted[startCross] = 0;
}


void carPlanSearch(vector<vector<int> > carData, vector<vector<vector<int> > >* AvaiablePath){
//�������г������п���·������һ����ά������ʾ����һά��carId���ڶ�ά�ǿ���·�ߣ�����ά��·����
//���ǵ�ʵ�ʳ����������ܻ�Ƚڵ�������ƽ��n^2���࣬���п��ܴ����ظ���·�ߣ���ô�ʹ�����ÿ�μ�����Ľڵ��֮��Ŀ���·������һ�γ����ظ�·�߾�ֱ�ӵ���


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
    dataShow(carData);
    //������ת����ͼ�ͽڵ����˫��ͼ���л�ͼ

    vector<ListNode*> crossNodeVector;// ���ڴ洢ÿһ���ڵ��ָ�룬����Ѱ��·����Ҳ������ʵ�ò��ţ�
                                    //����·�ڵ���žͿ����ж��ǲ��ǵ���Ŀ�ĵ�
    ListNode* mapHead = NULL;
    CreatRoadMap(roadData,crossData, &crossNodeVector);
    printf("the size of crossNodeVector is:%d\n",crossNodeVector.size());
    for(int i=0;i<crossNodeVector.size();i++){
        printf("%d\t",(crossNodeVector[i])->crossNumber);
    }
    printf("\n");
    for(int i=0;i<crossNodeVector.size();i++){
        printf("%d\t",(crossNodeVector[i])->LeftRoadLength);
    }
    //����ͼѰ�ҿ���·����Dijstra�����·����
    vector<int> isVisted;//��¼�ڵ��Ƿ񱻷��ʹ��������ڱ���ͼ��ʱ����Ϊ��������ѭ����
    isVisted.resize(crossNodeVector.size());
    for(int i=0;i<isVisted.size();i++){
        isVisted[i] = 0;
    }





	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	//���滮��·���������
//    bool answerDataWriteStatus = answerDataWrite( answerPath, plannedPath);

	return 0;
}
