#include<stdio.h>
#include "iostream"
#include<fstream>
#include<vector>
#include <cassert>
using namespace std;

#define VNAME(value) (#value)

bool txtDataRead(string carPath, vector<vector<int> > &carData,int cols){
//Ŀǰ�������ǻ���һ�����ݲ�֪��Ϊʲô,
//��ԭ��ѭ��ֹͣ����Ϊָ���ߵ��ļ�����������£�����һ������
//Ŀǰ�ȼ����������ٶ��ļ�
    std::cout << "carPath is " << carPath << std::endl;

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

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;
	
	if(argc < 5){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}
	
	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string answerPath(argv[4]);
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


    //����ͼѰ�ҿ���·����Dijstra�����·����






	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	//���滮��·���������
//    bool answerDataWriteStatus = answerDataWrite( answerPath, plannedPath);

	return 0;
}
