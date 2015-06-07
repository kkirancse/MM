#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int getbw(){
//Hard coding it for now. Assuming available bw to be 2 mbps. Ideally we should get this bw from client.
return 2;
}

/* The variable excess holds the amount of data that needs to be prefetched in order to maintain the.*/
int  main(){

fstream fp;
int fragment_size,excess,rate;
vector<int> fragments,allocation;

fp.open("streamdata.txt", ios::in | ios::binary);

if(fp.is_open()){
	while(fp >> fragment_size){
		fragments.push_back(fragment_size);
		allocation.push_back(0);
	}
}
else 
cout << "Unable to open file"; 

fp.close();

int i,n;
n=fragments.size();
rate= getbw();
for (excess=0,i=n-1;  i>=0  ;  i--){
   if (fragments[i] > rate){
      excess += (fragments[i]-rate);
      allocation[i] = rate;
   }
   else{
/* start buffering because rate constraint violated */
   		if (excess > (rate - fragments[i])){
      		allocation[i] = rate;
      		excess = excess - (rate - fragments[i]);
		}
    	else{
        	allocation[i] = fragments[i] + excess;
            	excess = 0;
	}
  }
#ifdef DEBUG
cout<<"fragment"<<i<<","<<"size : "<<fragments[i]<<","<<"bwallocated : " <<allocation[i] << "," << "excess : "<<excess <<endl;
#endif
}
cout<<"Totl buffer size :  "<<excess<<"MB"<<" startup time : "<< excess/rate <<" Seconds"<<endl;
return 0;
}
