#include<stdio.h>
void main()
{
 int n,x[100],y[100],i;
 float xpred, ypred, xbar, ybar, tx=0, ty=0,p=0,q=0,r=0,z=0,f=0,g=0,b1=0,b0=0;
 printf("Enter no. of Co-ordinates: ");
 scanf("%d",&n);
 printf("Enter Co-ordinates:\n");
 for(i=0;i<n;i++)
 {
  scanf("%d %d",&x[i],&y[i]);
 }
 printf("Value of X=");
 scanf("%f",&xpred);
 for(i=0;i<n;i++)
 {
  tx=tx+x[i];
  ty=ty+y[i];
 }
 xbar=tx/n;
 ybar=ty/n;
 for(i=0;i<n;i++)
 {
  p=x[i]-xbar;
  q=y[i]-ybar;
  r=p*q;
  z=z+r;
  g=p*p;
  f=f+g;
  b1=z/f;
  //printf("Value of b1=%f\n",b1);
  //v=b1*xbar;
  b0=ybar-b1*xbar;
  ypred=b0+b1*xpred;
 }
 //printf("%f\n",b1);
 //printf("%f\n",b0);
 printf("Predicted value of y when x=%f is %f", xpred, ypred);
}
