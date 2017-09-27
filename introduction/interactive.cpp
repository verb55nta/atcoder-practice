#include<iostream>
#include<vector>
#include<random>

#define DEBUG

#ifdef DEBUG

std::vector<int> sample_26(26);
#define DPRINT(x) do{											\
		std::cerr << "DPRINT:"  << x << std::endl ;} while(0)
#else
#define DPRINT(x)
#endif

using namespace std;
#ifdef DEBUG
void sample_init(){
	mt19937 mt;
	mt.seed(4);
	for(int i=0;i<26;i++){
		sample_26[i] = (unsigned int)mt() / 65536 / 256;
		cout << sample_26[i] << " ";
	}
	cout << endl;	
}
char query(int c1,int c2){
	static int query=0;
	query++;
	if ( query > 1000){
		abort();
	}
	DPRINT("query:" << query);
	DPRINT("c1,c2:" << (char)(c1+'A') << "," << (char)(c2+'A'));	
	if(sample_26[c1] > sample_26[c2]){
		DPRINT('>');
		return '>';
	}
	else{
		DPRINT('<');		
		return '<';
	}

}
#else
void sample_init(){

}
char query(int c1,int c2){
	char ret;
	cout << "? " << (char)(c1+'A') << " " << (char)(c2+'A') << endl;
	cin >> ret;
	return ret;
}
#endif

void sort_two(string& s,int a,int b){
	char ret=query(a,b);
	if(ret == '>'){
		DPRINT("swap!");
		swap(s[a],s[b]);
		DPRINT(s);
	}
}

void sort_three(string& s){
	sort_two(s,2,3);
	sort_two(s,2,4);
	sort_two(s,3,4);	
}

void sort_five(string& s){
	char ret;
	string answer;
	sort_two(s,0,1);
	sort_three(s);	
	DPRINT("s:"<<s);

	string s2={s[0],s[1]};
	string s3={s[2],s[3],s[4]};
	DPRINT("s2:"<<s2);
	DPRINT("s3:"<<s3);

	answer+=s2;
	DPRINT(answer);
	/*
	ret=query(s[0]-'A',s[2]-'A');
	DPRINT(s[0] << ret << s[2]);	
	if(ret == '>'){
		answer.insert(answer.begin(),s[2]);
		DPRINT(answer);
	}
	else{
		answer.insert(answer.begin()+1,s[2]);
		DPRINT(answer);
	}
	*/
	
}

void sort_in_range(string& s,int start,int end){

	DPRINT(s);
	DPRINT("start:"<<start);
	DPRINT("end:"<<end);
	
	if(start >= end) return;
	if(end - start <=1){
		char ret;
		ret = query(s[start]-'A',s[end]-'A');
		if(ret == '>'){
			swap(s[start],s[end]);
		}
		return;
	}

	int to_swap;
	int next_start,next_end;
	int piv=(start+end)/2;

	DPRINT("piv:"<<piv);

	int left_i=start;
	int right_j=end;
	char ret;

	while(left_i < right_j){
		if(left_i > piv) left_i=piv;
		if(right_j < piv) right_j=piv;		
		DPRINT("left_i:" << left_i << "right_j:" << right_j);
		DPRINT("searchng from left...");

		for(int i=left_i;i<piv;i++,left_i=i){		
			ret=query(s[i]-'A',s[piv]-'A');

			if(ret == '>'){
				DPRINT("detect!");

				break;
			}
		}
		
		if(left_i == s[piv]-'A'){
			DPRINT("left_i reaches piv!");
		}
		
		DPRINT("searchng from right...");		

		for(int j=right_j;j>piv;j--,right_j=j){		
			ret=query(s[j]-'A',s[piv]-'A');

			if(ret == '<'){
				DPRINT("detect!");				

				break;
			}			
		}
		
		if(right_j == s[piv]-'A'){
			DPRINT("right_j reaches piv!");
		}
		
		if(left_i >= right_j){
			DPRINT("left is over right!");
			break;
		}

		else{
			if(left_i == piv){
				DPRINT("swap piv!");
				swap(s[left_i],s[right_j]);
				DPRINT("swap piv " << (char)(s[left_i]) << " and " << (char)(s[right_j]));								
				piv=right_j;
				DPRINT("now piv is " << (char)(s[piv]));
				left_i++;
			}
			else if(right_j == piv){
				DPRINT("swap piv!");
				DPRINT("swap " << (char)(s[left_i]) << " and piv " << (char)(s[right_j]));								
				swap(s[left_i],s[right_j]);
				piv=left_i;
				DPRINT("now piv is " << (char)(s[piv]));				
				right_j--;
			}
			else{
				DPRINT("swap " << (char)(s[left_i]) << " and " << (char)(s[right_j]));				
				swap(s[left_i],s[right_j]);
				left_i++;
				right_j--;			
			}
		}
		DPRINT(s);					
	}
	DPRINT("current piv is over!");
	sort_in_range(s,start,piv-1);
	sort_in_range(s,piv+1,end);	
}

int main(void){
	sample_init();
	int N,Q;
	DPRINT("Hello World");
	cin >> N >> Q;
	string fa;

	for(int i=0;i<N;i++) fa+='A'+i;
	DPRINT(fa);
	if(N==26){
		sort_in_range(fa,0,N-1);
	}
	else if(N==5){
		sort_five(fa);
	}
	
	DPRINT(fa);
	cout << "! " << fa << endl;
  
  
	return 0;

}
