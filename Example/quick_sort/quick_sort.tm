:Begin:
:Function:	sort
:Pattern:	sort[arr_List]
:Arguments:	{arr}
:ArgumentTypes:	{IntegerList}
:ReturnType:	Manual
:End:
#include<wstp.h>
static void swap(int *a,int *b)
{
	int c;
	c=*a;*a=*b;*b=c;
}
void quick_sort(int *arr,  int size)
{
      int bench,benchindex,benchindex_1=0,benchindex_2=size-1;
              if(size>=2){
				    swap(arr,arr+(size>>1));
                     benchindex=0;bench=*arr;
                      for(int index=1;index<size;index++){
                                  if(arr[index]<bench){
                                           swap(arr+index,arr+benchindex++);
                                           if(index!=benchindex)
                                               swap(arr+index,arr+benchindex); }
                      }
                      for(int i=benchindex-1;i>=0;i--){
                          if(arr[i]!=bench){
                              benchindex_1=i+1;
                              break; }
                      }
                      for(int i=benchindex+1;i<size;i++){
                                     if(arr[i]!=bench) {
                                            benchindex_2=i;
                                            break;}
                      }
                      quick_sort(arr,benchindex_1);
                      quick_sort(arr+benchindex_2,size-benchindex_2);
              }
}
void sort(int *arr,long size)
{
    quick_sort(arr,size);
    WSPutInteger32List(stdlink,arr,size);
}
int main(int argc, char *argv[])
{ 
    return WSMain(argc, argv); 
}