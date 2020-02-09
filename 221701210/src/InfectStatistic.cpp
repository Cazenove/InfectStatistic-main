/***********************
FileName:InfectStatistic.cpp
Author:Cazenove
Version:1.0
Date:2020.02.09
Description:
Version Description:Basic funtion
Function List:
    void init();
    void ReadAllLog(string path);
    void ProcessLogFile(string filePath);
    void ShowProvince(string strProvince);
    void ShowAllProvince();
    void AddDiagnosis(string strProvince,int num);
    void AddSuspected(string strProvince,int num);
    void MoveDiagnosis(string strProvinceA,string strProvinceB,int num);
    void MoveSuspected(string strProvinceA,string strProvinceB,int num);
    void DeadDiagnosis(string strProvince,int num);
    void CureDiagnosis(string strProvince,int num);
    void SuspectedToDiagnosis(string strProvince,int num);
    void ExcludeSuspected(string strProvince,int num);
History:none

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
#pragma execution_character_set("gbk")//�趨�ַ�������ֹ������������
using namespace std;


/***********************
Description:ʡ����Ϣ�ṹ�壬���ڴ洢����ʡ�ݵ�ȷ����ơ���������������
***********************/
struct SProvinceInformation
{
    unsigned int diagnosis;//ȷ�ﻼ������
    unsigned int suspected;//���ƻ�������
    unsigned int cure;//������������
    unsigned int death;//������������

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
Others:none
***********************/
void init();


/***********************
Description:��ȡ���е���־�ļ�
Input:
Output:
Return:
Others:
***********************/
void ReadAllLog(string path);


/***********************
Description:���������־�ļ�
Input:
Output:
Return:
Others:
***********************/
void ProcessLogFile(string filePath);


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
Input:strProvince:ʡ������
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
void AddDiagnosis(string strProvince,int num);


/***********************
Description:<ʡ> ���� ���ƻ��� n��
Input:
    strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void AddSuspected(string strProvince,int num);


/***********************
Description:<ʡ1> ��Ⱦ���� ���� <ʡ2> n��
Input:
    strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void MoveDiagnosis(string strProvinceA,string strProvinceB,int num);


/***********************
Description:<ʡ1> ���ƻ��� ���� <ʡ2> n��
Input:strProvince:ʡ������
Output:none
Return:none
Others:
***********************/
void MoveSuspected(string strProvinceA,string strProvinceB,int num);


/***********************
Description:<ʡ> ���� n��
Input:
Output:
Return:none
Others:
***********************/
void DeadDiagnosis(string strProvince,int num);


/***********************
Description:<ʡ> ���� n��
Input:
Output:
Return:none
Others:
***********************/
void CureDiagnosis(string strProvince,int num);


/***********************
Description:<ʡ> ���ƻ��� ȷ���Ⱦ n��
Input:
Output:
Return:none
Others:
***********************/
void SuspectedToDiagnosis(string strProvince,int num);


/***********************
Description:<ʡ> �ų� ���ƻ��� n��
Input:
Output:
Return:none
Others:
***********************/
void ExcludeSuspected(string strProvince,int num);

/*������*/
int main(int args,char *argv[])
{
    init();
    ReadAllLog("..\\221701210\\log");
    ShowAllProvince();
    system("pause");
    return 0;
}


void init()//��ʼ��
{
    ifstream ifProvince("..\\221701210\\log\\provincelist.txt");
    if(!ifProvince)
    {
        cout<<"ʡ�������ļ���ʧ�ܣ�\n";
        exit(0);
    }
    
    string strProvince;
    for(int i=0;i<35;i++)
    {
        ifProvince>>strProvince;
        SProvinceInformation spiProvince = {0};
        mapProvince[strProvince] = spiProvince;//����ʡ����������Ϣ�洢�ṹ��ӳ���ϵ
    }
}

void ReadAllLog(string path)
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
            ProcessLogFile(filePath);//ͨ���ļ��������ļ����ж�Ӧ����
        } while (_findnext(hFile,&fileinfo) == 0);
        _findclose(hFile);
    }
}

void ProcessLogFile(string filePath)
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
                    AddDiagnosis(cBuffer[0],atoi(cBuffer[3]));
                }
                else//�������ƻ���
                {
                    AddSuspected(cBuffer[0],atoi(cBuffer[3]));
                }
            }
            else if(strcmp(cBuffer[1],"��Ⱦ����") == 0)//ʡ1��Ⱦ��������ʡ2
            {
                MoveDiagnosis(cBuffer[0],cBuffer[3],atoi(cBuffer[4]));
            }
            else if(strcmp(cBuffer[1],"���ƻ���") == 0)
            {
                if(strcmp(cBuffer[2],"����") == 0)//ʡ1���ƻ�������ʡ2
                {
                    MoveSuspected(cBuffer[0],cBuffer[3],atoi(cBuffer[4]));
                }
                else//���ƻ���ȷ�ϸ�Ⱦ
                {
                    SuspectedToDiagnosis(cBuffer[0],atoi(cBuffer[3]));
                }
            }
            else if(strcmp(cBuffer[1],"����") == 0)//��Ⱦ��������
            {
                DeadDiagnosis(cBuffer[0],atoi(cBuffer[2]));
            }
            else if(strcmp(cBuffer[1],"����") == 0)//��Ⱦ��������
            {
                CureDiagnosis(cBuffer[0],atoi(cBuffer[2]));
            }
            else if(strcmp(cBuffer[1],"�ų�") == 0)//�ų����ƻ��߻���
            {
                SuspectedToDiagnosis(cBuffer[0],atoi(cBuffer[3]));
            }
        }
    }
    ifLog.close();
}

void ShowProvince(string strProvince)//��ʡ�������������
{
    SProvinceInformation *pProvince=&mapProvince[strProvince];
    cout<<strProvince;
    printf(" ��Ⱦ����%d�� ",pProvince->diagnosis);
    printf("���ƻ���%d�� ",pProvince->suspected);
    printf("����%d�� ",pProvince->cure);
    printf("����%d��\n",pProvince->death);
    delete(pProvince);
}

void ShowAllProvince()//�������ʡ�ݵ�������Ϣ
{
    ifstream ifProvince("..\\221701210\\log\\provincelist.txt");
    if(!ifProvince)
    {
        cout<<"ʡ�������ļ���ʧ�ܣ�\n";
        exit(0);
    }
    string strProvince;
    for(int i=0;i<35;i++)//����ʡ���б��˳�����ÿ��ʡ�ݵ�������Ϣ
    {
        ifProvince>>strProvince;
        cout<<strProvince<<" ��Ⱦ����"<<mapProvince[strProvince].diagnosis<<"�� ";
        cout<<"���ƻ���"<<mapProvince[strProvince].suspected<<"�� ";
        cout<<"����"<<mapProvince[strProvince].cure<<"�� ";
        cout<<"����"<<mapProvince[strProvince].death<<"��\n";
    }
}

void AddDiagnosis(string strProvince,int num)
{
    mapProvince[strProvince].diagnosis += num;
    mapProvince["ȫ��"].diagnosis += num;
}
void AddSuspected(string strProvince,int num)
{
    mapProvince[strProvince].suspected += num;
    mapProvince["ȫ��"].suspected += num;
}
void MoveDiagnosis(string strProvinceA,string strProvinceB,int num)
{
    mapProvince[strProvinceA].diagnosis -= num;
    mapProvince[strProvinceB].diagnosis += num;
}
void MoveSuspected(string strProvinceA,string strProvinceB,int num)
{
    mapProvince[strProvinceA].suspected -= num;
    mapProvince[strProvinceB].suspected += num;
}
void DeadDiagnosis(string strProvince,int num)
{
    mapProvince[strProvince].diagnosis -= num;
    mapProvince[strProvince].death += num;
    mapProvince["ȫ��"].death += num;
}
void CureDiagnosis(string strProvince,int num)
{
    mapProvince[strProvince].diagnosis -= num;
    mapProvince[strProvince].cure += num;
    mapProvince["ȫ��"].cure += num;
}
void SuspectedToDiagnosis(string strProvince,int num)
{
    mapProvince[strProvince].suspected -= num;
    mapProvince[strProvince].diagnosis += num;
    mapProvince["ȫ��"].suspected -= num;
    mapProvince["ȫ��"].diagnosis += num;
}
void ExcludeSuspected(string strProvince,int num)
{
    mapProvince[strProvince].suspected -= num;
    mapProvince["ȫ��"].suspected -= num;
}