int BinSearch(int i_array[],int x,int i_start,int i_end) 
{
	 int  i_mid; 
	 if (i_start > i_end) 
	   return -1; 
	 else{
	   i_mid = (int)((i_start + i_end)/2); 
	    if (i_array[i_mid] == x)   return(i_mid); 
		if (i_array[i_mid] > x)    return BinSearch(i_array,x, i_start, i_mid - 1); 
		  else   return BinSearch(i_array,x, i_mid + 1, i_end ); 
	 }
}

int* GetRange(int i_array[],int i,int i_end) 
{
	 int i_val,i_min,i_max; 
	 int all[2];
	 all[0]=-1;
	 all[1]=-1;
	 i_min  = i; 
	 i_max=i;
	  while (i_max<i_end) { 
	      i_val = i_max;
		  if (i_array[i] == i_array[i_val+1]) 
		   i_max = i_max + 1;  
		  else   break; 
      }
       while (i_min > 0) { 
	   i_val = i_min; 
	   if (i_array[i] == i_array[i_val-1]) 
	        i_min = i_min - 1; 
	   else    break;   
	   } 
	   all[1]=i_max;
       all[0]=i_min;
	   return all; 
}
