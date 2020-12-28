//
// Created by liyingkai on 2020/12/23.
//

#ifndef DICHOTOMY_ALGORITHM_H
#define DICHOTOMY_ALGORITHM_H
#include "people.h"
#include<iostream>
#include <math.h>
#include <fstream>
using namespace std;
struct NORMAL{
    double mu_1;
    double mu_2;
    double delta_1;
    double delta_2;
    double rho;
};
NORMAL manNormal;
NORMAL womanNormal;
ifstream input_1("man.TXT");
ifstream input_2("woman.TXT");
ifstream input_3("test.txt");
int woman_num;
int man_num;
double mu[2];
double delate[2];
/*
 * 读入样本
 */
void input(){
    woman_num=0;
    man_num=0;
    while (input_2>>woman[woman_num+1].height>>woman[woman_num+1].weight){
        woman_num++;
    }
    while (input_1>>man[man_num+1].height>>man[man_num+1].weight){
        man_num++;
    }
}
/*
 * 计算mu
 */
double *normalMu(struct HUMAN *people,int people_num){
    double mu_1=0;
    double mu_2=0;
    for(int i=1;i<=people_num;i++){
        mu_1+=people[i].height;
        mu_2+=people[i].weight;
    }
    mu_2/=people_num;
    mu_1/=people_num;
    mu[0]=mu_1;
    mu[1]=mu_2;
    return mu;
}
/*
 * 计算delta
 */
double *normalDelta(struct HUMAN *people,int people_num,double mu_1,double mu_2){
    double delate_1=0;
    double delate_2=0;
    for(int i=1;i<=people_num;i++){
        delate_1+=(people[i].height-mu_1)*(people[i].height-mu_1);
        delate_2+=(people[i].weight-mu_2)*(people[i].weight-mu_2);
    }
    delate_2/=people_num;
    delate_1/=people_num;
    delate_1=sqrt(delate_1);
    delate_2=sqrt(delate_2);
    delate[0]=delate_1;
    delate[1]=delate_2;
    return delate;
}
/*
 * 计算rho
 */
double normalRho(struct HUMAN *people,int people_num,double mu_1,double mu_2,double delate_1,double delate_2){
    double rho=0;
    for(int i=1;i<=people_num;i++){
        rho+=people[i].height*people[i].weight;
    }
    rho/=people_num;
    rho-=mu_2*mu_1;
    rho/=delate_2*delate_1;
    return rho;
}
void NormalFun(struct HUMAN *people,int people_num,struct NORMAL &peopleNormal){
    double *mu;
    double *delate;
    double rho=0;
    mu=normalMu(people,people_num);
    delate=normalDelta(people,people_num,mu[0],mu[1]);
    rho=normalRho(people,people_num,mu[0],mu[1],delate[0],delate[1]);
    peopleNormal.mu_1=mu[0];
    peopleNormal.mu_2=mu[1];
    peopleNormal.delta_1=delate[0];
    peopleNormal.delta_2=delate[1];
    peopleNormal.rho=rho;
}
/*
 * 计算条件概率
 */
double P(struct NORMAL &normal,double x1,double x2){
    double result;
    double mu1=normal.mu_1;
    double mu2=normal.mu_2;
    double delta1=normal.delta_1;
    double delta2=normal.delta_2;
    double rho=normal.rho;
    rho=0;
    result=(1/(2*pi*delta1*delta2*sqrt(1-rho*rho)))*exp(-1/(2*sqrt(1-rho*rho))*(((x1-mu1)*(x1-mu1))/(delta1*delta1)+((x2-mu2)*(x2-mu2))/(delta2*delta2)-(2*rho*(x1-mu1)*(x2-mu2))/(delta1*delta2)));
    return result;
}

/*
 * 计算后验概率
 *  judge为0为女，1为男
 */
double posteriorProbability(double x1,double x2,bool judge){
    if(judge==0){
        return (P(womanNormal,x1,x2)*p)/(P(womanNormal,x1,x2)*p+P(manNormal,x1,x2)*p);
    }
    else {
        return (P(manNormal,x1,x2)*p)/(P(womanNormal,x1,x2)*p+P(manNormal,x1,x2)*p);
    }
}
/*
 * 判断男女，0为女，1为男
 */
bool classifyCategorize(double x1,double x2){
    if(posteriorProbability(x1,x2,0)>=posteriorProbability(x1,x2,1)){
        return 0;
    }
    else {
        return 1;
    }
}
void results(){
    double heigth,weight;
    char sex;
    while (input_3>>heigth>>weight>>sex){
        if(sex=='f'&&classifyCategorize(heigth,weight)==0){
            cout<<"正确"<<endl;
        } else if(sex=='m'&&classifyCategorize(heigth,weight)==0){
            cout<<"正确"<<endl;
        } else{
            cout<<"错误"<<endl;
        }
    }
}
#endif //DICHOTOMY_ALGORITHM_H
