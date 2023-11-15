#include <iostream>
 
int* HeapSort (int data[],int length)
{
	if (data == NULL || length <= 0)
		return data;
	for (int i=length/2-1; i>=0; --i) {
		int k=i;
	    int tmp = data[k];
		int j=2*k+1;
		while (j<length) {
		if (j+1<length && data[j]>data[j+1]) 
			++j;
		if (tmp < data[j])
			break;
		data[k] = data[j]; 
		k = j; 
		j = 2*k+1;
		}
		data[k] = tmp;
	}
 
	for (int i=length-1; i>=0; --i) {
		std::swap(data[0], data[i]);
		int length=i;
		int k=0;
		int tmp = data[k];
		int j=2*k+1;
		while (j<length) {
		if (j+1<length && data[j]>data[j+1])
			++j;
		if (tmp < data[j])
			break;
		data[k] = data[j];
		k = j; 
		j = 2*k+1;
		}
		data[k] = tmp;
	}
 
	return data;
}
