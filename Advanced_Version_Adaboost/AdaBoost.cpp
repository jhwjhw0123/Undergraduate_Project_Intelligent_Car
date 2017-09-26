/********************************
*@Function:To Train the Adaboost Classifier of Inteeligent Car to Judge the Mode of Tracking/Avoidance
*@Author:Chen Wang, Northwestern Polytechnical University
*@Version:1.0.0
***All Rights Reserved***
********************************/
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Speed;      //Speed Level
vector<int> Distance;   //Distance Level
vector<int> Indicate;   //Indicate Function
vector<int> Label;      //Label Indicate

int SignFunction(double data){
    if(data>0){
        return 1;
        }
    else{
        return -1;
        }
}

int GClassifier(int JFlag,double judge,double data){
    if(JFlag==0){
      if(data<judge){
          return 1;
          }
      else{
          return -1;
          }
      }
    else if(JFlag==1){
        if(data<judge){
          return -1;
          }
      else{
          return 1;
          }
        }
  }

double ClassifierError(int JFlag,double i,double weight[]){
  double Error = 0;
  int TestLabel[Label.size()];
  for(int j=0;j<Indicate.size();j++){
     TestLabel[j] = GClassifier(JFlag,i,Indicate[j]);
     if(TestLabel[j]!=Label[j]){
         Error = Error + weight[j];
         }
     }
  return Error;
}

double Alpha(double Em){
   double alpham;
   double tempAlpha = (1-Em)/Em;
   alpham = 0.5*log(tempAlpha);
   return alpham;
 }

int main(){
  int TempSpeed;
  int TempDistance;
  int TempLable;
/**************Initialize*****************/
  ifstream fin("Data.txt");
  //Read Training Data
  while(!fin.eof()){
       fin>>TempLable;
       Label.push_back(TempLable);
       fin>>TempDistance;
       Distance.push_back(TempDistance);
       fin>>TempSpeed;
       Speed.push_back(TempSpeed);
       Indicate.push_back(5*TempDistance + TempSpeed);
      }
  //Weight Array
  int wlength = Indicate.size();
  int WrongCl = 0;         //Datas been wrongly classified
  int m = 0;               //Iterate times
  int ClFlag;              //Store the value of ClFlag
  vector<int> JFlag;         //Determine the style of classifier function
  double ClValue;      //Classifier Value
  vector<double> JudgeValue;   //To store the Classifier Values
  vector<double> AlphaValue;   //To store the value of alpam
  double MinError = 0;     //Minimum Error
  double alpham = 0;      //αm
  double weight[wlength];
  double Tempweight[wlength];   //Transfer Variable using in calculating new weights
  double Sumweight;             //Normalization Factor
  double Errorm[wlength-1];
  int JudgeLabel[Label.size()];
  //Initial Value
  for(int i=0;i<wlength;i++){
      weight[i] = 1/(double)(wlength);
    }
/*****************Train*******************/
 while(1){
  m = m + 1;
  WrongCl = 0;
  ClValue = 0.5;
  alpham = 0;
  Sumweight = 0;
  memset(Tempweight,0,wlength*sizeof(double));
  for(int j=0;j<2;j++){
    for(double i=0.5;i<Indicate.size()-1;i=i+1){
        int k = (int)(i-0.5);
        Errorm[k] = ClassifierError(j,i,weight);
        if(k==0&&j==0){          //Initialize
            MinError = Errorm[0];
            }
        if(MinError>Errorm[k]){
         MinError = Errorm[k];
         ClFlag = j;
         ClValue = i;
         }
      }
   }
   JFlag.push_back(ClFlag);
   alpham = Alpha(MinError);
   JudgeValue.push_back(ClValue);
   AlphaValue.push_back(alpham);
   for(int i=0;i<wlength;i++){
      Tempweight[i] = exp(-1*alpham*Label[i]*GClassifier(ClFlag,ClValue,Indicate[i]));
      Sumweight = Sumweight + weight[i]*Tempweight[i];
       }
   for(int i=0;i<wlength;i++){
       weight[i] = weight[i]*Tempweight[i]/Sumweight;
       }
   for(int i=0;i<wlength;i++){
       double ClassifierValue = 0;
       for(int k=0;k<m;k++){
         ClassifierValue += AlphaValue[k]*GClassifier(JFlag[k],JudgeValue[k],Indicate[i]);
       }
       JudgeLabel[i] = SignFunction(ClassifierValue);
       if(JudgeLabel[i]!=Label[i]){
         WrongCl += 1;
         }
       }
   cout<<"本次迭代值：MinError:"<<MinError<<",ClValue:"<<ClValue<<",Alpha:"<<alpham\
   <<"错分数据个数:"<<WrongCl<<"二分类方式(0)小于分界为1，(1)大于分界为1: "<<ClFlag<<endl;
     if(WrongCl==0){
         cout<<"分类完成,已全部正确分类"<<endl;
         cout<<"总迭代次数"<<m<<"次"<<endl;
         break;
         }
     else if(m>30){
         cout<<"无法找到完全正确分类的分界面，以上为近似值"<<endl;
         cout<<"总迭代次数"<<m<<"次"<<endl;
         break;
         }
  }
/********Write the Data to text file*********/
  ofstream wr("Result.txt",ios::trunc);
  for(int i=0;i<m;i++){
    wr<<JFlag[i]<<" "<<JudgeValue[i]<<" "<<AlphaValue[i]<<"\n";
   }
}
