/***********************
FileName:InfectStatistic.cpp
Author:Cazenove
Version:v1.1
Date:2020.02.10
Description:
    �ó���Ϊ����ͳ�Ƴ��򣬴�logĿ¼�ж�ȡ.log.txt�ļ���ͳ�Ʋ����ɵ���������Ϣ����־�ļ���
Version Description:Basic funtion
Function List:
    void init();
    void ReadAllLog(string path);
    void ReadLog(string filePath);
    void ShowProvince(string strProvince);
    void ShowAllProvince();
    void AddIP(string strProvince,int num);
    void AddSP(string strProvince,int num);
    void MoveIP(string strProvinceA,string strProvinceB,int num);
    void MoveSP(string strProvinceA,string strProvinceB,int num);
    void IPtoDead(string strProvince,int num);
    void IPtoCure(string strProvince,int num);
    void SPtoIP(string strProvince,int num);
    void SubSP(string strProvince,int num);
History:
    v1.0:Basic function
************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <io.h>
#include <vector>
#include <map>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <strstream>
#include <getopt.h>
#pragma execution_character_set("gbk")//�趨�ַ�������ֹ������������
using namespace std;


/***********************
Description:ʡ����Ϣ�ṹ�壬���ڴ洢����ʡ�ݵ�ȷ����ơ���������������
***********************/
struct SProvinceInformation
{
    unsigned int ip;//ȷ�ﻼ������
    unsigned int sp;//���ƻ�������
    unsigned int cure;//������������
    unsigned int dead;//������������
};

string PROVINCE[35] = 
{
    "ȫ��","����","����","����","����","����","����",
    "�㶫","����","����","����","�ӱ�","����","������",
    "����","����","����","����","����","����","���ɹ�",
    "����","�ຣ","ɽ��","ɽ��","����","�Ϻ�","�Ĵ�",
    "̨��","���","����","���","�½�","����","�㽭"
};

/***********************
Description:ʹ��STL��map������ʡ�����ƺ�ʡ����Ϣ�ṹ��֮���ӳ���ϵ
***********************/
map<string,SProvinceInformation> mapProvince;


/***********************
Description:�����ʼ��
Input:none
Output:none
Return:none
Others:
    ��ȡʡ�������ļ������mapProvince
***********************/
void init();


/***********************
Description:�Ƚ�����yyyy-mm-dd��ʽ���ַ������ڵĴ�С
Input:
    string date1:��һ������
    string date2:�ڶ�������
Output:none
Return:
    int���ͣ�Ϊ����ʹ�ã�����strcmp�����ķ���ֵ��
    date1>date2 ����ֵ����0
    date1<date2 ����ֵС��0
    date1=date2 ����ֵΪ0
Others:none
***********************/
int datecmp(string date1, string date2);


/***********************
Description:��ȡ�����ļ����У����и�������֮ǰ����־�ļ�
Input:
    string path:�������ļ���·��
    string date:yyyy-mm-dd��ʽ������
Output:none
Return:none
Others:
    �Ὣ��ȡ�������ļ�����ReadLog��������
***********************/
void ReadAllLog(string path, string date);


/***********************
Description:���������־�ļ�
Input:
    string filePath:·��+�ļ���
Output:none
Return:none
Others:
    ����ȡ�������ݴ���mapProvince
***********************/
void ReadLog(string filePath);

/***********************
Description:���������в�����������list()����
Input:
    int argc:��main������ȡ��argc
    char *argv[]:��main������ȡ��argv
Output:none
Return:none
Others:
    �������������list��������
***********************/
void ProcessOption(int argc,char *argv[]);


/***********************
Description:����list����
Input:
    string logPath:��ȡ����־�ļ�Ŀ¼
    string outPath:����ļ��Ĵ��Ŀ¼
    string date:yyyy-mm-dd��ʽ������
    vector<string> type:����ĸ�ʽ
    vector<string> province:�����ʡ��
Output:none
Return:none
Others:
    ʹ��init���г�ʼ��
    ����ReadAllLog��ȡ��־�ļ�
    ��ʹ��OutLog�����־�ļ�
***********************/
void list(string logPath, string outPath, string date, vector<string> type, vector<string> province);


/***********************
Description:������־�ļ�
Input:
Output:
Return:
Others:
***********************/
void OutLog(string filePath, vector<string> type, vector<string> province);


/***********************
Description:���ָ��ʡ�ݵ���Ա��Ϣ
Input:strProvince:ʡ������
Output:ʡ�� ��Ⱦ����a�� ���ƻ���b�� ����c�� ����d��
Return:none
Others:
***********************/
void ShowProvince(string strProvince);


/***********************
Description:�������ʡ�ݵ���Ա��Ϣ
Input:
Output:ʡ�� ��Ⱦ����a�� ���ƻ���b�� ����c�� ����d��
Return:none
Others:
***********************/
void ShowAllProvince();


/***********************
Description:<ʡ> ���� ��Ⱦ���� n��
Input:
    strProvince:ʡ����
Output:none
Return:none
Others:
***********************/
void AddIP(string strProvince,int num);


/***********************
Description:<ʡ> ���� ���ƻ��� n��
Input:
    strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void AddSP(string strProvince,int num);


/***********************
Description:<ʡ1> ��Ⱦ���� ���� <ʡ2> n��
Input:
    strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void MoveIP(string strProvinceA,string strProvinceB,int num);


/***********************
Description:<ʡ1> ���ƻ��� ���� <ʡ2> n��
Input:strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void MoveSP(string strProvinceA,string strProvinceB,int num);


/***********************
Description:<ʡ> ���� n��
Input:
Output:
Return:none
Others:
***********************/
void IPtoDead(string strProvince,int num);


/***********************
Description:<ʡ> ���� n��
Input:
Output:
Return:none
Others:
***********************/
void IPtoCure(string strProvince,int num);


/***********************
Description:<ʡ> ���ƻ��� ȷ���Ⱦ n��
Input:
Output:
Return:none
Others:
***********************/
void SPtoIP(string strProvince,int num);


/***********************
Description:<ʡ> �ų� ���ƻ��� n��
Input:
Output:
Return:none
Others:
***********************/
void SubSP(string strProvince,int num);


/*������*/
int main(int argc,char *argv[])
{
    ProcessOption(argc,argv);//���������в���
    system("pause");
    return 0;
}


void init()//��ʼ��
{
    //ifstream ifProvince("..\\221701210\\log\\provincelist.txt");//��ʡ�������ļ�
    /*ifstream ifProvince("D:\\Users\\qaz70\\Documents\\GitHub\\InfectStatistic-main\\221701210\\log\\provincelist.txt");//��ʡ�������ļ�
    if(!ifProvince)
    {
        cout<<"ʡ�������ļ���ʧ�ܣ�\n";
        exit(0);
    }*/
    
    mapProvince.clear();//���map
    string strProvince;
    for(int i=0; i<35; i++)
    {
        //ifProvince>>strProvince;//���ļ��ж�ȡʡ������
        SProvinceInformation spiProvince = {0};
        mapProvince[PROVINCE[i]] = spiProvince;//����ʡ����������Ϣ�洢�ṹ��ӳ���ϵ
    }


}

int datecmp(string date1, string date2)
{
    /*��yyyy-mm-dd��ʽ���ַ������뿪*/
    int year1,month1,day1;
    int year2,month2,day2;

    year1 = atoi(date1.substr(0,4).c_str());
    month1 = atoi(date1.substr(5,2).c_str());
    day1 = atoi(date1.substr(8,2).c_str());

    year2 = atoi(date2.substr(0,4).c_str());
    month2 = atoi(date2.substr(5,2).c_str());
    day2 = atoi(date2.substr(8,2).c_str());

    if(year1 > year2)
    {
        return 1;
    }
    else if(year1 == year2)
    {
        if(month1 > month2)
        {
            return 1;
        }
        else if(month1 == month2)
        {
            if(day1 > day2)
            {
                return 1;
            }
            else if(day1 == day2)
            {
                return 0;
            }
            else
            {
                return -1;
            }
            
        }
        else//month1 < month2
        {
            return -1;
        }
    }
    else//year1 < year2
    {
        return -1;
    }
}

void ReadAllLog(string path, string date)//��ȡ��date֮ǰ�ĸ���·����������־�ļ�
{
    long hFile = 0;//�ļ����

    struct _finddata_t fileinfo;//�ļ���Ϣ

    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*.log.txt").c_str(),&fileinfo)) != -1)
    {
        do
        {
            string fileName = fileinfo.name;
            string filePath = "\\";
            filePath = path + filePath + fileName;//�����������ļ�·��������
            ReadLog(filePath);//ͨ���ļ��������ļ����ж�Ӧ����
        } while (_findnext(hFile,&fileinfo) == 0);
        _findclose(hFile);
    }
}

void ReadLog(string filePath)
{
    ifstream ifLog(filePath.c_str());//����־�ļ�
    if(!ifLog)
    {
        cout<<filePath<<"�ļ���ʧ��\n";
        return ;
    }

    string buffer;//��ȡ�л�����
    while(getline(ifLog,buffer))//���ж�ȡ�ļ�
    {
        char cBuffer[10][20];
        int i=0;
        if(buffer.size() == 0)//��������
        {
            break;
        }
        istringstream ist(buffer);
        while(ist>>cBuffer[i++])//�ӻ���������������
        {
            
        }

        if(cBuffer[0][0]!='/')//����ע��
        {
            if(strcmp(cBuffer[1],"����") == 0)
            {
                if(strcmp(cBuffer[2],"��Ⱦ����") == 0)//������Ⱦ����
                {
                    AddIP(cBuffer[0],atoi(cBuffer[3]));
                }
                else//�������ƻ���
                {
                    AddSP(cBuffer[0],atoi(cBuffer[3]));
                }
            }
            else if(strcmp(cBuffer[1],"��Ⱦ����") == 0)//ʡ1��Ⱦ��������ʡ2
            {
                MoveIP(cBuffer[0],cBuffer[3],atoi(cBuffer[4]));
            }
            else if(strcmp(cBuffer[1],"���ƻ���") == 0)
            {
                if(strcmp(cBuffer[2],"����") == 0)//ʡ1���ƻ�������ʡ2
                {
                    MoveSP(cBuffer[0],cBuffer[3],atoi(cBuffer[4]));
                }
                else//���ƻ���ȷ�ϸ�Ⱦ
                {
                    SPtoIP(cBuffer[0],atoi(cBuffer[3]));
                }
            }
            else if(strcmp(cBuffer[1],"����") == 0)//��Ⱦ��������
            {
                IPtoDead(cBuffer[0],atoi(cBuffer[2]));
            }
            else if(strcmp(cBuffer[1],"����") == 0)//��Ⱦ��������
            {
                IPtoCure(cBuffer[0],atoi(cBuffer[2]));
            }
            else if(strcmp(cBuffer[1],"�ų�") == 0)//�ų����ƻ��߻���
            {
                SubSP(cBuffer[0],atoi(cBuffer[3]));
            }
        }
    }
    ifLog.close();
}

void ProcessOption(int argc,char *argv[])//�������
{
    if(argc > 1)//�в���
    {
        if(strcmp(argv[1], "list") == 0)
        {
            string logPath = "";
            string outPath = "";
            string date ="";
            vector<string> type;
            vector<string> province;

            int index = 2;
            while(argv[index])
            {
                if(strcmp(argv[index], "-log") == 0)
                {
                    if(argv[index+1])
                    {
                        logPath = argv[index+1];
                        index++;
                    }
                }
                else if(strcmp(argv[index], "-out") == 0)
                {
                    if(argv[index+1])
                    {
                        outPath = argv[index+1];
                        index++;
                    }
                }
                else if(strcmp(argv[index], "-date") == 0)
                {
                    if(argv[index+1][0] != '-')//�����һλ������������������ô����date�Ĳ���ֵ
                    {
                        date = argv[index+1];
                        index++;
                    }
                }
                else if(strcmp(argv[index], "-type") == 0)
                {
                    while((argv[index+1]) && (argv[index+1][0] != '-'))//-type���������0���������ֵ
                    {
                        type.push_back(argv[index+1]);
                        index++;
                    }
                }
                else if(strcmp(argv[index], "-province") == 0)//-province���������0���������
                {
                    while((argv[index+1]) && (argv[index+1][0] != '-'))
                    {
                        province.push_back(argv[index+1]);
                        index++;
                    }
                }
                else
                {
                    if(argv[index][0] == '-')
                    {
                        cout<<"δ֪�Ĳ�����"<<argv[index]<<endl;
                    }
                }
                index++;
            }

            if(logPath == "" || outPath == "")
            {
                cout<<"-log��-outָ���������Ϊ�գ�\n";
                exit(0);
            }
            list(logPath, outPath, date, type, province);//����list��������
        }
    }
}

void list(string logPath, string outPath, string date, vector<string> type, vector<string> province)//list����
{
    cout<<logPath<<endl<<outPath<<endl<<date<<endl;
    init();//��ʼ��
    ReadAllLog(logPath, date);//��ȡdate֮ǰ���е���־�ļ�
    OutLog(outPath, type, province);//����ָ����ʽ���
    ShowAllProvince();
}

void OutLog(string filePath, vector<string> type, vector<string> province)
{   
    ofstream ofLog(filePath.c_str(),ios::out);//������д���µ���־�ļ�
    if(!ofLog)
    {
        cout<<"���Ŀ¼��ʧ�ܣ�";
        exit(0);
    }

    for(int i=0;i<35;i++)//����ʡ���б��˳�����ÿ��ʡ�ݵ�������Ϣ
    {
        ofLog<<PROVINCE[i]<<" ��Ⱦ����"<<mapProvince[PROVINCE[i]].ip<<"�� ";
        ofLog<<"���ƻ���"<<mapProvince[PROVINCE[i]].sp<<"�� ";
        ofLog<<"����"<<mapProvince[PROVINCE[i]].cure<<"�� ";
        ofLog<<"����"<<mapProvince[PROVINCE[i]].dead<<"��\n";
    }
    ofLog<<"// ���ĵ�������ʵ���ݣ���������ʹ��";

    ofLog.close();
}

void ShowProvince(string strProvince)//��ʡ�������������
{
    SProvinceInformation *pProvince=&mapProvince[strProvince];
    cout<<strProvince;
    printf(" ��Ⱦ����%d�� ",pProvince->ip);
    printf("���ƻ���%d�� ",pProvince->sp);
    printf("����%d�� ",pProvince->cure);
    printf("����%d��\n",pProvince->dead);
    delete(pProvince);
}

void ShowAllProvince()//�������ʡ�ݵ�������Ϣ
{
    for(int i=0;i<35;i++)//����ʡ���б��˳�����ÿ��ʡ�ݵ�������Ϣ
    {
        cout<<PROVINCE[i]<<" ��Ⱦ����"<<mapProvince[PROVINCE[i]].ip<<"�� ";
        cout<<"���ƻ���"<<mapProvince[PROVINCE[i]].sp<<"�� ";
        cout<<"����"<<mapProvince[PROVINCE[i]].cure<<"�� ";
        cout<<"����"<<mapProvince[PROVINCE[i]].dead<<"��\n";
    }
}

void AddIP(string strProvince,int num)
{
    mapProvince[strProvince].ip += num;
    mapProvince["ȫ��"].ip += num;
}
void AddSP(string strProvince,int num)
{
    mapProvince[strProvince].sp += num;
    mapProvince["ȫ��"].sp += num;
}
void MoveIP(string strProvinceA,string strProvinceB,int num)
{
    mapProvince[strProvinceA].ip -= num;
    mapProvince[strProvinceB].ip += num;
}
void MoveSP(string strProvinceA,string strProvinceB,int num)
{
    mapProvince[strProvinceA].sp -= num;
    mapProvince[strProvinceB].sp += num;
}
void IPtoDead(string strProvince,int num)
{
    mapProvince[strProvince].ip -= num;
    mapProvince[strProvince].dead += num;
    mapProvince["ȫ��"].ip -= num;
    mapProvince["ȫ��"].dead += num;
}
void IPtoCure(string strProvince,int num)
{
    mapProvince[strProvince].ip -= num;
    mapProvince[strProvince].cure += num;
    mapProvince["ȫ��"].ip -= num;
    mapProvince["ȫ��"].cure += num;
}
void SPtoIP(string strProvince,int num)
{
    mapProvince[strProvince].sp -= num;
    mapProvince[strProvince].ip += num;
    mapProvince["ȫ��"].sp -= num;
    mapProvince["ȫ��"].ip += num;
}
void SubSP(string strProvince,int num)
{
    mapProvince[strProvince].sp -= num;
    mapProvince["ȫ��"].sp -= num;
}