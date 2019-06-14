
unsigned short int Output[7];//七个输出为1的情况（用于七段线）。short int是16位整数，刚好可以表示16种输入
unsigned int exp2[16] = {1,2,4,8, 16,32,64,128, 256,512,1024,2048, 4096,8192,16384,32768};
bool Results[128];//七个输出的所有线性组合的结果
unsigned short Dubious = 0;//表示输出随意的情况。用bool数组也许更方便
bool lampValue[32][16];//lampValue[lamp][input]表示灯上接线为lamp，输入为input时该灯的值。lamp包含一位取反和四位接线

unsigned short int getCombination(unsigned int comb){//例如getCombination(0b1)=Output[0]，getCombination(0b1011)=Output[3]^Output[1]^Output[0]
	ret = 0;
	comb = (unsigned short int) comb;
	for(int i=0;i<7;i++){
		ret ^= comb & exp2[i] ? Output[i] : 0;
	}
	return ret;
}

int leastLamps(unsigned short output){//达到某种输出最少需要多少个灯。暂时认为该答案不会超过4。
	if(try0(output)) return 0;
	if(try1(output)) return 1;
	if(try2(output)) return 2;
	if(try3XOR(output)) return 3;
	if(try3AND(output)) return 3;
	return 4;
}

bool try0(unsigned short output){//无灯是否可解
	return output | Dubious == 65535 || output & Dubious == 0;
}

bool try1(unsigned short output){//单灯是否可解
	flag1 = false;
	flag2 = false;
	for(int lamp1=1;lamp1<32;lamp1++){
		if(lamp1 == 16) continue;
		for(int input=0;input<16;input++){
			if(Dubious & exp2[input]) continue;
			if(lampValue[lamp1][input] != (output & exp2[input] != 0)) flag2 = true;
			else flag1 = true;
			if(flag1 & flag2) break;
		}
		if(flag1 & flag2) continue;
		else return true;
	}
	return false;
}

bool try2(unsigned short output){//双灯是否可解
	bool lampFail01[32];//lampValue为0但是output为1
	bool lampFail10[32];//lampValue为1但是output为0
	for(int lamp=1;lamp<32;lamp++){
		lampFail01[lamp] = false;
		lampFail10[lamp] = false;
		for(int input=0;input<16;input++){
			if(Dubious & exp2[input]) continue;
			if(lampValue[lamp][input] == 0 && output & exp2[input]) lampFail01[lamp] = true;
			else if(lampValue[lamp][input] && output & exp2[input] == 0) lampFail10[lamp] = true;
		}
	}
	lampFail01[16] = lampFail10[16] = true; //不遍历lamp=16的情况
	bool flag1 = false;
	for(int lamp1=1;lamp1<32;lamp1++){//不取反可以得到结果
		if(lampFail01[lamp1]) continue;
		for(int lamp2=1;lamp2<32;lamp2++){
			if(lampFail01[lamp2]) continue;
			flag1=true;
			for(int input=0;input<16;input++){
				if(Dubious & exp2[input]) continue;
				if((output & exp2[input] != 0) != (lampValue[lamp1][input] && lampValue[lamp2][input])){
					flag1 = false;
					break;
				}
			}
			if(flag1) return true;
		}
	}
	for(int lamp1=1;lamp1<32;lamp1++){//取反可以得到结果
		if(lampFail10[lamp1]) continue;
		for(int lamp2=1;lamp2<32;lamp2++){
			if(lampFail10[lamp2]) continue;
			flag1=true;
			for(int input=0;input<16;input++){
				if(Dubious & exp2[input]) continue;
				if((output & exp2[input] != 0) == (lampValue[lamp1][input] && lampValue[lamp2][input])){
					flag1 = false;
					break;
				}
			}
			if(flag1) return true;
		}
	}
	return false;										   
}

bool try3AND(unsigned short output){//三灯与门是否可解
	bool lampFail01[32];//lampValue为0但是output为1
	bool lampFail10[32];//lampValue为1但是output为0
	for(int lamp=1;lamp<32;lamp++){
		lampFail01[lamp] = false;
		lampFail10[lamp] = false;
		for(int input=0;input<16;input++){
			if(Dubious & exp2[input]) continue;
			if(lampValue[lamp][input] == 0 && output & exp2[input]) lampFail01[lamp] = true;
			else if(lampValue[lamp][input] && output & exp2[input] == 0) lampFail10[lamp] = true;
		}
	}
	lampFail01[16] = lampFail10[16] = true; //不遍历lamp=16的情况
	bool flag1 = false;
	for(int lamp1=1;lamp1<32;lamp1++){//不取反可以得到结果
		if(lampFail01[lamp1]) continue;
		for(int lamp2=1;lamp2<32;lamp2++){
			if(lampFail01[lamp2]) continue;
			for(int lamp3=1;lamp3<32;lamp3++){
				if(lampFail01[lamp3]) continue;
				flag1=true;
				for(int input=0;input<16;input++){
					if(Dubious & exp2[input]) continue;
					if((output & exp2[input] != 0) != (lampValue[lamp1][input] && lampValue[lamp2][input] && lampValue[lamp3][input])){
						flag1 = false;
						break;
					}
				}
				if(flag1) return true;
			}
		}
	}
	for(int lamp1=1;lamp1<32;lamp1++){//取反可以得到结果
		if(lampFail10[lamp1]) continue;
		for(int lamp2=1;lamp2<31;lamp2++){
			if(lampFail10[lamp2]) continue;
			for(int lamp3=1;lamp3<32;lamp3++){
				if(lampFail10[lamp3]) continue;
				flag1=true;
				for(int input=0;input<16;input++){
					if(Dubious & exp2[input]) continue;
					if((output & exp2[input] != 0) == (lampValue[lamp1][input] && lampValue[lamp2][input] && lampValue[lamp3][input])){
						flag1 = false;
						break;
					}
				}
				if(flag1) return true;
			}
		}
	}
	return false;
}

bool try3XOR(unsigned short output){//三灯异或门是否可解
	bool lampFail01[32];//lampValue为0但是output为1
	bool lampFail10[32];//lampValue为1但是output为0
	for(int lamp=1;lamp<32;lamp++){
		lampFail01[lamp] = false;
		lampFail10[lamp] = false;
		for(int input=0;input<16;input++){
			if(Dubious & exp2[input]) continue;
			if(lampValue[lamp][input] == 0 && output & exp2[input]) lampFail01[lamp] = true;
			else if(lampValue[lamp][input] && output & exp2[input] == 0) lampFail10[lamp] = true;
		}
	}
	lampFail01[16] = lampFail10[16] = true; //不遍历lamp=16的情况
	bool flag2,flag3;
	for(int lamp1=1;lamp1<32;lamp1++){
		for(int lamp2=1;lamp2<32;lamp2++){
			for(int lamp3=1;lamp3<32;lamp3++){
				for(int input=0;input<16;input++){
					if(Dubious & exp2[input]) continue;
					if(lampValue[lamp1][input]){
						if(lampValue[lamp2][input]){
							flag2 = true;
							break;
						}
						if(lampValue[lamp3][input]){
							flag3 = true;
							break;
						}
					}
					else if(lampValue[lamp2][input]){
						
				}
			}
		}
	}
}

void Initialize(){
	for(int lamp=0;lamp<31;lamp++){
		for(int input=0;input<16;input++){
			lampValue[lamp][input] = XOR(lamp^input);
		}
	}
}

bool XOR(int x){
	x ^= x >> 1;
	x ^= x >> 2;
	x ^= x >> 4;
	return x & 1 == 1;
}

int main(){
	for(int i=0;i<128;i++){
		Results[i]=leastLamps(getCombination(i));
	}
}
