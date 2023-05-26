#include<math.h>
#include <stdio.h>
#include<stdlib.h>
#define SIZE 100
typedef struct iris_data
{
    float Sepal_length;
    float Sepal_width;
    float Petal_length;
    float Petal_width;
}ID;
ID set[50],versi[50],virgi[50],user;
void Min(float av_set,float av_versi,float av_virgi,char *ans);
void Euclidean(char *ans);
void Manhattan(char *ans);
void Cosine(char *ans);
void Mahalanobis(char *ans);
void Chi_square(char *ans);
float mahal(ID []);
float comp(float[3][3]);
void min(char ans);
void check(int *choice);
int main()
{
    float ACC[5];
    char ch[3]={'s','v','V'};
    char ans;
    int TP=0,TN=0,FP=0,FN=0;
    int i=0,z,A,B,choice;
    FILE *p=fopen("iris data.txt","r");
    for( i=0;i<50;i++)//......................file read
    {
        fscanf(p,"%f%f%f%f",&set[i].Sepal_length,&set[i].Sepal_width,&set[i].Petal_length,&set[i].Petal_width);
    }
    for(i=0;i<50;i++)
    {
        fscanf(p,"%f%f%f%f",&versi[i].Sepal_length,&versi[i].Sepal_width,&versi[i].Petal_length,&versi[i].Petal_width);
    }
    for(i=0;i<50;i++)
    {
        fscanf(p,"%f%f%f%f",&virgi[i].Sepal_length,&virgi[i].Sepal_width,&virgi[i].Petal_length,&virgi[i].Petal_width);
    }
    i=0;
    printf("DISPLAYING ACCURACY OF METHODS\n");
    p=fopen("sample","r");
    while(i<5)
    {
        for(A=0;A<3;A++)
        {
            for(B=0;B<20;B++)
            {
                fscanf(p,"%f%f%f%f",&user.Sepal_length,&user.Sepal_width,&user.Petal_length,&user.Petal_width);
                switch(i)
                {
                    case 0:Euclidean(&ans);
                            break;
                    case 1:Manhattan(&ans);
                            break;
                    case 2:Cosine(&ans);
                            break;
                    case 3:Mahalanobis(&ans);
                            break;
                    case 4:Chi_square(&ans);
                            break;
                }
                if(B<=10)
                {
                    if(ans==ch[A])
                        TP++;
                    else
                        FP++;
                }
                else
                {
                    if(ans!=ch[A])
                        TN++;
                    else
                        FN++;
                }
            }
        }
        ACC[i]=(TP+TN)*100/(TP+TN+FN+FP);
        printf("for %d\nTP=%dTN=%dFP=%dFN=%d\n",i,TP,TN,FP,FN);
        i++;
        TP=TN=FP=FN=0;
        fseek(p,0,SEEK_SET);
    }
    printf("EUCLIDEAN ACCURACY=%f\n",ACC[0]);
    printf("MANHATTAN ACCURACY=%f\n",ACC[1]);
    printf("COSINE ACCURACY=%f\n",ACC[2]);
    printf("MAHALANOBIS ACCURACY=%f\n",ACC[3]);
    printf("CHI-SQUARE ACCURACY=%f\n",ACC[4]);
    printf("\n*************************************************************************************************************\n");
    printf("CHOOSE ANY ONE OF THE BELOW!!!!\n");
    for(;;)
    {
        printf("1.EUCLIDEAN\n2.MANHATTAN\n3.COSINE\n4.MAHALANOBIS\n5.CHI-SQUARE\n6.EXIT\n");
        scanf("%d",&choice);
        printf("ENTER SEPAL LENGTH(1-10)\n");
        scanf("%f",&user.Sepal_length);
        printf("ENTER SEPAL WIDTH(1-10)\n");
        scanf("%f",&user.Sepal_width);
        printf("ENTER PETAL LENGTH(1-10)\n");
        scanf("%f",&user.Petal_length);
        printf("ENTER PETAL WIDTH(1-10)\n");
        scanf("%f",&user.Petal_width);
        check(&choice);
        switch(choice)
        {
            case 0:break;
            case 1:printf("ACCORDING TO EUCLIDEAN........\n\a");
                    Euclidean(&ans);
                    min(ans);
                    break;
            case 2:printf("ACCORDING TO MANHATTAN.........\n\a");
                   Manhattan(&ans);
                   min(ans);
                   break;
            case 3:printf("ACCORDING TO COSINE.........\n\a");
                    Cosine(&ans);
                    min(ans);
                    break;
            case 4: printf("ACCORDING TO MAHALANOBIS...........\n\a");
                    Mahalanobis(&ans);
                    min(ans);
                    break;
            case 5:printf("ACCORDING TO CHI-SQUARE..........\n\a");
                    Chi_square(&ans);
                    min(ans);
                    break;
            case 6:exit(0);
            default:printf("NOT A VALID CHOICE\n");
        }
        printf("\n*************************************************************************************************************\n");
    }
}

//--------------------------------------------------------------------->EUCLIDIAN<----------------------------------------------------------------
void Euclidean(char *ans)
{
    float l,m,n,q,sum1=0,sum2=0,sum3=0,av_set,av_versi,av_virgi;
    int i=0;
    for(i=0;i<50;i++)
    {
        l=sqrt(pow((set[i].Sepal_length-user.Sepal_length),2)+pow((set[i].Sepal_width-user.Sepal_width),2)+pow((set[i].Petal_length-user.Petal_length),2)+pow((set[i].Petal_width-user.Petal_width),2));
        sum1=sum1+l;
        m=sqrt(pow((versi[i].Sepal_length-user.Sepal_length),2)+pow((versi[i].Sepal_width-user.Sepal_width),2)+pow((versi[i].Petal_length-user.Petal_length),2)+pow((versi[i].Petal_width-user.Petal_width),2));
        sum2=sum2+m;
        n=sqrt(pow((virgi[i].Sepal_length-user.Sepal_length),2)+pow((virgi[i].Sepal_width-user.Sepal_width),2)+pow((virgi[i].Petal_length-user.Petal_length),2)+pow((virgi[i].Petal_width-user.Petal_width),2));
        sum3=sum3+n;
    }
    av_set=sum1/50;
    av_versi=sum2/50;
    av_virgi=sum3/50;
    Min(av_set,av_versi,av_virgi,ans);
}
//--------------------------------------------------------------------->MANHATTAN<---------------------------------------------------
void Manhattan(char *ans)
{
    float l,m,n,q,sum1=0,sum2=0,sum3=0,av_set,av_versi,av_virgi;
    int i;
    for(i=0;i<50;i++)
    {
        l=fabs(set[i].Sepal_length-user.Sepal_length)+fabs(set[i].Sepal_width-user.Sepal_width)+fabs(set[i].Petal_length-user.Petal_length)+fabs(set[i].Petal_width-user.Petal_width);
        sum1=sum1+l;
        m=fabs(versi[i].Sepal_length-user.Sepal_length)+fabs(versi[i].Sepal_width-user.Sepal_width)+fabs(versi[i].Petal_length-user.Petal_length)+fabs(versi[i].Petal_width-user.Petal_width);
        sum2=sum2+m;
        n=fabs(virgi[i].Sepal_length-user.Sepal_length)+fabs(virgi[i].Sepal_width-user.Sepal_width)+fabs(virgi[i].Petal_length-user.Petal_length)+fabs(virgi[i].Petal_width-user.Petal_width);
        sum3=sum3+n;
    }
    av_set=sum1/50;
    av_versi=sum2/50;
    av_virgi=sum3/50;
    Min(av_set,av_versi,av_virgi,ans);
}
//-------------------------------------------------------------------->COSINE<-----------------------------------------------------------------
void Cosine(char *ans)
{
    float l,m,n,q,sum1=0,sum2=0,sum3=0,av_set,av_versi,av_virgi;
    int i;
    for(i=0;i<50;i++)
    {
        l=(set[i].Sepal_length*user.Sepal_length+set[i].Sepal_width*user.Sepal_width+set[i].Petal_length*user.Petal_length+set[i].Petal_width*user.Petal_width);
        l=l/((sqrt(pow(set[i].Sepal_length,2)+pow(set[i].Sepal_width,2)+pow(set[i].Petal_length,2)+pow(set[i].Petal_width,2)))*(sqrt(pow(user.Sepal_length,2)+pow(user.Sepal_width,2)+pow(user.Petal_length,2)+pow(user.Petal_width,2))));
        sum1=sum1+l;
        m=(versi[i].Sepal_length*user.Sepal_length+versi[i].Sepal_width*user.Sepal_width+versi[i].Petal_length*user.Petal_length+versi[i].Petal_width*user.Petal_width);
        m=m/((sqrt(pow(versi[i].Sepal_length,2)+pow(versi[i].Sepal_width,2)+pow(versi[i].Petal_length,2)+pow(versi[i].Petal_width,2)))*(sqrt(pow(user.Sepal_length,2)+pow(user.Sepal_width,2)+pow(user.Petal_length,2)+pow(user.Petal_width,2))));
        sum2=sum2+m;
        n=(virgi[i].Sepal_length*user.Sepal_length+virgi[i].Sepal_width*user.Sepal_width+virgi[i].Petal_length*user.Petal_length+virgi[i].Petal_width*user.Petal_width);
        n=n/((sqrt(pow(virgi[i].Sepal_length,2)+pow(virgi[i].Sepal_width,2)+pow(virgi[i].Petal_length,2)+pow(virgi[i].Petal_width,2)))*(sqrt(pow(user.Sepal_length,2)+pow(user.Sepal_width,2)+pow(user.Petal_length,2)+pow(user.Petal_width,2))));
        sum3=sum3+n;
        
    }
    av_set=0;
    av_versi=0;
    av_virgi=0;
    av_set=sum1/50;
    av_versi=sum2/50;
    av_virgi=sum3/50;
    av_set=1-av_set;
    av_versi=1-av_versi;
    av_virgi=1-av_virgi;
    Min(av_set,av_versi,av_virgi,ans);
}
//--------------------------------------------------------------------->MAHALANOBIS<-----------------------------------------------------------------
void Mahalanobis(char *ans)
{
    float l,m,n,q,sum1=0,sum2=0,sum3=0,av_set,av_versi,av_virgi;
    int i;
    av_set=mahal(set);//----->function call to find inverse of covariance and computation of formula
    av_versi=mahal(versi);
    av_virgi=mahal(virgi);
    Min(av_set,av_versi,av_virgi,ans);
}
//----------------------------------------------------------------->CHI-SQUARE<------------------------------------------------------------------
void Chi_square(char *ans)
{
    float l,m,n,q,sum1=0,sum2=0,sum3=0,av_set,av_versi,av_virgi;
    int i;
    for(i=0;i<50;i++)
    {
        l=pow((set[i].Sepal_length-user.Sepal_length),2)/(set[i].Sepal_length+user.Sepal_length)+pow((set[i].Sepal_width-user.Sepal_width),2)/(set[i].Sepal_width+user.Sepal_width)+pow((set[i].Petal_length-user.Petal_length),2)/(set[i].Petal_length+user.Petal_length)+pow((set[i].Petal_width-user.Petal_width),2)/(set[i].Petal_width+user.Petal_width);
        sum1=sum1+l;
       
        m=pow((versi[i].Sepal_length-user.Sepal_length),2)/(versi[i].Sepal_length+user.Sepal_length)+pow((versi[i].Sepal_width-user.Sepal_width),2)/(versi[i].Sepal_width+user.Sepal_width)+pow((versi[i].Petal_length-user.Petal_length),2)/(versi[i].Petal_length+user.Petal_length)+pow((versi[i].Petal_width-user.Petal_width),2)/(versi[i].Petal_width+user.Petal_width);
        sum2=sum2+m;
       
        n=pow((virgi[i].Sepal_length-user.Sepal_length),2)/(virgi[i].Sepal_length+user.Sepal_length)+pow((virgi[i].Sepal_width-user.Sepal_width),2)/(virgi[i].Sepal_width+user.Sepal_width)+pow((virgi[i].Petal_length-user.Petal_length),2)/(virgi[i].Petal_length+user.Petal_length)+pow((virgi[i].Petal_width-user.Petal_width),2)/(virgi[i].Petal_width+user.Petal_width);
        sum3=sum3+n;
    }
    av_set=sum1/50;
    av_versi=sum2/50;
    av_virgi=sum3/50;
    Min(av_set,av_versi,av_virgi,ans);
}
//------------------------------------------------------------------------->USER DEFINED FUNCTIONS<--------------------------------------------------------
float mahal(ID s[])
{
    float x[4][4],U[4][4],S[4][4],COV[4][4],mat[3][3],TS[4][4],ADJ[4][4],c[4][4],b[2][2];
    float sum1=0,sum2=0,sum3=0,sum4=0,av=0,av1=0,ip;
    int r=0,l,m,n,q=0,k,i,j;
    for(i=0;i<50;i++)
    {
        sum1=sum1+s[i].Sepal_length;
        sum2=sum2+s[i].Sepal_width;
        sum3=sum3+s[i].Petal_length;
        sum4=sum4+s[i].Petal_width;
    }
    x[0][0]=sum1=sum1/50;
    x[1][0]=sum2=sum2/50;
    x[2][0]=sum3=sum3/50;
    x[3][0]=sum4=sum4/50;
    U[0][0]=user.Sepal_length;
    U[1][0]=user.Sepal_width;
    U[2][0]=user.Petal_length;
    U[3][0]=user.Petal_width;
    for(i=0;i<4;i++)
   {
       for(j=0;j<1;j++)
       {
           S[i][j]=U[i][j]-x[i][j];// finding (x-U)
       }
   }
   for(i=0;i<4;i++)
   {
       for(j=0;j<1;j++)
       {
           TS[j][i]=S[i][j];// computing(x-U)^T--->transpose of (x-U)
       }
   }
    for(i=0;i<4;i++)//..... finding covariance
    {
        for(j=0;j<4;j++)
        {
            
            if(i==j)
            {
                COV[i][j]=0;
                for(k=0;k<50;k++)
                {
                    if(i==0)
                        COV[i][j]=COV[i][j]+pow((s[k].Sepal_length-sum1),2);
                    else if(i==1)
                        COV[i][j]=COV[i][j]+pow((s[k].Sepal_width-sum2),2);
                     else if(i==2)
                        COV[i][j]=COV[i][j]+pow((s[k].Petal_length-sum3),2);
                    else
                        COV[i][j]=COV[i][j]+pow((s[k].Petal_width-sum4),2);
                }
                COV[i][j]=COV[i][j]/50;
            }
            else if(i>j)
            {
                continue;
            }
            else
            {
                if(i==0)
                {
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Sepal_length-sum1)*(s[i].Sepal_width-sum2);
                    }
                    COV[i][j]=COV[i][j]/50;
                    COV[j][i]=COV[i][j];
                    j++;
                    COV[i][j]=0;
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Sepal_length-sum1)*(s[i].Petal_length-sum3);
                    }
                    COV[i][j]=COV[i][j]/50;
                    COV[j][i]=COV[i][j];
                    j++;
                    COV[i][j]=0;
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Sepal_length-sum1)*(s[i].Petal_width-sum4);
                    }
                    COV[i][j]=COV[i][j]/50;
                    COV[j][i]=COV[i][j];
                }
                else if(i==1)
                {
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Sepal_width-sum2)*(s[i].Petal_length-sum3);
                    }
                    COV[i][j]=COV[i][j]/50;
                    COV[j][i]=COV[i][j];
                    j++;
                    COV[i][j]=0;
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Sepal_width-sum2)*(s[i].Petal_width-sum4);
                    }
                    COV[i][j]=COV[i][j]/50;
                    COV[j][i]=COV[i][j];
                }
                else
                {
                    for(l=0;l<50;l++)
                    {
                        COV[i][j]=COV[i][j]+(s[i].Petal_length-sum3)*(s[i].Petal_width-sum4);
                    }
                    COV[j][i]=COV[i][j];
                }
                    
            }
        }
    }
    l=0;
    k=0;
    for(i=0;i<1;i++)//....... finding magnitude of covariance matrix
    {
        for(j=0;j<4;j++)
        {
            ip=COV[i][j];
            r=0;
            for(m=0;m<4;m++)
            {
                q=0;
                for(n=0;n<4;n++)
                {
                    if(m==i||n==j)
                    {
                        continue;
                    }
                    else
                    {
                        mat[r][q]=COV[m][n];
                        q++;
                        if(q==3)
                        {
                            q=0;
                            r++;
                        }
                    }
                }
            }
            if(j%2==0)
                av=av+ip*comp(mat);
            else
                av=av-ip*comp(mat);
        }
    }
    av1=0;
    l=0;
    k=0;
    for(i=0;i<4;i++)//....... finding adjoint of covariance matrix
    {
        for(j=0;j<4;j++)
        {
            ip=COV[i][j];
            r=0;
            for(m=0;m<4;m++)
            {
                q=0;
                for(n=0;n<4;n++)
                {
                    if(m==i||n==j)
                    {
                        continue;
                    }
                    else
                    {
                        mat[r][q]=COV[m][n];
                        q++;
                        if(q==3)
                        {
                            q=0;
                            r++;
                        }
                    }
                }
            }
            av1=comp(mat);
        
            if((l+k)%2!=0)
            {
                ADJ[l][k]=-av1;
                k++;
            }
            else
            {
                ADJ[l][k]=av1;
                k++;
            }
        }
        k=0;
        l++;
        
    }
    for(i=0;i<4;i++)//.....finding inverse of covariance matrix
    {
        for(j=0;j<4;j++)
        {
            ADJ[i][j]=ADJ[i][j]/av;
        }
    }
    for(i=0;i<1;i++)//.... computing mahalanobis formula
    {
        for(j=0;j<4;j++)
        {
            k=0;
            c[i][j]=0;
            while(k<4)
            {
                c[i][j]=c[i][j]+TS[i][k]*ADJ[k][j];
                k++;
            }
        }
    }
    for(i=0;i<1;i++)
    {
        for(j=0;j<1;j++)
        {
            b[i][j]=0;
            for(k=0;k<4;k++)
            {
                b[i][j]=b[i][j]+c[i][k]*S[k][j];
            }
        }
    }
    return(sqrt(fabs(b[0][0])));
}
float comp(float mat[][3])
{
    int m,n,p=0,q=0,i,j;
    float matrix[2][2],ip,av=0,sum1,sum2;
    for(m=0;m<1;m++)
    {
        for(n=0;n<3;n++)
        {
            ip=mat[m][n];
            p=0;
            for(i=0;i<3;i++)
            {
                q=0;
                for(j=0;j<3;j++)
                {
                    if(i==m||j==n)
                    {
                        continue;
                    }
                    else
                    {
                        matrix[p][q]=mat[i][j];
                        q++;
                        if(q==2)
                        {
                            q=0;
                            p++;
                        }
                    }
                }
            }
            sum1=1;
            sum2=1;
            for(i=0;i<2;i++)
            {
                for(j=0;j<2;j++)
                {
                    if(i==j)
                    {
                        sum1=sum1*matrix[i][j];
                    }
                    else
                    {
                        sum2=sum2*matrix[i][j];
                    }
                }
            }
            if(n%2==0)
                av=av+ip*(sum1-sum2);
            else
                av=av-ip*(sum1-sum2);
        }
    }
    return av;
}
void min(char ans)
{
        if(ans=='s')
            printf("FLOWER BELONGS TO SETOSA\n");
        else if(ans=='v')
            printf("FLOWER BELONGS TO VERSICOLOUR\n");
        else
            printf("FLOWER BELONGS TO VIRGINICA\n");
}
void Min(float av_set,float av_versi,float av_virgi,char *ans)
{
    if(av_set<av_versi)
    {
        if(av_set<av_virgi)
            *ans='s';
        else
            *ans='V';
    }
    else
    {
        if(av_versi<av_virgi)
            *ans='v';
        else
            *ans='V';
    }
    /*if(av_set<av_versi)
    {
        if(av_set<av_virgi)
            *ans='s';
        else
        {
            if((av_versi-av_virgi)>=0.1&&(av_versi-av_virgi)<0.25)
                *ans='v';
            else
                *ans='V';
        }
    }
    else
    {
        if(av_versi<av_virgi)
        {
                *ans='v';
        }
            
        else
        {
            if((av_versi-av_virgi)>=0.1&&(av_versi-av_virgi)<0.25)
                *ans='v';
            else
                *ans='V';
        }
    }*/
   
}
void check(int *choice)
{
    if(user.Sepal_length>10||user.Sepal_width>10||user.Petal_length>10||user.Petal_width>10)
    {
        printf("DATA IS OUTLIER\n");
        *choice=0;
    }
}

/*
********************************************************FORMULAE*******************************************
1) EUCLIDEAN-->sqrt[(w1-w2)^2+(x1-x2)^2+(y1-y2)^2+(z1-z2)^2]
2)MANHATTAN---->|(w1-w2)|+|(x1-x2)|+|(y1-y2)|+|(z1-z2)|
3)COSINE------->[w1*w2 + x1*x2 + y1*y2+ z1*z2 ]/[sqrt((w1)^2 + (x1)^2 + (y1)^2 + (z1)^2 )*sqrt((w2)^2 + (x2)^2 + (y2)^2 + (z2)^2 )]
4)MAHALANOBIS--->[sqrt(matrix{data-user}*matrix{data-user}^T*(covariance of data)^-1)]
5)CHI-SQUARE----->[(w1-w2)^2/(w1+w2)+(x1-x2)^2/(x1+x2)+(y1-y2)^2/(y1+y2)+(z1-z2)^2/(z1+z2)]
where,  w1,x1,y1,z1 are available data
        w2,x2,y2,z2 are user data*/
 



