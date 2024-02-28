#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define iter 100

typedef struct{
    double coef,yDericativeCoef,yCoef;
    int exp;
}inputFunction;

void polynomTake(int n,inputFunction* input0);
double polynomAnswer(double x,double y,int n,inputFunction* input0);
void polynomWrite(int n,inputFunction* input0);
void rungeKutta(int n,inputFunction* input0,double h,double targetValue,double x0,double y0,double absoluteError);

int main()
{
    int n,i;
    double h,x0,y0,targetValue,absoluteError;
    printf("Please enter number of input polynomial  parts : ");
    scanf("%d",&n);
    inputFunction* arrFunctions;
    arrFunctions = (inputFunction*)calloc(n, sizeof(inputFunction));
    if (arrFunctions == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    printf("Please enter h value :");
    scanf("%lf",&h);
    printf("Please enter target value :");
    scanf("%lf",&targetValue);
    printf("Please enter x0 value :");
    scanf("%lf",&x0);
    printf("Please enter y0 value :");
    scanf("%lf",&y0);
    printf("Please enter real value for absolute error ");
    scanf("%lf",absoluteError);
    polynomTake(n,arrFunctions);
    polynomWrite(n,arrFunctions);
    rungeKutta(n,arrFunctions,h,targetValue,x0,y0,absoluteError);
    free(arrFunctions);

    return 0;
}
void rungeKutta(int n,inputFunction* input0,double h,double targetValue,double x0,double y0,double absoluteError){
    double k1,k2,k3,k4,result,absoluteError2,absoluteError3;
    int i=1,flag=1;
    while(i<iter && flag == 1){
        k1 = polynomAnswer(x0,y0, n, input0);

        k2 = polynomAnswer(x0 + (h / 2),(y0 + (k1*h / 2)), n, input0);

        k3 = polynomAnswer(x0 + (h / 2),(y0 + (k2*h / 2)), n, input0);

        k4 =  polynomAnswer(x0 + h,(y0 + (k3*h)), n, input0);


        result = y0 + h*(k1+2*k2+2*k3+k4)/6;

        if(x0+h == targetValue){
            flag = 0;
        }
        printf("Iteration : %d Result : %lf\n",i,result);
        if(flag==0 || i==iter){
            absoluteError3 = absoluteError-result;
            if(absoluteError3<0){
                absoluteError2 =  -1*(absoluteError3 / pow(2,i));
            }else{
                absoluteError2 =  absoluteError3 / pow(2,i);
            }

            printf("Absolute Error : %lf",absoluteError2);
        }
        x0 +=h;
        y0= result;
        i++;
    }
}

void polynomTake(int n,inputFunction* input0){
    int i=0;
    printf("Please enter your function in this format : y' + y = P(x) \n");
    printf("Polynom's yDerivative coefficient : ");
    scanf("%lf",&(input0+i)->yDericativeCoef);
    printf("Polynom's y coefficient: ");
    scanf("%lf",&(input0+i)->yCoef);
    for(i=0;i<n;i++){
        printf("%d. Polynom's coefficient : ",i+1);
        scanf("%lf",&(input0+i)->coef);
        printf("%d. Polynom's exponent : ",i+1);
        scanf("%d",&(input0+i)->exp);
    }
}

void polynomWrite(int n,inputFunction* input0){
    int i=0;
    printf("%.1lfy' + %.1lfy = ", (input0 + i)->yDericativeCoef, (input0 + i)->yCoef);
    for(i=0;i<n;i++){
         printf("+(%.1lfx^%d)", (input0 + i)->coef, (input0 + i)->exp);
    }
    printf("\n");
 }

double polynomAnswer(double x,double y,int n,inputFunction* input0){
    int i;
    double result=0;
    for(i=0;i<n;i++){
        result += ((input0+i)->coef)*pow(x,(input0+i)->exp);
    }
    result -= input0->yCoef * y;
    result /= input0->yDericativeCoef;
    return result;
}

