#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include<cassert>
#include<stdlib.h>
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

void carPathSearch(int startCross, int endCross,vector<ListNode*  > *CrossNodeVector,
                   vector<vector<int> > *Path, int *CurrentPathSum,vector<int > *isVisted, vector<int > *isReachable){//���ﲻ��Ҫ�ı��������β�,isVisted,CurrentPahtSumҲֻ���β�
//ע�⴫������isVisted����Ϊȫ�㣬Ҳ���ǳ�ʼ״̬
//������һ��·�ڵ���һ��·�ڵ����п���·��������ֻ����·����ʱ��ļ�����ݾ���ĳ���ȷ�����������Խ�ʡ�ܴ�һ����ʱ��
//����·����������ȷ����ͬʱ�ڵݹ�Ĺ�������Ҫ��¼·�߻���˵�Ǽ�¼�����Ľڵ�
//Ϊ�˱�����ѭ������Ҫ��¼�ڵ��Ƿ���ʹ���״̬���飬�ڵ���·���в����ظ����ʣ�������ɺ�Ҫ����״̬������Ŀǰ��������ѭ��
//��������������Ҳ�����ǵݹ�ջ���ˡ����ҵ��µ�·��֮���µ�vector�����ã�push����back��ջ
//��Ҫ��ǰ��Path����ռ䣬Ҳ����resizeһ�£���Ȼֱ�ӵ���(*Path)[0]���
//cross��1��ʼ����������
    int CurrentPathSumTemp = (*CurrentPathSum);
    (*Path)[(*CurrentPathSum)].push_back(startCross);
    (*isVisted)[startCross-1] = 1;//���ýڵ�Ϊ�Ѿ�����

    //�������·���������ҵ�һ��·��,��Ҫ���жϽڵ�����ڽ�������
    if(((*CrossNodeVector)[startCross-1]->UpCross&&(*CrossNodeVector)[startCross-1]->UpCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->RightCross&&(*CrossNodeVector)[startCross-1]->RightCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->DownCross&&(*CrossNodeVector)[startCross-1]->DownCross->crossNumber == endCross)||
       ((*CrossNodeVector)[startCross-1]->LeftCross&&(*CrossNodeVector)[startCross-1]->LeftCross->crossNumber == endCross)){

        (*isVisted)[endCross-1] = 1;//�յ�Ҳ��Ϊ�����ʹ�����������ж��鷳
        (*CurrentPathSum)++;
        (*Path).resize((*CurrentPathSum)+1);//��Ҫ�����һ�����洢��һ��·�ߣ�������Ҫ��֮ǰ��·������������
        for(int i=0;i<(*Path)[(*CurrentPathSum-1)].size();i++){//���µ�·����������֮ǰ�Ľڵ�·��
            (*Path)[*CurrentPathSum].push_back((*Path)[*CurrentPathSum-1][i]);
        }
        (*Path)[*CurrentPathSum-1].push_back(endCross);//��֮ǰ��·���з����յ�
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
    //��ɵ�ǰ�ڵ��������,�������·��������û����ô�������ڵ�֮���ǲ����е�
    if((*CurrentPathSum)==CurrentPathSumTemp){//���û�ҵ��µ�·��
        (*isReachable)[startCross-1]=0;
       // printf("this cross cannot come to end %d\n",startCross);
    }
    //����ҵ�һ��·���˾Ͳ�Ҫ����pop�ˣ���������������������û�ҵ�·��������²���Ҫpop��������Ҫ�̳�֮ǰ��·����Ϣ
    (*Path)[(*CurrentPathSum)].pop_back();
    (*isVisted)[startCross-1] = 0;
    return;
}

void carPlanSearch(vector<vector<int> > carData, vector<ListNode*  > crossNodeVector, vector<vector<vector<int> > >* AvaiablePath){
//�������г������п���·������һ����ά������ʾ����һά��carId���ڶ�ά�ǿ���·�ߣ�����ά��·����
//���ǵ�ʵ�ʳ����������ܻ�Ƚڵ�������ƽ��n^2���࣬���п��ܴ����ظ���·�ߣ���ô�ʹ�����ÿ�μ�����Ľڵ��֮��Ŀ���·��
//��һ�γ����ظ�·�߾�ֱ�ӵ��ã����ڻ�û��ʵ����������Ч�ʿ���
//(id,from,to,speed,planTime)
    int carNum = carData.size();
    (*AvaiablePath).resize(carNum);
    int SatrtCross = 0;
    int EndCross = 0;

    vector<int> isVisted;//��¼�ڵ��Ƿ񱻷��ʹ��������ڱ���ͼ��ʱ����Ϊ��������ѭ����
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
        //��Ҫ��Path������һ�и��ߵ���������CurrentPathSum������ѡ����ЩԪ�أ��ǲ���pop_back�ͺ���
       // printf("the CurrentPathSum of %dth inter is :%d\n",i,CurrentPathSum);
        if(Path.size()>CurrentPathSum){
            Path.pop_back();
        }
        (*AvaiablePath)[i] = Path;//������ֵ�᲻�������
        //����֮����Ҫ��Path��ɾ����CurrentPathSum��isVisted��isReachable����Ҫ��ʼ��
        Path.clear();//clear��������Ҫ����resize
        Path.resize(1);
        CurrentPathSum = 0;
        for(int ii=0;ii<isVisted.size();ii++){
            isVisted[ii] = 0;
            isReachable[ii] = 1;
        }
    }

}

void crossPath2RoadPath(vector<ListNode*  > crossNodeVector, vector<int > CrossPath,vector<int> *RoadPath){
//���ڵ���ʽ��·��ת��Ϊ��·ID��ʽ��·��
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
//ѡ�����ķ�����ֱ�����
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
        //��ʼ���ѡ·��
        choose = rand()%AvaiablePath[i].size();
        //CrossPath.insert(CrossPath.begin(),AvaiablePath[i][choose].begin(),AvaiablePath[i][choose].end());
        CrossPath = AvaiablePath[i][choose];
        //��·���ɽڵ���ʽת��Ϊ�ߵ���ʽ
        crossPath2RoadPath(crossNodeVector, CrossPath, &RoadPath);
        (*PlanPath)[i].insert((*PlanPath)[i].end(), RoadPath.begin(), RoadPath.end());
        vector<int>().swap(RoadPath);
    }
}

void PlanSelectIndivual(vector<vector<int> > carData, vector<vector<vector<int> > > AvaiablePath, vector<vector<int> >* PlanPath){
//ѡ�����ķ��������������壬ֻ����ÿ���������ʱ��
}
//��·��ת��Ϊ�ڴ��������ʽ
int PlanEvaluate(vector<vector<int> >* PlanPath){
    return 0;
}



bool txtDataRead(string carPath, vector<vector<int> > &carData, int cols){
// ����carPathΪ�ļ���·����һ��ʼ���ÿһ��car��path��cross��ÿһ��txt��дһ��������ȡ�����Ƿ�����ʵ��ͬһ������
//cols��Ϊtxt�ļ��������������car��cross����Ϊ5������road����Ϊ7
//car  #(id,from,to,speed,planTime)
//cross #(id,roadId,roadId,roadId,roadId)
//road #(id,length,speed,channel,from,to,isDuplex)

//��ԭ��ѭ��ֹͣ����Ϊָ���ߵ��ļ�����������£�����һ������ Ŀǰ�ȼ����������ٶ��ļ�

    //std::cout << "Path is " << carPath << std::endl;

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
   // printf("the rows is:%d\n",rows);
    infile.clear(std::ios::goodbit);
    infile.seekg(std::ios::beg);
    //
    string s;
    getline(infile,s);
    //cout<<s<<endl;
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
            ofile<<"\n";//�������һ�о�����س�
        }
    }
    ofile.close();
    return true;
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
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
    }
}

void dataShow3D(vector<vector<vector<int > > > arr){
//���ڲ鿴��ά��������
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
    //�����ļ���·����������������·���������Ϣ���Լ�����ļ�
    string carPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\1-map-training-1\\car.txt";
    string roadPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\1-map-training-1\\road.txt";
    string crossPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\1-map-training-1\\cross.txt";
    string answerPath = "F:\\����\\19�껪Ϊ�����Ӣ��ս��\\1-map-training-1\\answer.txt";

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
    //dataShow(carData);
    //������ת����ͼ�ͽڵ����˫��ͼ���л�ͼ
    vector<ListNode*> crossNodeVector;// ���ڴ洢ÿһ���ڵ��ָ�룬����Ѱ��·����Ҳ������ʵ�ò��ţ�
                                    //����·�ڵ���žͿ����ж��ǲ��ǵ���Ŀ�ĵ�
    //ListNode* mapHead = NULL;
//����ͼ
    CreatRoadMap(roadData,crossData, &crossNodeVector);
//Ѱ�ҿ���·��
    vector<vector<vector<int> > > AvaiablePath;
    carPlanSearch(carData, crossNodeVector, &AvaiablePath);
//����·���滮
	vector<vector<int > > PlanPath;
	PlanSelectRandom(crossNodeVector, carData, AvaiablePath, &PlanPath);
   dataShow(PlanPath);

	// TODO:write output file
	//���滮��·���������
//���txt
    bool answerDataWriteStatus = txtDataWrite(answerPath,PlanPath);
	return 0;
}
