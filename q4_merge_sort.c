#include<stdio.h>
#include<stdlib.h>
int arr[100];
void merge(int left,int mid,int right){
    int i=left,j=mid+1,k=left;
    int temp[100];
    while(i<=mid && j<=right){
        if (arr[i]<=arr[j]){
            temp[k++]=arr[i++];
        }
        else{
            temp[k++]=arr[j++];
        }
    }
    while(i<=mid){
        temp[k++]=arr[i++];
    }
    while(j<=right){
        temp[k++]=arr[j++];
    }
    for (int i=left;i<=right;i++){
        arr[i]=temp[i];
    }
    
}void mergesort(int left,int right){
    if(left>=right){
        return;
    }
    int mid=(left+right)/2;
    mergesort(left,mid);
    mergesort(mid+1,right);
    merge(left,mid,right);
}
int main(){
     int n, i;

    printf("Enter size: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergesort(0, n - 1);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}