
unsigned short int Output[7];
unsigned int exp2[16] = {1,2,4,8, 16,32,64,128, 256,512,1024,2048, 4096,8192,16384,32768};
bool Results[128];
unsigned short Dubious = 0;
bool lampValue[32][16]

unsigned short int getCombination(unsigned int comb){
	ret = 0;
	comb = (unsigned short int) comb;
	for(int i=0;i<7;i++){
		ret ^= comb & exp2[i] ? Output[i] : 0;
	}
	return ret;
}

int leastLamps(unsigned short output){
	if(try0(output)) return 0;
	if(try1(output)) return 1;
	if(try2(output)) return 2;
	if(try3XOR(output)) return 3;
	if(try3AND(output)) return 3;
	return 4;
}

bool try0(unsigned short output){//�޵��Ƿ�ɽ�
	return output | Dubious == 65535 || output & Dubious == 0;
}

bool try1(unsigned short output){//�����Ƿ�ɽ�
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

bool try2(unsigned short output){//˫���Ƿ�ɽ�
	bool lampFail01[32];//lampValueΪ0����outputΪ1
	bool lampFail10[32];//lampValueΪ1����outputΪ0
	for(int lamp=1;lamp<32;lamp++){
		lampFail01[lamp] = false;
		lampFail10[lamp] = false;
		for(int input=0;input<16;input++){
			if(Dubious & exp2[input]) continue;
			if(lampValue[lamp][input] == 0 && output & exp2[input]) lampFail01[lamp] = true;
			else if(lampValue[lamp][input] && output & exp2[input] == 0) lampFail10[lamp] = true;
		}
	}
	lampFail01[16] = lampFail10[16] = true; //������lamp=16�����
	bool flag1 = false;
	for(int lamp1=1;lamp1<32;lamp1++){//��ȡ�����Եõ����
		if(lampFail01[lamp1]) continue;
		for(int lamp2=1;lamp2<31;lamp2++){
			if(lampFail01[lamp2]) continue;
			flag1=true;
			for(int input=0;input<16;input++){
				if(Dubious & exp2[input]) continue;
				if((output & exp2[input] != 0) != (lampValue[lamp1][input] && lampvalue[lamp2][input])){
					flag1 = false;
					break;
				}
			}
			if(flag1) return true;
		}
	}
	for(int lamp1=1;lamp1<32;lamp1++){//ȡ�����Եõ����
		if(lampFail10[lamp1]) continue;
		for(int lamp2=1;lamp2<31;lamp2++){
			if(lampFail10[lamp2]) continue;
			flag1=true;
			for(int input=0;input<16;input++){
				if((output & exp2[input] != 0) == (lampValue[lamp1][input] && lampvalue[lamp2][input])){
					flag1 = false;
					break;
				}
			}
			if(flag1) return true;
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